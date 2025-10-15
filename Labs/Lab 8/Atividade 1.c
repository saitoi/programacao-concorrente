#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Requisitos:
// Uma thread produtora gera N inteiros (aleatórios)
// Canal de tamanho M < N
// Várias threads consumidoras avaliam a primalidade e tem contagem individual
// Thread produtora preenche buffer de vez

// Observações
// Por padrão, os números gerados pela thread produtora são aleatórios.
// No entanto, o usuário poderá passar um intervalo.

/* ------------------- MACROS ------------------- */

#define MAX 1000        // Número aleatório máximo gerado
#define NTHREADS_CONS 4 // Número de threads consumidoras

// Macro para exibir mensagem se a VERBOSE estiver definido
#ifdef VERBOSE
#define LOG(output, fmt, ...) fprintf(output, "[VERBOSE] " fmt, ##__VA_ARGS__)
#else
#define LOG(output, fmt, ...) ((void)0)
#endif

// Estrutura para os argumentos das threads
typedef struct {
  int *buffer;
  int id, N, M, inicio;
} thread_args;

// Variáveis globais
int qtd_buffer = 0;        // Qtd. elementos no buffer
sem_t mutex, vazio, cheio; // Semáforos

/* ------------------- EH PRIMO? ------------------- */

static inline int ehPrimo(long long int n) {
  int i;
  if (n <= 1)
    return 0;
  if (n == 2)
    return 1;
  if (n % 2 == 0)
    return 0;
  for (i = 3; i < sqrt(n) + 1; i += 2)
    if (n % i == 0)
      return 0;
  return 1;
}

/* ------------------- GERAR ENTRADAS (ALEATÓRIA / SEQUENCIAL) * ------------------- */

// Inicializa as últimas posições com -1 para as threads consumidoras
// finalizarem
int *gerar_entradas_seq(int inicio, int dim) {
  int *arr = (int *)malloc(sizeof(int) * dim);
  if (!arr) {
    fprintf(stderr, "Erro durante a alocação do vetor de int sequencial.\n");
    pthread_exit(NULL);
  }
  int dados = dim - NTHREADS_CONS;
  for (int i = 0; i < dados; ++i)
    arr[i] = i + inicio;
  for (int i = dados; i < dim; ++i)
    arr[i] = -1;
  return arr;
}

// Inicializa as últimas posições com -1 para as threads consumidoras
// finalizarem
int *gerar_entradas_aleat(int dim) {
  int *arr = (int *)malloc(sizeof(int) * dim);
  if (!arr) {
    fprintf(stderr, "Erro durante a alocação do vetor de int aleatorios.\n");
    pthread_exit(NULL);
  }
  int dados = dim - NTHREADS_CONS;
  for (int i = 0; i < dados; ++i)
    arr[i] = (int)(rand() % (MAX + 1));
  for (int i = dados; i < dim; ++i)
    arr[i] = -1;
  return arr;
}

/* ------------------- RETIRAR ------------------- */

int retirar(int *buffer, int dim) {
  static int in = 0;
  int aux;
  sem_wait(&cheio);
  sem_wait(&mutex);
  aux = buffer[in];
  LOG(stdout, "Consumidora pegou: %d\n", buffer[in]);
  in = (in + 1) % dim;
  qtd_buffer--;
  if (qtd_buffer == 0)
    sem_post(&vazio);
  sem_post(&mutex);
  return aux;
}

/* ------------------- INSERIR ------------------- */

void inserir(int *buffer, int *entradas, int dim) {
  sem_wait(&vazio);
  sem_wait(&mutex);
  for (int i = 0; i < dim; ++i) {
    buffer[i] = entradas[i];
    qtd_buffer++;
    LOG(stdout, "Produtora inseriu: %d\n", buffer[i]);
  }
  sem_post(&mutex);
  for (int i = 0; i < dim; ++i) {
    sem_post(&cheio);
  }
}

/* ------------------- PRODUTORA ------------------- */

void *produtora(void *args) {
  thread_args *t = (thread_args *)args;
  int *entradas;
  // Se início for positivo ou igual à zero, gera o intervalo sequencial [I, I +
  // N)
  if (t->inicio > -1) {
    LOG(stdout, "Entrada sequencial gerada:");
    entradas = gerar_entradas_seq(t->inicio, t->N);
  } else {
    LOG(stdout, "[VERBOSE] Entrada aleatória gerada:");
    entradas = gerar_entradas_aleat(t->N);
  }

#ifdef VERBOSE
  for (int i = 0; i < t->N; i++)
    fprintf(stdout, "%d ", entradas[i]);
  fprintf(stdout, "\n");
#endif

  for (int i = 0; i < t->N; i += t->M) {
    int qtd_inserir = ((t->N - i) < t->M) ? (t->N - i) : t->M;
    inserir(t->buffer, &entradas[i], qtd_inserir);
  }
  pthread_exit((void *)entradas);
}

/* ------------------- CONSUMIDORA ------------------- */

void *consumidora(void *args) {
  thread_args *t = (thread_args *)args;
  int *qtd_primos = (int *)malloc(sizeof(int));
  if (!qtd_primos) {
    fprintf(stderr, "Erro durante alocação da variável qtd_primos.\n");
    pthread_exit(NULL);
  }
  *qtd_primos = 0;

  int aux;
  while (1) {
    aux = retirar(t->buffer, t->M);
    // Threads consumidoras capturam o -1, sinalizando término
    if (aux == -1)
      break;
    if (ehPrimo(aux))
      (*qtd_primos)++;
  }
  free(t);
  pthread_exit((void *)qtd_primos);
}

/* ------------------- MAIN ------------------- */

int main(int argc, char *argv[]) {
  srand(time(NULL));
  pthread_t *tids;
  int N,      // Quantidade de inteiros aleatorios gerados (int)
      M,      // Tamanho do canal (int)
      inicio; // Parâmetro opcional para gerar um intervalo sequencial
  int qtd_primos_conc =
          0, // Quantidade de primos capturados pelas threads consumidoras
      qtd_primos_vencedora = 0, // Quantidade de primos da thread vencedora
      vencedora =
          0; // Id da thread vencedora (considerando só uma thread vencedora)
  int *entradas;

  if (argc < 3) {
    fprintf(stderr,
            "Uso: %s <qtd. de inteiros gerados> <tamanho do canal> <inicio>\n",
            argv[0]);
    return 1;
  }

  N = (int)atoi(argv[1]);
  M = (int)atoi(argv[2]);
  inicio = (int)((argc == 4) ? atoi(argv[3]) : -1);

  if (N < 1 || M < 1 || M >= N) {
    fprintf(stderr, "Entrada de qtd. inteiros gerados ou o tamanho do canal "
                    "são inválidos.\n"
                    "- Ambas as entradas devem ser positivas.\n"
                    "- O tamanho do canal deve ser estritamente menor que a "
                    "qtd. de inteiros.\n");
    return 1;
  }

  LOG(stdout,
      "Entrada:\n"
      "\t  - N: %d\n"
      "\t  - M: %d\n"
      "\t  - inicio: %d\n",
      N, M, inicio);

  // Inicialização do identificador das threads.
  tids = (pthread_t *)malloc(sizeof(pthread_t) * (1 + NTHREADS_CONS));
  if (!tids) {
    fprintf(stderr, "Erro durante a alocação do identificador das threads.\n");
    return 1;
  }

  // Inicialização canal/buffer
  int *buffer = (int *)malloc(sizeof(int) * M);
  if (!buffer) {
    fprintf(stderr, "Erro durante a alocação do buffer.\n");
    return 1;
  }

  // Buffer alocado na Heap é suficiente
  thread_args *arg = (thread_args *)malloc(sizeof(thread_args));
  if (!arg) {
    fprintf(stderr, "Erro durante a alocação da estrutura da thread.\n");
    return 1;
  }

  // Inicialização dos semáforos
  sem_init(&mutex, 0, 1);
  sem_init(&vazio, 0, 1);
  sem_init(&cheio, 0, 0);

  // Inicialização dos argumentos para thread produtora
  arg->inicio = inicio;
  arg->buffer = buffer;

  // Argumento para thread produtora
  // Qtd. inteiros gerados = N + "-1 para sinalizar encerramento das
  // consumidoras"
  arg->N = N + NTHREADS_CONS;
  arg->M = M;

  // Primeira thread produtora
  if (pthread_create(&tids[0], NULL, produtora, (void *)arg) != 0) {
    fprintf(stderr, "Erro durante a criação da thread produtora.\n");
    return 1;
  }

  // Restante das threads consumidoras
  // thread_args *args_cons[NTHREADS_CONS];
  for (int i = 0; i < NTHREADS_CONS; ++i) {
    thread_args *args_cons = (thread_args *)malloc(sizeof(thread_args));
    if (!args_cons) {
      fprintf(
          stderr,
          "Erro durante a alocação da estrutura da thread consumidora %d.\n",
          i);
      return 1;
    }
    args_cons->buffer = buffer;
    args_cons->M = M;
    if (pthread_create(&tids[i + 1], NULL, consumidora, (void *)args_cons) !=
        0) {
      fprintf(stderr, "Erro durante a criação das threads consumidoras.\n");
      return 1;
    }
  }

  // Join da thread produtora
  // Variável entradas para capturar o vetor gerado pela produtora
  if (pthread_join(tids[0], (void **)&entradas) != 0) {
    fprintf(stderr, "Erro na junção da thread produtora.\n");
    return 1;
  }

  // Join das threads consumidoras
  for (int i = 1; i < NTHREADS_CONS + 1; ++i) {
    int *qtd_primos;
    if (pthread_join(tids[i], (void **)&qtd_primos) != 0) {
      fprintf(stderr, "Erro na junção das threads consumidoras.\n");
      return 1;
    }
    qtd_primos_conc += *qtd_primos;
    LOG(stdout, "Thread %d consumiu %d primos.\n", i, *qtd_primos);
    if (*qtd_primos > qtd_primos_vencedora) {
      vencedora = i;
      qtd_primos_vencedora = *qtd_primos;
    }
    free(qtd_primos);
  }

  // Remoção dos semáforos
  sem_destroy(&mutex);
  sem_destroy(&vazio);
  sem_destroy(&cheio);

// Impressão dos resultados
// Comparação com o sequencial para corretude
#ifdef VERBOSE
  int qtd_primos_seq = 0;
  for (int i = 0; i < N; ++i)
    if (ehPrimo(entradas[i]))
      qtd_primos_seq++;
  printf("Quantidade total de primos (seq): %d\n", qtd_primos_seq);
#endif

  printf("Quantidade total de primos: %d\n", qtd_primos_conc);
  printf("Thread %d foi a vencedora com %d primos.\n", vencedora,
         qtd_primos_vencedora);

  // Liberar memória
  free(entradas);
  free(buffer);
  free(arg);
  free(tids);

  return 0;
}
