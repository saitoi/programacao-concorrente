// Objetivo: Computar o valor de pi usando a formula de Bailey-Borwein-Plouffe
// CLI: ./a.out <numero de threads> <entradas>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct {
    int id;
    int nthreads;
    size_t entradas;
} thread_args;

static inline double bbp(size_t i) {
    double d = (double) i;
    double num = 4.0/(8.0 * d + 1.0)
               - 2.0/(8.0 * d + 4.0)
               - 1.0/(8.0 * d + 5.0)
               - 1.0/(8.0 * d + 6.0);
    return num / pow(16.0, d);
}

void *calc_pi(void *args) {
    thread_args *t = (thread_args*) args;
    double pi_aux = 0.0;

    size_t base = (size_t) t->entradas / t->nthreads;
    size_t rem = (size_t) t->entradas % t->nthreads;
    size_t chunk = base + (t->id < (int) rem);
    size_t start = (size_t)t->id * base + (t->id < (int) rem ? (size_t) t->id : rem);

    printf("Start: %zu, Chunk: %zu\n", start, chunk);
    for (size_t i = start; i < start + chunk; i++)
        pi_aux += bbp(i);

    printf("Pi part: %.17g\n", pi_aux);
    double *pi_part = malloc(sizeof(double));
    if (!pi_part) { fprintf(stderr, "Erro durante alocação do double para retorno. [malloc]"); exit(1); }
    else *pi_part = pi_aux;
    free(t);
    pthread_exit((void*) pi_part);
}

int main(int argc, char *argv[]) {
    int nthreads, entradas;
    double pi = 0.0;
    size_t dim;
    void *thread_ret;

    if (argc < 3) {
        fprintf(stderr, "Uso: %s <numero de threads> <entradas>", argv[0]);
        return 1;
    }

    nthreads = atoi(argv[1]);
    entradas = atoi(argv[2]);
    if (nthreads < 1 || entradas < 1) {
        fprintf(stderr, "Erro na definição dos parametros <numero de threads> ou <entradas>.");
        return 1;
    }
    if (entradas < nthreads)
        nthreads = entradas;

    pthread_t *tids = (pthread_t*) malloc(sizeof(pthread_t) * nthreads);
    if (!tids) {
        fprintf(stderr, "Erro durante alocação do identificador das threads. [malloc]");
        return 1;
    }

    for (int i = 0; i < nthreads; ++i) {
        thread_args *arg = malloc(sizeof(thread_args));
        if (!arg) {
            fprintf(stderr, "Erro durante alocação da estrutura pras threads. [malloc]");
            return 1;
        }
        arg->id = i;
        arg->nthreads = nthreads;
        arg->entradas = entradas;
        if (pthread_create(&tids[i], NULL, calc_pi, (void*) arg) != 0) {
            fprintf(stderr, "Erro durante a criação das threads. [pthread_create]");
            return 1;
        }
    }

    for (int i = 0; i < nthreads; ++i) {
        if (pthread_join(tids[i], &thread_ret) != 0) {
            fprintf(stderr, "Erro durante a junção das threads. [pthread_join]");
            return 1;
        }
        pi += *(double*) thread_ret;
        free(thread_ret);
    }

    printf("O resultado de pi com %d iterações: %.20lf", entradas, pi);

    free(tids);

    return 0;
}

