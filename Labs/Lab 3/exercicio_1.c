#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

// Estrutura contendo os dados a serem passados para thread
typedef struct {
    float *arr_a;
    float *arr_b;
    int chunk;
} thread_args;

// Função executada pelas threads: Produto interno concorrente com paralelismo de dados
void *produto_interno(void *args) {
    thread_args *t = (thread_args*)args;
    double soma_aux = 0.0;
    double *ret;

    // Somatório do produto interno no espaço delimitado pela thread (0 -> tamanho do chunk)
    // Vale notar que como eu passo o endereço para uma posição específica do vetor, posso começar do zero.
    for (int i = 0; i < t->chunk; ++i)
        soma_aux += t->arr_a[i] * t->arr_b[i];

    // Alocação do espaço de memória para a variável ret a ser retornada
    free(t);
    ret = (double*) malloc(sizeof(double));
    if (ret != NULL) *ret = soma_aux;
    else fprintf(stderr, "Erro durante a alocação na thread.\n");
    pthread_exit((void*) ret);
}

// Cálculo da variação relativa do resultado, tomando o cuidado de capturar o módulo do resultado sequencial e do concorrente
double variacao_relativa(double seq, double conc) {
    if (seq == 0.0) {
        fprintf(stderr, "Resultado sequencial deve ser diferente de zero.\n");
        exit(1);
    }
    return fabs(conc - seq) / fabs(seq);
}

// Wrapper sobre fread que verifica o número de itens lidos
void fread_validado(void *object, size_t size, size_t nitems, FILE *file) {
    size_t ret = fread(object, size, nitems, file);
    if (ret != nitems) {
        fprintf(stderr, "Erro durante a leitura do arquivo. [fread]");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    float *arr_a, *arr_b;
    double resultado_conc = 0.0, resultado_seq = 0.0; // Resultados em double dos produtos internos seq e concorrentes
    long int dim;
    FILE *arquivo_leitura;
    void *thread_ret;
    double start, end;

    // Verifica a entrada do usuário na linha de comando
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <numero de threads> <nome arquivo de entrada>\n", argv[0]);
        return 1;
    }

    // Leitura e verificação do número de threads >= 0
    int nthreads = atoi(argv[1]);
    char *nome_arquivo_leitura = argv[2];
    if (nthreads < 1) {
        fprintf(stderr, "Insira um número de threads válido (nthreads > 0)\n");
        return 1;
    }

    // Abertura do arquivo binário para leitura
    arquivo_leitura = fopen(nome_arquivo_leitura, "rb");
    if (!arquivo_leitura) {
        fprintf(stderr, "Erro durante leitura do arquivo");
        return 1;
    }

    // Leitura da dimensão do arquivo de binário e alocação dos vetores arr_a e arr_b a serem lidos
    fread_validado(&dim, sizeof(long int), 1, arquivo_leitura);
    arr_a = (float*)malloc(sizeof(float)*dim);
    arr_b = (float*)malloc(sizeof(float)*dim);
    if (!arr_a || !arr_b) {
        fprintf(stderr, "Falha de alocação dos vetores arr_a e arr_b\n");
        return 1;
    }

    // Leitura dos vetores já alocados, bem como do resultado sequencial
    fread_validado(arr_a, sizeof(float), dim, arquivo_leitura);
    fread_validado(arr_b, sizeof(float), dim, arquivo_leitura);
    fread_validado(&resultado_seq, sizeof(double), 1, arquivo_leitura);
    fclose(arquivo_leitura);

    // Ajusta o número de threads à dimensão do vetor quando número de threads > dimensão
    if (nthreads > dim)
        nthreads = (int) dim;

    // Dividindo o vetor em chunks para cada thread
    int *chunks = (int*) malloc(sizeof(int)*nthreads);
    int base = (int) (dim / nthreads);
    int extra = (int) (dim % nthreads);
    // Caso não for divisível, particione os chunks restantes entre as primeiras (dim % nthreads) threads
    for (int i = 0; i < nthreads; ++i) 
        chunks[i] = base + (i < extra);

    // Alocação dos identificadores das threads
    pthread_t *tids = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);

    // Inicialização das threads e da estrutura a ser passada para cada uma
    // Cada thread processa uma parte de arr_a e arr_b a partir da posição inicial (init) definida
    // que é ajustada conforme o tamanho do chunk alocado para a thread
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

    // Finalização dae threads e coleta da soma parcial de cada uma
    for (int i = 0; i < nthreads; ++i) {
        if (pthread_join(tids[i], &thread_ret) != 0) { fprintf(stderr, "join\n"); return 1; }
        resultado_conc += *(double*)thread_ret;
        free(thread_ret);
    }
    GET_TIME(end); // Ao sair do loop, o produto interno concorrente já estará concluído (resultado_conc)

    // Cálculo da duração do prod interno concorrente e sua variação relativa em comparação ao seq
    double delta = end - start;
    double val_rel = variacao_relativa(resultado_seq, resultado_conc);

    // Impressão dos resultados gerais (valor do prod interno seq e conc, duração do concorrente e variação relativa)
    printf("Resultados para %d threads, vetor de %ld dimensões, arquivo '%s'\n", nthreads, dim, nome_arquivo_leitura);
    printf("========================================\n");
    printf("Resultado sequencial  : %.26lf\n", resultado_seq);
    printf("Resultado concorrente : %.26lf\n", resultado_conc);
    printf("Duração (concorrente) : %.10lf s\n", delta);
    printf("Variação relativa     : %.10e\n\n\n", val_rel);

    // Liberação dos espaços de memória alocados durante o programa
    free(chunks);
    free(tids);
    free(arr_a);
    free(arr_b);
    return 0;
}
