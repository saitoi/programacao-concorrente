#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

typedef struct {
    float *arr_a;
    float *arr_b;
    int chunk;
} thread_args;

void *produto_interno(void *args) {
    thread_args *t = (thread_args*)args;
    double soma_aux = 0.0;
    double *ret;

    for (int i = 0; i < t->chunk; ++i)
        soma_aux += (double) t->arr_a[i] * (double) t->arr_b[i];

    free(t);
    ret = (double*) malloc(sizeof(double));
    if (ret != NULL) *ret = soma_aux;
    else fprintf(stderr, "Erro durante a alocação na thread.\n");
    pthread_exit((void*) ret);
}

double variacao_relativa(double seq, double conc) {
    if (seq == 0.0) {
        fprintf(stderr, "Resultado sequencial deve ser diferente de zero.\n");
        exit(1);
    }
    return fabs(conc - seq) / fabs(seq);
}

void fread_validado(void *object, size_t size, size_t nitems, FILE *file) {
    size_t ret = fread(object, size, nitems, file);
    if (ret != nitems) {
        fprintf(stderr, "Erro durante a leitura do arquivo. [fread]");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    float *arr_a, *arr_b;
    double resultado_conc = 0.0, resultado_seq = 0.0;
    long int dim;
    FILE *arquivo_leitura;
    void *thread_ret;
    double start, end;

    if (argc < 3) {
        fprintf(stderr, "Uso: %s <numero de threads> <nome arquivo de entrada>\n", argv[0]);
        return 1;
    }

    int nthreads = atoi(argv[1]);
    char *nome_arquivo_leitura = argv[2];
    if (nthreads < 1) {
        fprintf(stderr, "nthreads >= 1\n");
        return 1;
    }

    arquivo_leitura = fopen(nome_arquivo_leitura, "rb");
    if (!arquivo_leitura) {
        fprintf(stderr, "Erro durante leitura do arquivo");
        return 1;
    }

    fread_validado(&dim, sizeof(long int), 1, arquivo_leitura);
    arr_a = (float*)malloc(sizeof(float)*dim);
    arr_b = (float*)malloc(sizeof(float)*dim);
    if (!arr_a || !arr_b) {
        fprintf(stderr, "Falha de alocação dos vetores arr_a e arr_b\n");
        return 1;
    }

    fread_validado(arr_a, sizeof(float), dim, arquivo_leitura);
    fread_validado(arr_b, sizeof(float), dim, arquivo_leitura);
    fread_validado(&resultado_seq, sizeof(double), 1, arquivo_leitura);
    fclose(arquivo_leitura);

    if (nthreads > dim)
        nthreads = (int) dim;

    int *chunks = (int*) malloc(sizeof(int)*nthreads);
    int base = (int) (dim / nthreads);
    int extra = (int) (dim % nthreads);
    for (int i = 0; i < nthreads; ++i)
        chunks[i] = base + (i < extra);

    pthread_t *tids = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);

    long int init = 0;
    GET_TIME(start);
    for (int i = 0; i < nthreads; ++i) {
        thread_args *args = (thread_args*) malloc(sizeof(thread_args));
        args->arr_a = &arr_a[init];
        args->arr_b = &arr_b[init];
        args->chunk = chunks[i];
        if (pthread_create(&tids[i], NULL, produto_interno, (void*)args) != 0) {
            fprintf(stderr, "Erro criando thread %d\n", i);
            return 1;
        }
        init += chunks[i];
    }

    for (int i = 0; i < nthreads; ++i) {
        if (pthread_join(tids[i], &thread_ret) != 0) { fprintf(stderr, "join\n"); return 1; }
        resultado_conc += *(double*)thread_ret;
        free(thread_ret);
    }
    GET_TIME(end);

    double delta = end - start;
    double val_rel = variacao_relativa(resultado_seq, resultado_conc);

    printf("Resultados para %d threads, vetor de %ld dimensões, arquivo '%s'\n", nthreads, dim, nome_arquivo_leitura);
    printf("========================================\n");
    printf("Resultado sequencial  : %.26lf\n", resultado_seq);
    printf("Resultado concorrente : %.26lf\n", resultado_conc);
    printf("Duração (concorrente) : %.10lf s\n", delta);
    printf("Variação relativa     : %.10e\n\n\n", val_rel);

    free(chunks);
    free(tids);
    free(arr_a);
    free(arr_b);
    return 0;
}
