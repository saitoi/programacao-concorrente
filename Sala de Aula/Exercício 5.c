// Corrigindo implementação da barreira para o caso geral
// de mais de uma chamada da barreira na aplicação

sem_t mutex; //exclusao mutua (iniciado com 1)
sem_t cond; //condicional (iniciado com 0)
sem_t cond_sair; // semaforo (iniciado com N-1)

void barreira(int numThreads) {
    static int chegaram = 0;
    static int sairam = 0;
    sem_wait(&mutex);
    chegaram++;
    if (chegaram < numThreads) {

      // Mudança aqui (
      sem_post(&mutex);
      sem_wait(&cond_sair);
      // )

      sem_wait(&cond);

      // Mudança aqui (
      sem_wait(&mutex);
      sairam++;
      if (sairam == (numThreads-1)) // A última reseta cond_sair para numThreads-1
          for (int i = 1; i < numThreads; ++i)
              sem_post(&cond_sair);
      sem_pos(&mutex);
      // )

    } else {
      for(int i=1; i<numThreads; i++)
         { sem_post(&cond); }
      chegaram = 0;
      // Mudança aqui (
      sairam = 0;
      // )
      sem_post(&mutex);
    }
}
