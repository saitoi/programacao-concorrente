
/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Comunicação entre threads usando variável compartilhada e exclusao mutua com bloqueio */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define ITER 100000
#define MULTIPLO 1000

long int soma = 0; //variavel compartilhada entre as threads
long int proximo_multiplo = MULTIPLO;
short int impresso = 1;
pthread_mutex_t mutex; //variavel de lock para exclusao mutua
pthread_cond_t cond_1, cond_2;

//funcao executada pelas threads
void *ExecutaTarefa (void *arg) {
  long int id = (long int) arg;
  printf("Thread : %ld esta executando...\n", id);

  for (int i=0; i<ITER; i++) {
     //--entrada na SC
     pthread_mutex_lock(&mutex);
     //--SC (seção critica)
     while (!impresso)
        pthread_cond_wait(&cond_2, &mutex);
     soma++; //incrementa a variavel compartilhada 
     if (soma == proximo_multiplo) {
        impresso = 0;
        pthread_cond_signal(&cond_1);
     }
     //--saida da SC
     pthread_mutex_unlock(&mutex);
  }
  printf("Thread : %ld terminou!\n", id);
  pthread_exit(NULL);
}

//funcao executada pela thread de log
void *extra (void *args) {
  long int max_iter = (long int) args;
  printf("Extra : esta executando...\n");

  pthread_mutex_lock(&mutex);
  while (proximo_multiplo < max_iter) {
     while (soma < proximo_multiplo) //imprime se 'soma' for multiplo de 1000
         pthread_cond_wait(&cond_1, &mutex);

     printf("soma = %ld \n", soma);
     impresso = 1;
     pthread_cond_broadcast(&cond_2);
     proximo_multiplo += MULTIPLO;
  }
  pthread_mutex_unlock(&mutex);

  printf("Extra : terminou!\n");
  pthread_exit(NULL);
}

//fluxo principal
int main(int argc, char *argv[]) {
   pthread_t *tid; //identificadores das threads no sistema
   long int nthreads; //qtde de threads (passada linha de comando)

   //--le e avalia os parametros de entrada
   if(argc<2) {
      printf("Digite: %s <numero de threads>\n", argv[0]);
      return 1;
   }
   nthreads = (long int) atoi(argv[1]);

   //--aloca as estruturas
   tid = (pthread_t*) malloc(sizeof(pthread_t)*(nthreads+1));
   if(tid==NULL) {puts("ERRO--malloc"); return 2;}

   //--inicilaiza o mutex (lock de exclusao mutua)
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&cond_1, NULL);
   pthread_cond_init(&cond_2, NULL);

   //--cria as threads
   // Cria nthreads de ExecutaTarefa
   for(long int t=0; t<nthreads; t++) {
     if (pthread_create(&tid[t], NULL, ExecutaTarefa, (void *)t)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
     }
   }

   //--cria uma thread de log
   if (pthread_create(&tid[nthreads], NULL, extra, (void*) (ITER * nthreads))) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
   }

   //--espera todas as threads terminarem
   for (int t=0; t<(nthreads + 1); t++) {
     if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
     } 
   } 

   //--finaliza o mutex
   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond_1);
   pthread_cond_destroy(&cond_2);
   
   printf("Valor de 'soma' = %ld\n", soma);

   return 0;
}
