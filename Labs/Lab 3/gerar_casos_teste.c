#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "timer.h"

#define MAX 1000
//#define LOG

void inicializar_vetor_random(float **arr, long int dim) {
    (*arr) = (float*) malloc(sizeof(float) * dim);
    if ((*arr) == NULL) {
        fprintf(stderr, "Erro durante a alocação do vetor.");
        exit(1);
    }
    // Gera valores aleatórios float de -MAX até MAX
    for (long int i = 0; i < dim; ++i) {
        *(*arr+i) = ((float) rand() / RAND_MAX) * (2 * MAX) - MAX;
    }
}

double produto_interno(float *arr_a, float *arr_b, long int dim) {
    double soma = 0;
    for (int i = 0; i < dim; ++i)
        soma += arr_a[i] * arr_b[i];
    return soma;
}

void imprime_vetor(float *arr, long int dim) {
    for (int i = 0; i < dim; ++i)
        fprintf(stdout, "%.10f ", arr[i]);
}

void fwrite_validado(const void *object, size_t size, size_t nitems, FILE *file) {
    size_t ret = fwrite(object, size, nitems, file);
    if (ret != nitems) {
      fprintf(stderr, "Erro durante escrita no arquivo [fwrite]\n");
      exit(1);
    }
}

int main(int argc, char *argv[]) {
    // Usando seed do tempo em microsegundos para gerar valores 'ainda mais aleatórios'
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned)(tv.tv_usec + tv.tv_sec));

    // Vetores de entrada
    float *arr_a, *arr_b;
    FILE *arquivo_saida;
    double start, end;

    if (argc < 3) {
        fprintf(stderr, "Uso: %s <dimensao do vetor> <nome do arquivo de saida>\n", argv[0]);
        return 1;
    }

    long int dim = (long int) atoi(argv[1]);
    char *nome_arquivo_saida = (char*) argv[2];
    if (dim < 1) {
        fprintf(stderr, "Insira uma dimensão válida (dim > 0).\n");
        return 1;
    }

    inicializar_vetor_random(&arr_a, dim);
    inicializar_vetor_random(&arr_b, dim);

    GET_TIME(start);
    double resultado = produto_interno(arr_a, arr_b, dim);
    GET_TIME(end);

    double delta = end - start;

    fprintf(stdout, "Duração (sequencial)  : %.10lf s\n", delta);

    arquivo_saida = fopen(nome_arquivo_saida, "wb");
    if (arquivo_saida == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo. [fopen]");
        return 1;
    }

    fwrite_validado(&dim, sizeof(long int), 1, arquivo_saida);
    fwrite_validado(arr_a, sizeof(float), dim, arquivo_saida);
    fwrite_validado(arr_b, sizeof(float), dim, arquivo_saida);
    fwrite_validado(&resultado, sizeof(double), 1, arquivo_saida);

    #ifdef LOG
    fprintf(stdout, "Vetor A:");
    imprime_vetor(arr_a, dim);
    fprintf(stdout, "\nVetor B:");
    imprime_vetor(arr_b, dim);
    fprintf(stdout, "\nResultado sequencial: %lf\n", resultado);
    #endif

    fclose(arquivo_saida);
    free(arr_a);
    free(arr_b);

    return 0;
}
