#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Requisitos:
// Uma thread produtora gera N inteiros (aleatórios)
// Canal de tamanho M < N
// Várias threads consumidoras avaliam a primalidade e tem contagem individual
// Thread produtora preenche buffer de vez

#define MAX 1000
#define NTHREADS_CONS 4

typedef struct {
  int *buffer; // Buffer de tamanho M
  int id, N, M;
} thread_args;

sem_t mutex, vazio, cheio;

static inline int ehPrimo(long long int n) {
  int i;
  if (n <= 1)
    return 0;
  if (n == 2)
    return 1;
  if (n % 2 == 0)
    return 0;
  for (i = 3; i < sqrt(n) + 1; i += 2)
    if (n % i == 0)
      return 0;
  return 1;
}

int *gerar_entradas_aleat(int dim) {
  int *arr = (int *)malloc(sizeof(int) * dim);
  if (!arr) {
    fprintf(stderr, "Erro durante a alocação do vetor de int aleatorios.\n");
    pthread_exit(NULL);
  }
  for (int i = 0; i < dim; ++i)
    arr[i] = (int)(rand() % (MAX + 1));
  return arr;
}

int retirar(int *buffer, int dim) {
  static int in = 0;
  int aux;
  sem_wait(&cheio);
  sem_wait(&mutex);
  aux = buffer[in++];
  if (in == dim)
    sem_post(&vazio);
  in %= dim;
  sem_post(&mutex);
  return aux;
}

void inserir(int *buffer, int *entradas, int dim) {
  sem_wait(&vazio);
  sem_wait(&mutex);
  for (int i = 0; i < dim; ++i) {
    buffer[i] = entradas[i];
    sem_post(&cheio);
  }
  sem_post(&mutex);
}

void *produtora(void *args) {
  thread_args *t = (thread_args *)args;
  int *entradas = gerar_entradas_aleat(t->N);
  puts("Entrada aleatoria gerada: ");
  for (int i = 0; i < t->N; i++)
    printf("%d ", entradas[i]);
  puts("\n");
  for (int i = 0; i < t->N; i += t->M) {
    inserir(t->buffer, &entradas[i], t->M);
  }
  pthread_exit((void*) entradas);
}

void *consumidora(void *args) {
  thread_args *t = (thread_args *)args;
  int *qtd_primos = (int *)malloc(sizeof(int));
  if (!qtd_primos) {
    fprintf(stderr, "Erro durante alocação da variável qtd_primos.\n");
    free(qtd_primos);
    pthread_exit(NULL);
  }

  int rem = t->N % NTHREADS_CONS;
  int chunk = (t->N / NTHREADS_CONS) + ((t->id < rem) ? t->id : rem);

  for (int i = 0; i < chunk; i++) {
    int aux = retirar(t->buffer, t->M);
    if (ehPrimo(aux))
      (*qtd_primos)++;
  }
  pthread_exit((void *)qtd_primos);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  pthread_t *tids;
  int N, // Quantidade de inteiros aleatorios gerados (int)
      M; // Tamanho do canal (int)
  int qtd_primos_total = 0, qtd_primos_seq = 0, qtd_primos_vencedora = 0, vencedora = 0;
  int *entradas;

  if (argc < 3) {
    fprintf(stderr, "Uso: %s <qtd. de inteiros gerados> <tamanho do canal>\n",
            argv[0]);
    return 1;
  }

  N = (int)atoi(argv[1]);
  M = (int)atoi(argv[2]);

  if (N < 1 || M < 1 || M >= N) {
    fprintf(stderr, "Entrada de qtd. inteiros gerados ou o tamanho do canal "
                    "são inválidos.\n"
                    "- Ambas as entradas devem ser positivas.\n"
                    "- O tamanho do canal deve ser estritamente menor que a "
                    "qtd. de inteiros.\n");
    return 1;
  }

  tids = (pthread_t *)malloc(sizeof(pthread_t) * (1 + NTHREADS_CONS));
  if (!tids) {
    fprintf(stderr, "Erro durante a alocação do identificador das threads.\n");
    return 1;
  }

  int *buffer = (int *)malloc(sizeof(int) * M);
  if (!buffer) {
    fprintf(stderr, "Erro durante a alocação do buffer.\n");
    return 1;
  }

  // Buffer alocado na Heap é suficiente
  thread_args *arg = (thread_args *)malloc(sizeof(thread_args));
  if (!arg) {
    fprintf(stderr, "Erro durante a alocação da estrutura da thread.\n");
    return 1;
  }

  arg->buffer = buffer;
  arg->N = N;
  arg->M = M;

  sem_init(&mutex, 0, 1);
  sem_init(&vazio, 0, 1);
  sem_init(&cheio, 0, 0);

  // Primeira thread produtora
  if (pthread_create(&tids[0], NULL, produtora, (void *)arg) != 0) {
    fprintf(stderr, "Erro durante a criação da thread produtora.\n");
    return 1;
  }

  // Restante das threads consumidoras
  for (int i = 1; i < NTHREADS_CONS + 1; ++i) {
    arg->id = i;
    if (pthread_create(&tids[i], NULL, consumidora, (void *)arg) != 0) {
      fprintf(stderr, "Erro durante a criação das threads consumidoras.\n");
      return 1;
    }
  }

  // Join da thread produtora
  if (pthread_join(tids[0], (void**) &entradas) != 0) {
    fprintf(stderr, "Erro na junção da thread produtora.\n");
    return 1;
  }

  // Join das threads consumidoras
  for (int i = 1; i < NTHREADS_CONS + 1; ++i) {
    int *qtd_primos;
    if (pthread_join(tids[i], (void**) &qtd_primos) != 0) {
      fprintf(stderr, "Erro na junção das threads consumidoras.\n");
      return 1;
    }
    qtd_primos_total += *qtd_primos;
    if (*qtd_primos > qtd_primos_vencedora) {
      vencedora = i;
      qtd_primos_vencedora = *qtd_primos;
    }
  }

  sem_destroy(&mutex);
  sem_destroy(&vazio);
  sem_destroy(&cheio);

  // Comparação com o sequencial
  for (int i = 0; i < N; ++i)
      if (ehPrimo(entradas[i]))
          qtd_primos_seq++;
  // Impressão dos resultados
  printf("Quantidade total de primos: %d\n", qtd_primos_total);
  printf("Quantidade total de primos (seq): %d\n", qtd_primos_seq);
  printf("Thread %d foi a vencedora com %d primos.\n", vencedora,
         qtd_primos_vencedora);

  return 0;
}
