#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"

static inline int ehPrimo(long long int n) {
    int i;
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if ((n % 2) == 0) return 0;
    for (i = 3; i < (sqrt(n) + 1); i += 2)
        if ((n % i) == 0) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    int qtd_primos = 0;
    double start = 0.0, end = 0.0;
    long long nelementos;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <numero de elementos>\n", argv[0]);
        return 1;
    }

    nelementos = (long long) atoll(argv[1]);

    GET_TIME(start);
    for (long long i = 0; i < nelementos; ++i) {
        if (ehPrimo(i+1)) {
            ++qtd_primos;
        }
    }
    GET_TIME(end);

    double delta = end - start;

    printf("A quantidade total de primos é de %d.\n", qtd_primos);
    printf("O tempo de execução sequencial foi de %.26lf.\n", delta);

    return 0;
}
