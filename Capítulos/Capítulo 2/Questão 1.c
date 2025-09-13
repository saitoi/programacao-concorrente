#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

typedef struct {
    int (*A)[N];
    int (*B)[N];
    int (*C)[N];
    int row;
} thread_args;

void *calcularLinha(void *arg) {
    thread_args *t = arg;
    for (int j = 0; j < N; ++j) {
        int soma = 0;
        for (int k = 0; k < N; ++k)
            soma += t->A[t->row][k] * t->B[k][j];
        t->C[t->row][j] = soma;
    }
    return NULL;
}

void inicializarMatriz(int m[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            m[i][j] = i + j;
}

int main(void) {
    int A[N][N], B[N][N], C[N][N] = {0};
    pthread_t tids[N];
    thread_args args[N];

    inicializarMatriz(A);
    inicializarMatriz(B);

    for (int i = 0; i < N; ++i) {
        args[i].A = A;
        args[i].B = B;
        args[i].C = C;
        args[i].row = i;
        if (pthread_create(&tids[i], NULL, calcularLinha, &args[i]) != 0)
            perror("pthread_create");
    }

    for (int i = 0; i < N; ++i)
        pthread_join(tids[i], NULL);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%4d", C[i][j]);
        putchar('\n');
    }
    return 0;
}
