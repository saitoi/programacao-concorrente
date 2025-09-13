#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10
#define P 4

typedef struct {
    int (*A)[N];
    int (*B)[N];
    int (*C)[N];
    int start;
    int qtd;
} thread_args;

void *calcularLinha(void *arg) {
    thread_args *t = arg;
    for (int y = t->start; y < ((t->start)+(P*t->qtd)); y+=P)
        for (int j = 0; j < N; ++j) {
            int soma = 0;
            for (int k = 0; k < N; ++k)
                soma += t->A[y][k] * t->B[k][j];
            t->C[y][j] = soma;
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
    int rows[P] = {0};
    pthread_t tids[N];
    thread_args args[N];
    inicializarMatriz(A);
    inicializarMatriz(B);

    // Distribuir entre as cores
    int tarefas_int = N/P;
    int tarefas_rem = N%P;
    for (int i = 0; i < P; ++i)
        rows[i] = tarefas_int;

    // Distribuir o restante
    if (tarefas_rem > 0)
        for (int i = 0; i < tarefas_rem; ++i)
            rows[i] += 1;

    for (int i = 0; i < P; ++i) {
        args[i].A = A;
        args[i].B = B;
        args[i].C = C;
        args[i].start = i;
        args[i].qtd = rows[i];
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
