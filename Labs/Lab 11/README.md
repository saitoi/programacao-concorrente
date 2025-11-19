# Lab 11 - Pool de Threads em Java

## Atividade 1

Implementação de um pool de threads customizado. Verifica números primos até N usando fila de
tarefas FIFO.

### Execução:

```bash
cd atividade1/
make && make run N=100 NTHR=16 # default: 50, 10
# ou simplesmente: javac MyPool.java && java MyPool <inteiro>
```

#### Observação

Neste exercício, optei por exibir somente os primos encontrados no intervalo
[1-N]. O programa verifica todos os inteiros dentro do intervalo, porém exibe
apenas os primos para facilitar a comparação com o programa sequencial.

## Atividade 3

Uso de API de alto nível do Java (ExecutorService, Callable, Future) para contar quantos números primos existem até N.

### Execução:

```bash
cd atividade3/
make && make run N=200 NTHR=16 # default: 50, 10
# ou simplesmente: javac FuturePool.java && java FuturePool <inteiro>
```

## Makefile

Cada atividade possui seu próprio Makefile (`atividade1/Makefile` e
`atividade3/Makefile`) com comandos para compilar, limpar, executar e testar a corretude do código.

Para avaliar a corretude execute: `make test`.
Esse comando compara a saída dos programa entre si para cada iteração.

## Saídas

O resultado do teste de corretude por extenso pode ser encontrado em `results/`. Por outro lado, o resultado resumido obtido quando executa `make test` está descrito abaixo:

<table>
  <tr>
    <td>
        root@saitoi-droplet:~/repos/programacao-concorrente/Labs/Lab 11/atividade1# make test<br>
        javac PrimoSequencial.java<br>
        javac MyPool.java<br>
        Testando com 1 threads<br>
          N=-100, NTHREADS=1...OK<br>
          N=-50, NTHREADS=1...OK<br>
          N=-1, NTHREADS=1...OK<br>
          N=0, NTHREADS=1...OK<br>
          N=10, NTHREADS=1...OK<br>
          N=20, NTHREADS=1...OK<br>
          N=30, NTHREADS=1...OK<br>
          N=50, NTHREADS=1...OK<br>
          N=75, NTHREADS=1...OK<br>
          N=100, NTHREADS=1...OK<br>
          N=150, NTHREADS=1...OK<br>
          N=200, NTHREADS=1...OK<br>
          N=250, NTHREADS=1...OK<br>
          N=300, NTHREADS=1...OK<br>
          N=350, NTHREADS=1...OK<br>
          N=400, NTHREADS=1...OK<br>
          N=450, NTHREADS=1...OK<br>
          N=500, NTHREADS=1...OK<br>
          N=550, NTHREADS=1...OK<br>
          N=1000, NTHREADS=1...OK<br>
          N=10000, NTHREADS=1...OK<br>
          N=100000, NTHREADS=1...OK<br>
          N=1000000, NTHREADS=1...OK<br>
          N=10000000, NTHREADS=1...OK<br>
        Testando com 2 threads<br>
          N=-100, NTHREADS=2...OK<br>
          N=-50, NTHREADS=2...OK<br>
          N=-1, NTHREADS=2...OK<br>
          N=0, NTHREADS=2...OK<br>
          N=10, NTHREADS=2...OK<br>
          N=20, NTHREADS=2...OK<br>
          N=30, NTHREADS=2...OK<br>
          N=50, NTHREADS=2...OK<br>
          N=75, NTHREADS=2...OK<br>
          N=100, NTHREADS=2...OK<br>
          N=150, NTHREADS=2...OK<br>
          N=200, NTHREADS=2...OK<br>
          N=250, NTHREADS=2...OK<br>
          N=300, NTHREADS=2...OK<br>
          N=350, NTHREADS=2...OK<br>
          N=400, NTHREADS=2...OK<br>
          N=450, NTHREADS=2...OK<br>
          N=500, NTHREADS=2...OK<br>
          N=550, NTHREADS=2...OK<br>
          N=1000, NTHREADS=2...OK<br>
          N=10000, NTHREADS=2...OK<br>
          N=100000, NTHREADS=2...OK<br>
          N=1000000, NTHREADS=2...OK<br>
          N=10000000, NTHREADS=2...OK<br>
        Testando com 4 threads<br>
          N=-100, NTHREADS=4...OK<br>
          N=-50, NTHREADS=4...OK<br>
          N=-1, NTHREADS=4...OK<br>
          N=0, NTHREADS=4...OK<br>
          N=10, NTHREADS=4...OK<br>
          N=20, NTHREADS=4...OK<br>
          N=30, NTHREADS=4...OK<br>
          N=50, NTHREADS=4...OK<br>
          N=75, NTHREADS=4...OK<br>
          N=100, NTHREADS=4...OK<br>
          N=150, NTHREADS=4...OK<br>
          N=200, NTHREADS=4...OK<br>
          N=250, NTHREADS=4...OK<br>
          N=300, NTHREADS=4...OK<br>
          N=350, NTHREADS=4...OK<br>
          N=400, NTHREADS=4...OK<br>
          N=450, NTHREADS=4...OK<br>
          N=500, NTHREADS=4...OK<br>
          N=550, NTHREADS=4...OK<br>
          N=1000, NTHREADS=4...OK<br>
          N=10000, NTHREADS=4...OK<br>
          N=100000, NTHREADS=4...OK<br>
          N=1000000, NTHREADS=4...OK<br>
          N=10000000, NTHREADS=4...OK<br>
        Testando com 6 threads<br>
          N=-100, NTHREADS=6...OK<br>
          N=-50, NTHREADS=6...OK<br>
          N=-1, NTHREADS=6...OK<br>
          N=0, NTHREADS=6...OK<br>
          N=10, NTHREADS=6...OK<br>
          N=20, NTHREADS=6...OK<br>
          N=30, NTHREADS=6...OK<br>
          N=50, NTHREADS=6...OK<br>
          N=75, NTHREADS=6...OK<br>
          N=100, NTHREADS=6...OK<br>
          N=150, NTHREADS=6...OK<br>
          N=200, NTHREADS=6...OK<br>
          N=250, NTHREADS=6...OK<br>
          N=300, NTHREADS=6...OK<br>
          N=350, NTHREADS=6...OK<br>
          N=400, NTHREADS=6...OK<br>
          N=450, NTHREADS=6...OK<br>
          N=500, NTHREADS=6...OK<br>
          N=550, NTHREADS=6...OK<br>
          N=1000, NTHREADS=6...OK<br>
          N=10000, NTHREADS=6...OK<br>
          N=100000, NTHREADS=6...OK<br>
          N=1000000, NTHREADS=6...OK<br>
          N=10000000, NTHREADS=6...OK<br>
        Testando com 8 threads<br>
          N=-100, NTHREADS=8...OK<br>
          N=-50, NTHREADS=8...OK<br>
          N=-1, NTHREADS=8...OK<br>
          N=0, NTHREADS=8...OK<br>
          N=10, NTHREADS=8...OK<br>
          N=20, NTHREADS=8...OK<br>
          N=30, NTHREADS=8...OK<br>
          N=50, NTHREADS=8...OK<br>
          N=75, NTHREADS=8...OK<br>
          N=100, NTHREADS=8...OK<br>
          N=150, NTHREADS=8...OK<br>
          N=200, NTHREADS=8...OK<br>
          N=250, NTHREADS=8...OK<br>
          N=300, NTHREADS=8...OK<br>
          N=350, NTHREADS=8...OK<br>
          N=400, NTHREADS=8...OK<br>
          N=450, NTHREADS=8...OK<br>
          N=500, NTHREADS=8...OK<br>
          N=550, NTHREADS=8...OK<br>
          N=1000, NTHREADS=8...OK<br>
          N=10000, NTHREADS=8...OK<br>
          N=100000, NTHREADS=8...OK<br>
          N=1000000, NTHREADS=8...OK<br>
          N=10000000, NTHREADS=8...OK<br>
        Testando com 16 threads<br>
          N=-100, NTHREADS=16...OK<br>
          N=-50, NTHREADS=16...OK<br>
          N=-1, NTHREADS=16...OK<br>
          N=0, NTHREADS=16...OK<br>
          N=10, NTHREADS=16...OK<br>
          N=20, NTHREADS=16...OK<br>
          N=30, NTHREADS=16...OK<br>
          N=50, NTHREADS=16...OK<br>
          N=75, NTHREADS=16...OK<br>
          N=100, NTHREADS=16...OK<br>
          N=150, NTHREADS=16...OK<br>
          N=200, NTHREADS=16...OK<br>
          N=250, NTHREADS=16...OK<br>
          N=300, NTHREADS=16...OK<br>
          N=350, NTHREADS=16...OK<br>
          N=400, NTHREADS=16...OK<br>
          N=450, NTHREADS=16...OK<br>
          N=500, NTHREADS=16...OK<br>
          N=550, NTHREADS=16...OK<br>
          N=1000, NTHREADS=16...OK<br>
          N=10000, NTHREADS=16...OK<br>
          N=100000, NTHREADS=16...OK<br>
          N=1000000, NTHREADS=16...OK<br>
          N=10000000, NTHREADS=16...OK<br>
        Testando com 32 threads<br>
          N=-100, NTHREADS=32...OK<br>
          N=-50, NTHREADS=32...OK<br>
          N=-1, NTHREADS=32...OK<br>
          N=0, NTHREADS=32...OK<br>
          N=10, NTHREADS=32...OK<br>
          N=20, NTHREADS=32...OK<br>
          N=30, NTHREADS=32...OK<br>
          N=50, NTHREADS=32...OK<br>
          N=75, NTHREADS=32...OK<br>
          N=100, NTHREADS=32...OK<br>
          N=150, NTHREADS=32...OK<br>
          N=200, NTHREADS=32...OK<br>
          N=250, NTHREADS=32...OK<br>
          N=300, NTHREADS=32...OK<br>
          N=350, NTHREADS=32...OK<br>
          N=400, NTHREADS=32...OK<br>
          N=450, NTHREADS=32...OK<br>
          N=500, NTHREADS=32...OK<br>
          N=550, NTHREADS=32...OK<br>
          N=1000, NTHREADS=32...OK<br>
          N=10000, NTHREADS=32...OK<br>
          N=100000, NTHREADS=32...OK<br>
          N=1000000, NTHREADS=32...OK<br>
          N=10000000, NTHREADS=32...OK<br>
        Todos os testes passaram!<br>
    </td>
    <td>
    root@saitoi-droplet:~/repos/programacao-concorrente/Labs/Lab 11/atividade3# make test<br>
    javac QuantosPrimosSeq.java<br>
    javac FuturePool.java<br>
    Testando com 1 threads<br>
      N=-100, NTHREADS=1...OK<br>
      N=-50, NTHREADS=1...OK<br>
      N=-1, NTHREADS=1...OK<br>
      N=0, NTHREADS=1...OK<br>
      N=10, NTHREADS=1...OK<br>
      N=20, NTHREADS=1...OK<br>
      N=30, NTHREADS=1...OK<br>
      N=50, NTHREADS=1...OK<br>
      N=75, NTHREADS=1...OK<br>
      N=100, NTHREADS=1...OK<br>
      N=123, NTHREADS=1...OK<br>
      N=150, NTHREADS=1...OK<br>
      N=189, NTHREADS=1...OK<br>
      N=200, NTHREADS=1...OK<br>
      N=231, NTHREADS=1...OK<br>
      N=250, NTHREADS=1...OK<br>
      N=289, NTHREADS=1...OK<br>
      N=300, NTHREADS=1...OK<br>
      N=333, NTHREADS=1...OK<br>
      N=350, NTHREADS=1...OK<br>
      N=355, NTHREADS=1...OK<br>
      N=400, NTHREADS=1...OK<br>
      N=450, NTHREADS=1...OK<br>
      N=500, NTHREADS=1...OK<br>
      N=550, NTHREADS=1...OK<br>
      N=999, NTHREADS=1...OK<br>
      N=1000, NTHREADS=1...OK<br>
      N=1890, NTHREADS=1...OK<br>
      N=10000, NTHREADS=1...OK<br>
      N=12399, NTHREADS=1...OK<br>
      N=100000, NTHREADS=1...OK<br>
      N=109089, NTHREADS=1...OK<br>
      N=1000000, NTHREADS=1...OK<br>
      N=1959823, NTHREADS=1...OK<br>
      N=10000000, NTHREADS=1...OK<br>
    Testando com 2 threads<br>
      N=-100, NTHREADS=2...OK<br>
      N=-50, NTHREADS=2...OK<br>
      N=-1, NTHREADS=2...OK<br>
      N=0, NTHREADS=2...OK<br>
      N=10, NTHREADS=2...OK<br>
      N=20, NTHREADS=2...OK<br>
      N=30, NTHREADS=2...OK<br>
      N=50, NTHREADS=2...OK<br>
      N=75, NTHREADS=2...OK<br>
      N=100, NTHREADS=2...OK<br>
      N=123, NTHREADS=2...OK<br>
      N=150, NTHREADS=2...OK<br>
      N=189, NTHREADS=2...OK<br>
      N=200, NTHREADS=2...OK<br>
      N=231, NTHREADS=2...OK<br>
      N=250, NTHREADS=2...OK<br>
      N=289, NTHREADS=2...OK<br>
      N=300, NTHREADS=2...OK<br>
      N=333, NTHREADS=2...OK<br>
      N=350, NTHREADS=2...OK<br>
      N=355, NTHREADS=2...OK<br>
      N=400, NTHREADS=2...OK<br>
      N=450, NTHREADS=2...OK<br>
      N=500, NTHREADS=2...OK<br>
      N=550, NTHREADS=2...OK<br>
      N=999, NTHREADS=2...OK<br>
      N=1000, NTHREADS=2...OK<br>
      N=1890, NTHREADS=2...OK<br>
      N=10000, NTHREADS=2...OK<br>
      N=12399, NTHREADS=2...OK<br>
      N=100000, NTHREADS=2...OK<br>
      N=109089, NTHREADS=2...OK<br>
      N=1000000, NTHREADS=2...OK<br>
      N=1959823, NTHREADS=2...OK<br>
      N=10000000, NTHREADS=2...OK<br>
    Testando com 4 threads<br>
      N=-100, NTHREADS=4...OK<br>
      N=-50, NTHREADS=4...OK<br>
      N=-1, NTHREADS=4...OK<br>
      N=0, NTHREADS=4...OK<br>
      N=10, NTHREADS=4...OK<br>
      N=20, NTHREADS=4...OK<br>
      N=30, NTHREADS=4...OK<br>
      N=50, NTHREADS=4...OK<br>
      N=75, NTHREADS=4...OK<br>
      N=100, NTHREADS=4...OK<br>
      N=123, NTHREADS=4...OK<br>
      N=150, NTHREADS=4...OK<br>
      N=189, NTHREADS=4...OK<br>
      N=200, NTHREADS=4...OK<br>
      N=231, NTHREADS=4...OK<br>
      N=250, NTHREADS=4...OK<br>
      N=289, NTHREADS=4...OK<br>
      N=300, NTHREADS=4...OK<br>
      N=333, NTHREADS=4...OK<br>
      N=350, NTHREADS=4...OK<br>
      N=355, NTHREADS=4...OK<br>
      N=400, NTHREADS=4...OK<br>
      N=450, NTHREADS=4...OK<br>
      N=500, NTHREADS=4...OK<br>
      N=550, NTHREADS=4...OK<br>
      N=999, NTHREADS=4...OK<br>
      N=1000, NTHREADS=4...OK<br>
      N=1890, NTHREADS=4...OK<br>
      N=10000, NTHREADS=4...OK<br>
      N=12399, NTHREADS=4...OK<br>
      N=100000, NTHREADS=4...OK<br>
      N=109089, NTHREADS=4...OK<br>
      N=1000000, NTHREADS=4...OK<br>
      N=1959823, NTHREADS=4...OK<br>
      N=10000000, NTHREADS=4...OK<br>
    Testando com 6 threads<br>
      N=-100, NTHREADS=6...OK<br>
      N=-50, NTHREADS=6...OK<br>
      N=-1, NTHREADS=6...OK<br>
      N=0, NTHREADS=6...OK<br>
      N=10, NTHREADS=6...OK<br>
      N=20, NTHREADS=6...OK<br>
      N=30, NTHREADS=6...OK<br>
      N=50, NTHREADS=6...OK<br>
      N=75, NTHREADS=6...OK<br>
      N=100, NTHREADS=6...OK<br>
      N=123, NTHREADS=6...OK<br>
      N=150, NTHREADS=6...OK<br>
      N=189, NTHREADS=6...OK<br>
      N=200, NTHREADS=6...OK<br>
      N=231, NTHREADS=6...OK<br>
      N=250, NTHREADS=6...OK<br>
      N=289, NTHREADS=6...OK<br>
      N=300, NTHREADS=6...OK<br>
      N=333, NTHREADS=6...OK<br>
      N=350, NTHREADS=6...OK<br>
      N=355, NTHREADS=6...OK<br>
      N=400, NTHREADS=6...OK<br>
      N=450, NTHREADS=6...OK<br>
      N=500, NTHREADS=6...OK<br>
      N=550, NTHREADS=6...OK<br>
      N=999, NTHREADS=6...OK<br>
      N=1000, NTHREADS=6...OK<br>
      N=1890, NTHREADS=6...OK<br>
      N=10000, NTHREADS=6...OK<br>
      N=12399, NTHREADS=6...OK<br>
      N=100000, NTHREADS=6...OK<br>
      N=109089, NTHREADS=6...OK<br>
      N=1000000, NTHREADS=6...OK<br>
      N=1959823, NTHREADS=6...OK<br>
      N=10000000, NTHREADS=6...OK<br>
    Testando com 8 threads<br>
      N=-100, NTHREADS=8...OK<br>
      N=-50, NTHREADS=8...OK<br>
      N=-1, NTHREADS=8...OK<br>
      N=0, NTHREADS=8...OK<br>
      N=10, NTHREADS=8...OK<br>
      N=20, NTHREADS=8...OK<br>
      N=30, NTHREADS=8...OK<br>
      N=50, NTHREADS=8...OK<br>
      N=75, NTHREADS=8...OK<br>
      N=100, NTHREADS=8...OK<br>
      N=123, NTHREADS=8...OK<br>
      N=150, NTHREADS=8...OK<br>
      N=189, NTHREADS=8...OK<br>
      N=200, NTHREADS=8...OK<br>
      N=231, NTHREADS=8...OK<br>
      N=250, NTHREADS=8...OK<br>
      N=289, NTHREADS=8...OK<br>
      N=300, NTHREADS=8...OK<br>
      N=333, NTHREADS=8...OK<br>
      N=350, NTHREADS=8...OK<br>
      N=355, NTHREADS=8...OK<br>
      N=400, NTHREADS=8...OK<br>
      N=450, NTHREADS=8...OK<br>
      N=500, NTHREADS=8...OK<br>
      N=550, NTHREADS=8...OK<br>
      N=999, NTHREADS=8...OK<br>
      N=1000, NTHREADS=8...OK<br>
      N=1890, NTHREADS=8...OK<br>
      N=10000, NTHREADS=8...OK<br>
      N=12399, NTHREADS=8...OK<br>
      N=100000, NTHREADS=8...OK<br>
      N=109089, NTHREADS=8...OK<br>
      N=1000000, NTHREADS=8...OK<br>
      N=1959823, NTHREADS=8...OK<br>
      N=10000000, NTHREADS=8...OK<br>
    Testando com 16 threads<br>
      N=-100, NTHREADS=16...OK<br>
      N=-50, NTHREADS=16...OK<br>
      N=-1, NTHREADS=16...OK<br>
      N=0, NTHREADS=16...OK<br>
      N=10, NTHREADS=16...OK<br>
      N=20, NTHREADS=16...OK<br>
      N=30, NTHREADS=16...OK<br>
      N=50, NTHREADS=16...OK<br>
      N=75, NTHREADS=16...OK<br>
      N=100, NTHREADS=16...OK<br>
      N=123, NTHREADS=16...OK<br>
      N=150, NTHREADS=16...OK<br>
      N=189, NTHREADS=16...OK<br>
      N=200, NTHREADS=16...OK<br>
      N=231, NTHREADS=16...OK<br>
      N=250, NTHREADS=16...OK<br>
      N=289, NTHREADS=16...OK<br>
      N=300, NTHREADS=16...OK<br>
      N=333, NTHREADS=16...OK<br>
      N=350, NTHREADS=16...OK<br>
      N=355, NTHREADS=16...OK<br>
      N=400, NTHREADS=16...OK<br>
      N=450, NTHREADS=16...OK<br>
      N=500, NTHREADS=16...OK<br>
      N=550, NTHREADS=16...OK<br>
      N=999, NTHREADS=16...OK<br>
      N=1000, NTHREADS=16...OK<br>
      N=1890, NTHREADS=16...OK<br>
      N=10000, NTHREADS=16...OK<br>
      N=12399, NTHREADS=16...OK<br>
      N=100000, NTHREADS=16...OK<br>
      N=109089, NTHREADS=16...OK<br>
      N=1000000, NTHREADS=16...OK<br>
      N=1959823, NTHREADS=16...OK<br>
      N=10000000, NTHREADS=16...OK<br>
  Testando com 32 threads<br>
      N=-100, NTHREADS=32...OK<br>
      N=-50, NTHREADS=32...OK<br>
      N=-1, NTHREADS=32...OK<br>
      N=0, NTHREADS=32...OK<br>
      N=10, NTHREADS=32...OK<br>
      N=20, NTHREADS=32...OK<br>
      N=30, NTHREADS=32...OK<br>
      N=50, NTHREADS=32...OK<br>
      N=75, NTHREADS=32...OK<br>
      N=100, NTHREADS=32...OK<br>
      N=123, NTHREADS=32...OK<br>
      N=150, NTHREADS=32...OK<br>
      N=189, NTHREADS=32...OK<br>
      N=200, NTHREADS=32...OK<br>
      N=231, NTHREADS=32...OK<br>
      N=250, NTHREADS=32...OK<br>
      N=289, NTHREADS=32...OK<br>
      N=300, NTHREADS=32...OK<br>
      N=333, NTHREADS=32...OK<br>
      N=350, NTHREADS=32...OK<br>
      N=355, NTHREADS=32...OK<br>
      N=400, NTHREADS=32...OK<br>
      N=450, NTHREADS=32...OK<br>
      N=500, NTHREADS=32...OK<br>
      N=550, NTHREADS=32...OK<br>
      N=999, NTHREADS=32...OK<br>
      N=1000, NTHREADS=32...OK<br>
      N=1890, NTHREADS=32...OK<br>
      N=10000, NTHREADS=32...OK<br>
      N=12399, NTHREADS=32...OK<br>
      N=100000, NTHREADS=32...OK<br>
      N=109089, NTHREADS=32...OK<br>
      N=1000000, NTHREADS=32...OK<br>
      N=1959823, NTHREADS=32...OK<br>
      N=10000000, NTHREADS=32...OK<br>
  Todos os testes passaram!<br>
  </td>
  </tr>
</table>
