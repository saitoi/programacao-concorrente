// Objetivo: Encontrar o menor e maior valores em um vetor
// CLI: ./a.out <numero de threads> <entradas>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 100

pthread_mutex_t mutex;
int min_global = MAX;
int max_global = 0;

typedef struct {
    int id;
    int *arr;
    size_t chunk;
} thread_args;

void *find_min_max(void *args) {
    thread_args *t = (thread_args*) args;
    int min_local = MAX, max_local = 0;

    for (size_t i = 0; i < t->chunk; i++) {
        if (t->arr[i] < min_local) min_local = t->arr[i];
        if (t->arr[i] > max_local) max_local = t->arr[i];
    }

    printf("[%d] Valor mínimo local: %d\n", t->id, min_local);
    printf("[%d] Valor máximo local: %d\n", t->id, max_local);

    pthread_mutex_lock(&mutex);
    printf("[%d] Valor máximo global atual: %d\n", t->id, max_global);
    printf("[%d] Valor mínimo global atual: %d\n", t->id, min_global);
    if (min_local < min_global) min_global = min_local;
    if (max_global < max_local) max_global = max_local;
    printf("[%d] Valor máximo global atual: %d\n", t->id, max_global);
    printf("[%d] Valor mínimo global atual: %d\n", t->id, min_global);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void inicializar_vetor_random(int **arr, size_t dim) {
    (*arr) = (int*) malloc(sizeof(int) * dim);
    if (!arr) {
        fprintf(stderr, "Erro durante a alocação do vetor random. [malloc]");
        exit(1);
    }

    for (size_t i = 0; i < dim; ++i)
        (*arr)[i] = (int) rand() % (MAX + 1);
}

void imprimir_vetor(int *arr, size_t dim, char *nome_vetor) {
    printf("%s\n", nome_vetor);
    for (size_t i = 0; i < dim; ++i)
        printf("%d ", arr[i]);
    puts("\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    int *arr;
    int nthreads;
    size_t chunk;
    size_t dim;

    if (argc < 3) {
        fprintf(stderr, "Uso: %s <numero de threads> <dim>", argv[0]);
        return 1;
    }

    nthreads = atoi(argv[1]);
    dim = atoi(argv[2]);
    if (nthreads < 1 || dim < 1 || dim % nthreads != 0) {
        fprintf(stderr, "Erro na definição dos parametros <numero de threads> ou <dim>.");
        fprintf(stderr, "Dimensão do vetor deve ser divisível pelo número de threads.");
        return 1;
    }

    inicializar_vetor_random(&arr, dim);
    imprimir_vetor(arr, dim, "Vetor aleatório");

    pthread_t *tids = (pthread_t*) malloc(sizeof(pthread_t) * nthreads);
    if (!tids) {
        fprintf(stderr, "Erro durante alocação do identificador das threads. [malloc]");
        return 1;
    }

    if (dim < nthreads)
        nthreads = dim;

    chunk = dim / nthreads;

    for (int i = 0; i < nthreads; ++i) {
        thread_args *arg = (thread_args*) malloc(sizeof(thread_args));
        if (!arg) {
            fprintf(stderr, "Erro durante alocação da estrutura para as threads. [malloc]");
            return 1;
        }
        arg->id = i;
        arg->arr = &arr[i * chunk];
        arg->chunk = chunk;
        if (pthread_create(&tids[i], NULL, find_min_max, (void*) arg) != 0) {
            fprintf(stderr, "Erro durante a criação das threads. [pthread_create]");
            return 1;
        }
    }

    for (int i = 0; i < nthreads; ++i) {
        if (pthread_join(tids[i], NULL) != 0) {
            fprintf(stderr, "Erro durante a junção das threads. [pthread_join]");
            return 1;
        }
    }

    free(tids);
    pthread_mutex_destroy(&mutex);

    printf("Valor máximo global: %d\n", max_global);
    printf("Valor mínimo global: %d\n", min_global);

    return 0;
}

