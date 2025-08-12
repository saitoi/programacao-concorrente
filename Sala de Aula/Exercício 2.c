#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *arr;
} thread_args;

void *thread_increment(void *args) {
    thread_args *t = (thread_args*) args;
    *(t->arr) += 1;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Você deve passar um e apenas um argumento.");
        return 1;
    }

    int entrada = atoi(argv[1]);

    int *arr = (int*) malloc(sizeof(int) * entrada);
    pthread_t *tids = (pthread_t*) malloc(sizeof(pthread_t) * entrada);
    thread_args *args = (thread_args*) malloc(sizeof(thread_args) * entrada);

    if (arr == NULL || tids == NULL || args == NULL) {
        printf("Houve um erro durante a alocação dos vetores..");
        exit(1);
    }

    for (int i = 0; i < entrada; ++i) {
        args[i].arr = &arr[i];
        if (pthread_create(tids+i, NULL, thread_increment, (void*)&args[i]) != 0) {
            printf("Não foi possível criar a thread %d", i);
            exit(1);
        }
    }
    
    for (int i = 0; i < entrada; ++i)
        pthread_join(tids[i], NULL);

    printf("Vetor resultante: ");
    for (int i = 0; i < entrada; ++i)
        printf("%d ", arr[i]);

    return 0;
}
