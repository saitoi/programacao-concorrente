#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 5

pthread_mutex_t mutex_leit_escr;
pthread_cond_t insere, remove;

// Padrão Leitor X Escritor

int qtd_escritor = 0;
int qtd_leitor = 0;

pthread_cond_t escrita, leitura;

void *escritor(void *args) {
    while (1) {
        // ...
        entraParaEscrever(void);
        // ...
        // ...
        saiDaEscrita(void);
    }
    pthread_exit(NULL);
}

void *leitora(void *args) {
    while (1) {
        // ...
        entraLeitura(void);
        // ...
        int elem = (int) v[<alguma_posicao>] // Estrutura de dados compartilhada
        // ...
        saiLeitura(void);
    }
    pthread_exit(NULL);
}

// Funções de Entrada e Saída - Leitor/Escritor

void entraLeitura(void) {
    pthread_mutex_lock(&mutex);
    while (qtd_escritor > 0)
        pthread_cond_wait(&leitura, &mutex);
    ++qtd_leitor;
    pthread_mutex_unlock(&mutex);
}

void saiLeitura(void) {
    pthread_mutex_lock(&mutex);
    --qtd_leitor;
    pthread_cond_signal(&escrita, &mutex);
    pthread_mutex_unlock(&mutex);
}

void entraParaEscrever(void) {
    while ((leitor > 0) || (escritor > 0))
        pthread_cond_wait(&escrita, &mutex);
    ++qtd_escritor;
    pthread_cond_signal(&escrita, &mutex);
    pthread_mutex_unlock(&mutex);
}

void saiEscrita(void) {
    pthread_mutex_lock(&mutex);
    qtd_escritor--;
    pthread_cond_signal(&escrita, &mutex);
    pthread_cond_broadcast(&leitura, &mutex);
    pthread_mutex_unlock(&mutex);
}

// Padrão Produtor X Consumidor

int vetor[5];
int in = 0, out = 0;
int qtd = 0;

pthread_mutex_t insere, remove;

void *produtor(void *args) {
    int elem;
    while (REPETE) {
        elem = produzElemento() // Função qualquer
        inserir(elem);
    }    
    pthread_exit(NULL);
}

void *consumidor(void *args) {
    int elem;
    while (REPETE) {
        elem = remover();
        processarElemento(elem); // Função qualquer
    }
    pthread_exit(NULL);
}

// Funções para interagir com a estrutura de dados
// Inserir x Remover um elemento por vez (Sincronização)

void inserir(int elem) {
    pthread_mutex_lock(&mutex);
    while (qtd == MAX)
        pthread_mutex_wait(&insere, &mutex);
    vetor[in] = elem;
    qtd++;
    in = (in + 1) % MAX;
    pthread_mutex_unlock(&mutex);
}

int remover(void) {
    pthread_mutex_lock(&mutex);
    while (!qtd)
        pthread_mutex_wait(&remove, &mutex);
    int aux = vetor[out];
    qtd--;
    out = (out + 1) % MAX;
    pthread_mutex_unlock(&mutex);
    return aux;
}

// Funções para operações em batch

void inserir_batch(int *elem) {
    pthread_mutex_lock(&mutex);
    while (qtd == N)
        pthread_cond_wait(&insere, &mutex);
    for (int i = 0; i < N; ++i)
        vetor[i] = elem[i];
    qtd = N;
    in = (in + N) % N;
    pthread_cond_broadcast(&remove);
    pthread_mutex_unlock(&mutex);
}

int remover(void) {
    pthread_mutex_lock(&mutex);
    while (qtd == 0)
        pthread_cond_wait(&remove, &mutex);
    item = v[out];
    qtd--;
    out = (out + 1) % N;
    if (qtd == 0)
        pthread_cond_signal(&insere);
    pthread_mutex_unlock(&mutex);
    return item
}

int main(int argc, char *argc[]) {
    int nthreads_produtoras, nthreads_consumidoras;    

    if (argc < 3) {
        fprintf(stderr, "Uso: %s <numero de threads produtoras> <numero de threads consumidoras>\n", argv[0]);
        return 1;
    }

    nthreads_produtoras = (int) atoi(argv[1]);
    nthreads_consumidoras = (int) atoi(argv[2]);

    pthread_t *tids = (pthread_t*) malloc(sizeof(pthread_t) * (nthreads_produtoras + nthreads_consumidoras));
    if (!tids) {
        fprintf(stderr, "Erro durante a alocação de espaço para os identificadores das threads.\n");
        return 1;
    }

    // Inicialização do mutex + cond
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&insere, NULL);
    pthread_cond_init(&remove, NULL);

    for (int i = 0; i < nthreads_produtoras; ++i) {
        if (pthread_create(&tids[i], NULL, produtora, (void*) i) == 0) {
            fprintf(stderr, "Erro durante a criação das threads.\n");
            return 1;
        }
    }

    for (int i = nthreads_produtoras; i < (nthreads_produtoras + nthreads_consumidoras); ++i) {
        if (pthread_create(&tids[i], NULL, consumidora, (void*) i) == 0) {
            fprintf(stderr, "Erro durante a criação das threads.\n");
            return 1;
        }
    }

    pthread_cond_destroy(&insere);
    pthread_cond_destroy(&remove);
}
