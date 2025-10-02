#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

#define NTHREADS 2
#define MAX 1000

sem_t mutex;
sem_t cheio, vazio;
int qtd_canal;
int in = 0, out = 0;
int qtd_primos = 0;

typedef struct {
    int *seq;
    int *canal;
    int N;
    int M;
} thread_args;

static inline int ehPrimo(long long int n) {
    int i;
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if ((n % 2) == 0) return 0;
    for (i = 3; i < sqrt(n) + 1; i += 2)
        if ((n % i) == 0) return 0;
    return 1;
}

void init_vetor_random(int **vetor, int N) {
    (*vetor) = (int*) malloc(sizeof(int) * N);
    if ((*vetor) == NULL) {
        fprintf(stderr, "Erro durante a alocação da sequência de inteiros.\n");
        return 1;
    }
    for (int i = 0; i < N; ++i)
        (*vetor)[i] = (int) (rand() % (MAX + 1));
}

void insere(int n, int M, int *canal) {
    sem_wait(&vazio);
    sem_wait(&mutex);
    canal[in] = n;
    in = (in + 1) % M;
    sem_post(&cheio);
    sem_post(&mutex);
}

int retira(int M, int *canal) {
    int aux;
    sem_wait(&cheio);
    sem_wait(&mutex);
    aux = canal[out];
    out = (out + 1) % M;
    sem_post(&vazio);
    sem_post(&mutex);
}

void *produtora(void *args) {
    thread_args *arg = (thread_args*) args;
    int qtd_produzida = 0;
    while (qtd_produzida != N) {
        int aux = (arg->seq)[qtd_produzida];
        sem_wait(&mutex);
        insere(aux, arg->M, arg->canal);
        sem_post(&mutex);
        qtd_produzida++;
    }
    pthread_exit(NULL);
}

void *consumidora(void *args) {
    thread_args *arg = (thread_args*) args;
    int qtd_consumida = 0, aux;
    while (qtd_consumida != N) {
        sem_wait(&mutex);
        aux = retira(arg->M, arg->canal);
        sem_post(&mutex);
        qtd_consumida++;
        if (ehPrimo(aux)) qtd_primos++;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    pthread_t *tids;
    int N,      // Quantidade de inteiros produzidos pela thread PRODUTORA
        M,      // Tamanho do canal de inteiros
        *canal, // Vetor do canal
        *seq;   // Sequência de números aleatórios

    init_vetor_random(&seq);

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <quantidade de inteiros produzidos> <tam do canal de inteiros>", argv[0]);
        return 1;
    }

    N = (int) atoi(argv[1]);
    M = (int) atoi(argv[2]);

    if (M < 1 || N < 1) {
        fprintf(stderr, "Quantidade de inteiros produzidos e tamanho do canal devem ser positivos.\n");
        return 1;
    }

    sem_init(&mutex, 0, 1);
    sem_init(&cheio, 0, 0);
    sem_init(&vazio, 0, M);

    canal = (int*) malloc(sizeof(int) * M);
    if (!canal) {
        fprintf(stderr, "Erro durante a alocação do canal de inteiros.\n");
        return 1;
    }

    thread_args *arg = (thread_args*) malloc(sizeof(thread_args));
    if (!arg) {
        fprintf(stderr, "Erro durante a alocação da estrutura das threads.\n");
        return 1;
    }

    arg->seq = seq;
    arg->canal = canal;
    arg->N = N;
    arg->M = M;

    tids = (pthread_t*) malloc(sizeof(pthread_t) * NTHREADS);
    if (!tids) {
        fprintf(stderr, "Erro durante a alocação do identificador das threads.\n");
        return 1;
    }

    if (pthread_create(&tids[0], NULL, produtora, (void*) arg)) {
        fprintf(stderr, "Erro durante a criação da thread produtora.\n");
        return 1;
    }

    if (pthread_create(&tids[0], NULL, consumidora, (void*) arg)) {
        fprintf(stderr, "Erro durante a criação da thread produtora.\n");
        return 1;
    }

    for (int i = 0; i < NTHREADS; ++i) {
        if (pthread_join(tids[i], NULL) != 0) {
            fprintf(stderr, "Erro durante a junção das threads.\n");
            return 1;
        }
    }

    sem_destroy(&mutex);
    sem_destroy(&cheio);
    sem_destroy(&vazio);

    int qtd_primos_seq = 0;
    for (int i = 0; i < N; ++i)
        if (ehPrimo(seq[i])) qtd_primos_seq++;

    printf("Quantidade de primos encontrados (prod/cons): %d\n", qtd_primos);
    printf("Quantidade de primos encontrados (seq): %d\n", qtd_primos_seq);

    return 0;
}
