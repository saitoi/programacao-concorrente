// Objetivo: Implementar operação saxpy concorrente com número limitado de threads
// Obs. Computar os chunks no contexto das threads
// CLI: ./a.out <numero de threads> <tamanho do vetor> <k>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    float *A, *B, *C;
    int k;
    int id;
    int nthreads;
    size_t dim; 
} thread_args;

void *saxpy(void *args) {
    thread_args *t = (thread_args*) args;
    size_t chunk = (size_t) t->dim / t->nthreads;
    chunk += (t->id < (t->dim % t->nthreads));
    size_t start = t->id * chunk;

    for (size_t i = start; i < start + chunk; ++i)
        t->C[i] = t->A[i] * t->k + t->B[i];

    free(t);
    pthread_exit(NULL);
}

void inicializar_vetor(float **arr, size_t dim) {
    (*arr) = (float*) malloc(sizeof(float) * dim);
    if (!(*arr)) {
        fprintf(stderr, "Erro durante alocação do vetor de floats. [malloc]");
        exit(1);
    }

    for (size_t i = 0; i < dim; i++)
        (*arr)[i] = i;
}

void imprimir_vetor(float *arr, char *nome_vetor, size_t dim) {
    printf("%s:\n", nome_vetor);
    for (size_t i = 0; i < dim; i++)
        printf("%.10f ", arr[i]);
    puts("\n");
}

int main(int argc, char *argv[]) {
    float *A, *B, *C;
    pthread_t *tids;
    int nthreads, k;
    size_t dim;

    // Se o usuário passar qtd_args > 3 apenas ignore.
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <numero de threads> <tamanho do vetor> <k>\n", argv[0]);
        return 1;
    }

    k = (int) atoi(argv[3]);
    nthreads = (int) atoi(argv[1]);
    if (nthreads < 1) {
        fprintf(stderr, "Número de threads deve ser positivo.");
        return 1;
    }

    dim = (size_t) atoi(argv[2]);
    if (dim < 1) {
        fprintf(stderr, "Dimensão do vetor deve ser positiva.");
        return 1;
    }

    inicializar_vetor(&A, dim);
    inicializar_vetor(&B, dim);
    inicializar_vetor(&C, dim);

    imprimir_vetor(A, "Vetor A", dim);
    imprimir_vetor(B, "Vetor B", dim);
    imprimir_vetor(C, "Vetor C", dim);

    if (dim < nthreads) nthreads = dim;
    tids = (pthread_t*) malloc(sizeof(pthread_t) * nthreads);
    if (!tids) {
        fprintf(stderr, "Erro durante alocação do identificador das threads. [malloc]");
        exit(1);
    }

    for (int i = 0; i < nthreads; ++i) {
        thread_args *arg = (thread_args*) malloc(sizeof(thread_args));
        if (!arg) {
            fprintf(stderr, "Erro durante alocação da estrutura das threads. [malloc]");
            return 1;
        }
        arg->A = A;
        arg->B = B;
        arg->C = C;
        arg->id = i;
        arg->nthreads = nthreads;
        arg->dim = dim;
        arg->k = k;
        if (pthread_create(&tids[i], NULL, saxpy, (void*) arg) != 0) {
            fprintf(stderr, "Erro durante criação das threads. [pthread_create]");
            return 1;
        }
    }

    for (int i = 0; i < nthreads; ++i) {
        if (pthread_join(tids[i], NULL) != 0) {
            fprintf(stderr, "Erro durante join da thread, [pthread_join]");
            return 1;
        }
    }

    imprimir_vetor(C, "Vetor C", dim);

    return 0;
}
