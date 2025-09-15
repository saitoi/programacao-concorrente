#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5
#define ITER 10

int canal[N] = {0};
int qtd = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_insere, cond_remove;

typedef struct {
    int obj;
    int *arr;
} thread_args;

// Situação hipótetica de processamento de obj

void *produtor(void *args) {
    thread_args *t = (thread_args*) args;
    int obj = t->obj;
    for (int i = 0; i < ITER; ++i) {
        obj = (int) transformar_obj(obj);
        // ...
        inserir(t->arr[i]);
        // ...
    }
    pthread_exit(NULL);
}

void *consumidor(void *args) {
    thread_args *t = (thread_args*) args;
    int obj = 0;
    for (int i = 0; i < ITER; ++i) {
        obj = (int) retirar();
        // ...
        processar_obj(obj);
        // ...
    }
}

// Inserindo e removendo um por vez

void inserir(int obj) {
    pthread_mutex_lock(&mutex);
    while (qtd == N)
        pthread_cond_wait(&cond_insere, &mutex);
    canal[in] = obj;
    qtd++;
    in = (in + 1) % N;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond_remove;);
}

int retirar(void) {
    pthread_mutex_lock(&mutex);
    while (qtd == 0)
        pthread_mutex_wait(&cond_remove, &mutex);
    int aux = canal[out];
    qtd--;
    out = (out + 1) % N;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond_insere);
    return aux;
}

// Inserindo em batch e removendo normal

void inserir_batch(int *objs) {
    pthread_mutex_lock(&mutex);
    while (qtd != 0)
        pthread_mutex_wait(&cond_insere, &mutex);
    qtd = N;
    for (int i = 0; i < N; ++i)
        canal[in] = objs[i];
    in = (in + N) % N;
    pthread_cond_broadcast(&cond_remove);
    pthread_mutex_unlock(&mutex);
}

int retirar_batch(void) {
    int aux;
    pthread_mutex_lock(&mutex);
    qtd--;
    aux = canal[out];
    out = (out + 1) % N;
    if (qtd == 0) pthread_cond_signal(&cond_insere);
    pthread_mutex_unlock(&mutex);
}

int main(void) {
    // ...
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_insere, NULL);
    pthread_cond_init(&cond_remove, NULL);
    // ...
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_insere);
    pthread_cond_destroy(&cond_remove);

}
