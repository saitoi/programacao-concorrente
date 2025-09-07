#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

void *A(void *tid) {
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&x_mutex);
        x++;
        if ((x % 10) == 0) {
            pthread_cond_signal(&x_cond);
        }
        pthread_mutex_unlock(&x_mutex);
    }
    return NULL;
}

void *B(void *tid) {
    pthread_mutex_lock(&x_mutex);
    while ((x % 10) != 0) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("X=%d\n", x);
    pthread_mutex_unlock(&x_mutex);
    return NULL;
}

int main() {
    pthread_t threadsA[10], threadB;
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_create(&threadsA[i], NULL, A, NULL);
    }
    pthread_create(&threadB, NULL, B, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_join(threadsA[i], NULL);
    }
    pthread_join(threadB, NULL);

    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
    return 0;
}
