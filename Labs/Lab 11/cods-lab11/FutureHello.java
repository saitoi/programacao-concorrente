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


//classe runnable
class MyCallable implements Callable<Long> {
  //construtor
  MyCallable() {}
 
  //método para execução
  public Long call() throws Exception {
    long s = 0;
    for (long i=1; i<=100; i++) {
      s++;
    }
    return s;
  }
}

class PrimeCallable implements Callable<Long> {
  long n, start, chunk;
  PrimeCallable(long n, long start, long chunk) {
    this.n = n;
    this.start = start;
    this.chunk = chunk;
  }
  public Long call() throws Exception {
    long sum = 0;
    for (long j = this.start; j < this.chunk + this.start; ++j) {
      if (j <= 1) continue;
      if (j == 2) { sum++; continue; }
      if ((j % 2) == 0) continue;
      boolean isPrime = true;
      for (long i = 3; i < Math.sqrt(j) + 1; i += 2) {
        if ((j % i) == 0) {
          isPrime = false;
          break;
        }
      }
      if (isPrime) sum++;
    }
    return sum;
  }
}

//classe do método main
public class FutureHello  {
  private static final int N = 100;
  private static final int NTHREADS = 10;

  public static void main(String[] args) {
    //cria um pool de threads (NTHREADS)
    ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
    //cria uma lista para armazenar referencias de chamadas assincronas
    List<Future<Long>> list = new ArrayList<Future<Long>>();

    long buf = N / NTHREADS;
    long res = N % NTHREADS;
    for (long i = 0; i < NTHREADS; i++) {
      long chunk = buf + (i < res ?  1 : 0);
      long start = buf * i + (i < res ? i : res);
      Callable<Long> worker = new PrimeCallable(i, start, chunk);
      /*submit() permite enviar tarefas Callable ou Runnable e obter um objeto Future para acompanhar o progresso e recuperar o resultado da tarefa
       */
      Future<Long> submit = executor.submit(worker);
      list.add(submit);
    }

    System.out.println(list.size());
    //pode fazer outras tarefas...

    //recupera os resultados e faz o somatório final
    long val = 0;
    long cval = 0;
    for (Future<Long> future : list) {
      try {
        cval = future.get(); //bloqueia se a computação nao tiver terminado
	val += cval;
	if (cval == 1) System.out.println(cval);
      } catch (InterruptedException e) {
        e.printStackTrace();
      } catch (ExecutionException e) {
        e.printStackTrace();
      }
    }
    System.out.println(val);
    executor.shutdown();
  }
}
