#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define k 2

typedef struct {
    int *A;
    int *B;
    int *C;
} thread_args;

void *saxpy(void *args) {
    thread_args *t = (thread_args*) args;
    *(t->C) = *(t->A) * k + *(t->B);
    return NULL;
}

void inicializarVetor(int *arr) {
    for (int i = 0; i < N; ++i)
        arr[i] = i;
}

int main(void) {
    int A[N] = {0},
        B[N] = {0},
        C[N] = {0};
    pthread_t tids[N];
    thread_args args[N];

    inicializarVetor(A);
    inicializarVetor(B);

    for (int i = 0; i < N; ++i)
        printf("%d ", A[i]);
    printf("\n");

    for (int i = 0; i < N; ++i) {
        args[i].A = &A[i];
        args[i].B = &B[i];
        args[i].C = &C[i];
        if (pthread_create(tids+i, NULL, saxpy, (void*) &args[i]) != 0) {
            printf("Erro durante a criação da thread..");
            exit(1);
        }
    }

    for (int i = 0; i < N; ++i)
        pthread_join(tids[i], NULL);

    printf("Vetor resultante: ");
    for (int i = 0; i < N; ++i)
        printf("%d ", C[i]);

    return 0;
}
