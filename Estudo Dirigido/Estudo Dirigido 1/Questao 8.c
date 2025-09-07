// Objetivo: Threads se comunicando constantemente

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond1, cond2;
int ordem = 0;

// Enumeração da possível ordem de execução das instruções

void *thread1(void *arg) {
    pthread_mutex_lock(&mutex);

    printf("olá, você está acessando a variável 'aux' agora?\n"); // 2
    ordem = 1;
    pthread_cond_signal(&cond1); // 3
    while (ordem < 2) pthread_cond_wait(&cond2, &mutex); // 4

    printf("certo, então vou aterá-la, tá?\n"); // 8
    ordem = 3;
    pthread_cond_signal(&cond1); // 9
    while (ordem < 4) pthread_cond_wait(&cond2, &mutex); // 10

    printf("terminei a alteração da variável 'aux'\n"); // 14
    ordem = 5;
    pthread_cond_signal(&cond1); // 15

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    pthread_mutex_lock(&mutex);

    while (ordem < 1) pthread_cond_wait(&cond1, &mutex); // 1
    printf("oi, não, não estou\n"); // 5
    ordem = 2;
    pthread_cond_signal(&cond2); // 6

    while (ordem < 3) pthread_cond_wait(&cond1, &mutex); // 7
    printf("tudo bem\n"); // 11
    ordem = 4;

    pthread_cond_signal(&cond2); // 12
    while (ordem < 5) pthread_cond_wait(&cond1, &mutex); // 13
    printf("perfeito, recebido!\n"); // 17

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tids[2];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond1, NULL);
    pthread_cond_init(&cond2, NULL);

    if (pthread_create(&tids[0], NULL, thread1, NULL) != 0) {
        fprintf(stderr, "Erro durante criação das threads.\n");
        return 1;
    }
    if (pthread_create(&tids[1], NULL, thread2, NULL) != 0) {
        fprintf(stderr, "Erro durante criação das threads.\n");
        return 1;
    }

    
    for (int i = 0; i < 2; i++) {
        if (pthread_join(tids[i], NULL) != 0) {
            fprintf(stderr, "Erro durante junção das threads.\n");
            return 1;
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    return 0;
}
