#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

int estado = 0;
pthread_mutex_t mutex;
pthread_cond_t pedido, tchau;

// Primeiras duas threads
void *saudacoes(void *args) {
    static int saudacao = 0;
    pthread_mutex_lock(&mutex);
    (saudacao) ? printf("Oi Maria!\n") : printf("Oi José!\n");
    saudacao++;
    estado++;
    if (saudacao == 2) pthread_cond_signal(&pedido);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

// Terceira thread
void *solicitacao(void *args) {
    pthread_mutex_lock(&mutex);
    while (estado < 2)
        pthread_cond_wait(&pedido, &mutex);
    printf("Sente-se por favor!\n");
    estado++;
    pthread_cond_broadcast(&tchau);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

// Últimas duas threads
void *despedidas(void *args) {
    static int despedidas = 0;
    pthread_mutex_lock(&mutex);
    while (estado < 3)
        pthread_cond_wait(&tchau, &mutex);
    (despedidas) ? printf("Até mais Maria!\n") : printf("Até mais José!\n");
    despedidas++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tids[N];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&pedido, NULL);
    pthread_cond_init(&tchau, NULL);

    pthread_create(&tids[0], NULL, saudacoes, NULL);
    pthread_create(&tids[1], NULL, saudacoes, NULL);
    pthread_create(&tids[2], NULL, solicitacao, NULL);
    pthread_create(&tids[3], NULL, despedidas, NULL);
    pthread_create(&tids[4], NULL, despedidas, NULL);

    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_join(tids[2], NULL);
    pthread_join(tids[3], NULL);
    pthread_join(tids[4], NULL);

    pthread_cond_destroy(&pedido);
    pthread_cond_destroy(&tchau);
    pthread_mutex_destroy(&mutex);
}
