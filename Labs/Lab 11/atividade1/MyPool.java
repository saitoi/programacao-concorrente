/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 11 */
/* Codigo: Criando um pool de threads em Java */

import java.util.LinkedList;

/* ******************* Classe FilaTarefas ******************* */ 

// Implementação da fila de tarefas (Runnable)
class FilaTarefas {
    private final int nThreads;                 // Número de threads na pool
    private final MyPoolThreads[] threads;      // Array de MyPoolThreads
    private final LinkedList<Runnable> queue;   // Fila de tarefas
    private boolean shutdown;                   // Encerramento da pool de threads (join)

    // Construtor
    public FilaTarefas(int nThreads) {
        this.shutdown = false;                  // Encerramento da pool de threads (join)
        this.nThreads = nThreads;               // Número de threads na pool
        queue = new LinkedList<Runnable>();     // Fila de tarefas
        threads = new MyPoolThreads[nThreads];  // Array de MyPoolThreads
        for (int i=0; i<nThreads; i++) {        // Inicialização das MyPoolThreads
            threads[i] = new MyPoolThreads();
            threads[i].start();
        } 
    }

    // Método para adicionar uma tarefa à fila (ordem FIFO).
    // Alguma thread notificada terá que executar a tarefa
    public void execute(Runnable r) {
        synchronized(queue) {
            if (this.shutdown) return;
            queue.addLast(r);
            queue.notify();
        }
    }
    
    // Método para encerrrar a fila de tarefas
    // Tarefas já adicionadas à fila são executadas.
    // Porém, não são mais aceitas novas tarefas (shutdown=true)
    public void shutdown() {
        synchronized(queue) {
            this.shutdown=true; // Garante que novas tarefas não sejam adicionadas
            queue.notifyAll();  // Notifica todas as threads prosseguir
        }
        for (int i=0; i<nThreads; i++) {
          try { threads[i].join(); } catch (InterruptedException e) { return; }
        }
    }

    // Implementação do comportamento das threads da pool
    // Cada thread "consome" as tarefas em ordem FIFO, conforme a ordem de chegada.
    private class MyPoolThreads extends Thread {
       public void run() {
        // Tarefa a ser executada
        Runnable r;    
         while (true) {
           synchronized(queue) {
            // Espera até que uma tarefa seja adicionada à fila
             while (queue.isEmpty() && (!shutdown)) {
               try { queue.wait(); }
               catch (InterruptedException ignored){}
             }
             // Encerramento das threads após shutdown. Tarefas recusadas => Fila vezia => Encerramento
             if (queue.isEmpty()) return;
             // Captura "primeira" tarefa da fila
             r = (Runnable) queue.removeFirst();
           }
           // Executa a tarefa
           try { r.run(); }
           catch (RuntimeException e) {}
         } 
       } 
    } 
}

/* ******************* Classe Runnable Primo ******************* */ 

class Primo implements Runnable {
   int n;

   public Primo(int n) {
      this.n = n;
   }

   @Override
   public void run() {
       if (this.ehPrimo(n))
           System.out.println(n);
   }
   
   private boolean ehPrimo(int n) {
       if (n <= 1) return false;
       if (n == 2) return true;
       if ((n % 2) == 0) return false;
       for (long i = 3; i < Math.sqrt(n) + 1; i += 2)
           if ((n % i) == 0)
               return false;
       return true;
   }
}

/* ******************* Classe MyPool ******************* */ 

class MyPool {
    private static final int NTHREADS = 10;

    public static void main (String[] args) {
      //--PASSO 2: cria o pool de threads
      FilaTarefas pool = new FilaTarefas(NTHREADS); 
      int n;

      // Uso da linha de comando
      if (args.length != 1)
          throw new IllegalArgumentException("Uso: java MyPool <numero primo maximo: int>");

      // Parsing da entrada
      n = Integer.parseInt(args[0]);
      // Verifica se o número é válido, ie, maior que zero
      if (n < 1) {
          System.out.println("Entrada deve ser maior que zero.");
          System.exit(1);
      }

      //--PASSO 3: dispara a execução dos objetos runnable usando o pool de threads
      System.out.println("Primos encontrados:");
      for (int i = 0; i < n; i++) {
        // final String m = "Hello da tarefa " + i;
        // Runnable hello = new Hello(m);
        // pool.execute(hello);
        Runnable primo = new Primo(i);
        pool.execute(primo);
      }

      //--PASSO 4: esperar pelo termino das threads
      pool.shutdown();
      System.out.println("Terminou");
   }
}
