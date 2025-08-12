#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define P 4

typedef struct {
    int *arr;
    int chunk;
} thread_args;

void *thread_increment(void *arg) {
    thread_args *t = (thread_args*) arg;
    for (int i = 0; i < t->chunk; ++i) {
        t->arr[i] += 1;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Passe um e apenas um argumento.");
        return 1;
    }

    int entrada = atoi(argv[1]);
    printf("Entrada: %d.\n", entrada);
    if (entrada < 1) {
        printf("A entrada não pode ser nula");
        return 1;
    }

    int tamanho_vetor = P * entrada;
    int *vetor = (int *) malloc(P * entrada * sizeof(int));
    if (vetor == NULL) {
        printf("Erro durante a alocação.");
        exit(1);
    }

    for (int i = 0; i < tamanho_vetor; ++i)
        vetor[i] = 0;

    pthread_t tids[P];
    thread_args args[P];
    for (int i = 0; i < P; ++i) {
        int start = i * (tamanho_vetor/P);
        args[i].chunk = (tamanho_vetor/P);
        args[i].arr = &vetor[start];
        printf("Começo da thread %d: %d\n", i, start);
        if (pthread_create(tids+i, NULL, thread_increment, (void *)&args[i]) != 0) {
            printf("Erro durante a criação da thread.");
            exit(1);
        }
    }

    for (int i = 0; i < P; ++i)
        pthread_join(tids[i], NULL);

    printf("Vetor resultante: ");
    for (int i = 0; i < tamanho_vetor; ++i)
        printf("%d ", vetor[i]);

    return 0;
}
