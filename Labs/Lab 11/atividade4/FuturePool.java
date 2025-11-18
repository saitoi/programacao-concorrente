/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 11 */
/* Codigo: Exemplo de uso de futures */
/* -------------------------------------------------------------------*/

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import java.util.ArrayList;
import java.util.List;

/* ******************* Classe Callable<Boolean> Primo ******************* */ 

class Primo implements Callable<Boolean> {
   int n;

   // Construtor
   public Primo(int n) {
      this.n = n;
   }

   @Override
   public Boolean call() {
       if (n <= 1) return false;
       if (n == 2) return true;
       if ((n % 2) == 0) return false;
       for (long i = 3; i < Math.sqrt(n) + 1; i += 2)
           if ((n % i) == 0)
               return false;
       return true;
   }
}

/* ******************* Classe FuturePool ******************* */ 

public class FuturePool  {
  private static final int NTHREADS = 10;

  public static void main(String[] args) {
    //cria um pool de threads (NTHREADS)
    ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
    //cria uma lista para armazenar referencias de chamadas assincronas
    List<Future<Boolean>> list = new ArrayList<Future<Boolean>>();
    // 
    int n;

    // Uso da linha de comando
    if (args.length != 1)
        throw new IllegalArgumentException("Uso: java MyPool <numero primo maximo: int>");

    // Parsing da entrada
    n = Integer.parseInt(args[0]);
    // Verifica se o número é válido, ie, maior que zero
    if (n < 1) {
        System.out.println("N deve ser maior que 1");
        System.exit(1);
    }

    for (int i = 1; i <= n; i++) {
      Callable<Boolean> worker = new Primo(i);
      /*submit() permite enviar tarefas Callable ou Runnable e obter um objeto Future para acompanhar o progresso e recuperar o resultado da tarefa
       */
      Future<Boolean> submit = executor.submit(worker);
      list.add(submit);
    }

    //pode fazer outras tarefas...

    //recupera os resultados e faz o somatório final
    long sum = 0;
    for (Future<Boolean> future : list) {
      try {
        if (future.get()) //bloqueia se a computação nao tiver terminado
            sum++;
      } catch (InterruptedException e) {
        e.printStackTrace();
      } catch (ExecutionException e) {
        e.printStackTrace();
      }
    }
    System.out.println("Quantidade de números primos encontrados: " + sum);
    executor.shutdown();
  }
}
