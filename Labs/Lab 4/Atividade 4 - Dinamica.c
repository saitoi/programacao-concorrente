#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"

long long qtd_primos = 0;
long long nelementos = 0;
pthread_mutex_t mutex;

typedef struct {
    int nthreads;
    int id;
} thread_args;

static inline int ehPrimo(long long int n) {
    int i;
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if ((n % 2) == 0) return 0;
    for (i = 3; i < (sqrt(n) + 1); i += 2)
        if ((n % i) == 0) return 0;
    return 1;
}

void *quantos_primos(void *args) {
    thread_args *t = (thread_args*) args;

    while (1) {
        pthread_mutex_lock(&mutex);
        /* printf("Entrei aqui com nelementos=%lld, qtd_primos=%lld\n", nelementos, qtd_primos); */
        if (nelementos <= -1) {
            pthread_mutex_unlock(&mutex);
            break;
        } 
        if (ehPrimo(nelementos))
            qtd_primos++;
        nelementos -= 2;
        pthread_mutex_unlock(&mutex);
    }

    free(t);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int nthreads;
    double start = 0.0, end = 0.0;

    pthread_mutex_init(&mutex, NULL);
    
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <numero de threads> <numero de elementos>", argv[0]);
        return 1;
    }

    nthreads = (int) atoi(argv[1]);
    nelementos = (long long) atoll(argv[2]);

    if (nelementos < 1) {
        fprintf(stderr, "Número de elementos deve ser um valor positivo não nulo.\n");
        return 1;
    }

    if ((nelementos % 2) == 0) {
        nelementos--; // Começar com número de elementos ímpar.
        qtd_primos++; // 2 é primo, logo contabilizo ele aqui.
    }

    if (nelementos < nthreads)
        nthreads = (int) nelementos;

    pthread_t *tids = (pthread_t*) malloc(sizeof(pthread_t) * (size_t) nthreads);
    if (!tids) {
        fprintf(stderr, "Erro durante a alocação do identificador das threads.");
        return 1;
    }

    GET_TIME(start);
    for (int i = 0; i < nthreads; ++i) {
        thread_args *args = (thread_args*) malloc(sizeof(thread_args));
        if (!args) {
            fprintf(stderr, "Erro durante a alocação da estrutura.");
            return 1;
        }
        args->id = i;
        args->nthreads = nthreads;
        if (pthread_create(&tids[i], NULL, quantos_primos, (void*) args) != 0) {
            fprintf(stderr, "Erro durante a criação das threads.");
            return 1;
        }
    }

    for (int i = 0; i < nthreads; ++i) {
        if (pthread_join(tids[i], NULL) != 0) {
            fprintf(stderr, "Erro durante a junção das threads.");
            return 1;
        }
    }
    GET_TIME(end);

    double delta = end - start;

    printf("A quantidade total de primos é de %lld.\n", qtd_primos);
    printf("O tempo de execução concorrente foi de %.26lf.\n", delta);

    pthread_mutex_destroy(&mutex);

    return 0;
}
