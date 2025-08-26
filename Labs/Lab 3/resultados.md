# Análise das Execuções (5)

## Programa sequencial é mais eficiente (1 thread) 

Nesse caso, o programa concorrente é sequencial também.

Observação: A duração contabilizada é referente ao cálculo do produto interno somente.

##### Resultados para 1 threads, vetor de 9999999 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : 863371170.25526797771453857421875000
- Resultado concorrente : 863371140.29085052013397216796875000
- Duração (sequencial)  : 0.0376880169 s
- Duração (concorrente) : 0.0378429890 s
- Variação relativa     : 3.4706298392e-08

## Programa é mais eficiente (2 thread) 

##### Resultados para 2 threads, vetor de 50000000 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : 910542551.21956205368041992187500000
- Resultado concorrente : 910542506.52690923213958740234375000
- Duração (sequencial)  : 0.1769709587 s
- Duração (concorrente) : 0.0918409824 s
- Variação relativa     : 4.9083541194e-08

## Programa concorrente é mais eficiente (4 threads)

##### Resultados para 4 threads, vetor de 99900000 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : 222258253.64716321229934692382812500
- Resultado concorrente : 222258210.87690418958663940429687500
- Duração (sequencial)  : 0.3593559265 s
- Duração (concorrente) : 0.0980069637 s
- Variação relativa     : 1.9243496393e-07

## Programa concorrente é mais eficiente (16 threads)

##### Resultados para 8 threads, vetor de 12345678 dimensões, arquivo 'tst_bin/ex_1'

- Resultado sequencial  : 104793565.65728300809860229492187500
- Resultado concorrente : 104793571.36473536491394042968750000
- Duração (sequencial)  : 0.0444240570 s
- Duração (concorrente) : 0.0072591305 s
- Variação relativa     : 5.4463767131e-08

## Resultados:

Os resultados abaixos foram calculados manualmente.

- Duração média (concorrente) : 0.0587375164 s
- Duração média (sequencial)  : 0.1546097398 s
- Diferente entre as durações : 0.0958722234 s
- Variação relativa média     : 8.2672142662e-08

