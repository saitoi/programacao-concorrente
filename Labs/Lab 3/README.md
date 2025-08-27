# Instruções

Se quiser usar o Makefile para gerar o `results.txt`, basta executar:

```bash
make clean && make numero_threads=4 dimensao_vetor=99900000 numero_testes=1 prefix=arq
```

# Análise das Execuções (5)

## Programa sequencial é mais eficiente (1 thread) 

Nesse caso, o programa concorrente é sequencial também.

Observação: A duração contabilizada é referente ao cálculo do produto interno somente.

##### Resultados para 1 threads, vetor de 9999999 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : 1651527923.82456016540527343750000000
- Resultado concorrente : 1651527923.82456016540527343750000000
- Duração (sequencial)  : 0.0373699665 s
- Duração (concorrente) : 0.0363638401 s
- Variação relativa     : 0.0000000000e+00

## Programa concorrente é mais eficiente (2 thread) 

##### Resultados para 2 threads, vetor de 50000000 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : 2174772995.22824001312255859375000000
- Resultado concorrente : 2174772995.22824001312255859375000000
- Duração (sequencial)  : 0.2204740047 s
- Duração (concorrente) : 0.0976269245 s
- Variação relativa     : 0.0000000000e+00

## Programa concorrente é mais eficiente (4 threads)

##### Resultados para 4 threads, vetor de 99900000 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : -7495859719.89456176757812500000000000
- Resultado concorrente : -7495859719.89456844329833984375000000
- Duração (sequencial)  : 0.4880499840 s
- Duração (concorrente) : 0.1234750748 s
- Variação relativa     : 8.9058766630e-16

## Programa concorrente é mais eficiente (8 threads)

##### Resultados para 8 threads, vetor de 12345678 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : 978725562.16634511947631835937500000
- Resultado concorrente : 978725562.16634500026702880859375000
- Duração (sequencial)  : 0.0432879925 s
- Duração (concorrente) : 0.0077121258 s
- Variação relativa     : 1.2180052730e-16

## Programa concorrente é mais eficiente (16 threads)

##### Resultados para 16 threads, vetor de 101010101 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : -3702962332.94008255004882812500000000
- Resultado concorrente : -3702962332.94007873535156250000000000
- Duração (sequencial)  : 0.4517450333 s
- Duração (concorrente) : 0.0974659920 s
- Variação relativa     : 1.0301744719e-15

## Resultados:

Os resultados abaixos foram calculados manualmente.

- Duração média (concorrente) : 0.0725287914 s
- Duração média (sequencial)  : 0.2481853962 s
- Diferente entre as durações : 0.1756566048 s
- Variação relativa média     : 4.0851253310e-16

