# Mudanças feita em `soma-lock-atom.c`

### Execução

```bash
gcc Atividade\ 5.c
./a.out
```

### Variáveis e Macros adicionadas

- Macro `ITER` (=100000) que especifica o número máximo de iterações.
- Macro `MULTIPLO` (=1000) que simplesmente armazena o múltiplo que deve ser impresso. Estamos interessados em múltiplos de 1.000 somente.
- Variável para sincronização por condição `cond_2` e renomeação da anterior para `cond_1`.
- Variável `long int` `proximo_multiplo`.
- Variável `short` `impressso` 'binária'.

### Objetivo das Variáveis Acrescentadas

- `ITER`: Número de iterações das threads ExecutaTarefa do programa original, apenas converti em uma macro.
- `MULTIPLO`: Como havia sido dito, especifica o múltiplo de interesse.
- `impresso`: Verificar se a soma (equivalente ao próximo múltiplo de 1.000) foi impressa ou não.
- `proximo_multiplo`: Condição no `while` para validar se a soma já alcançou o próximo múltiplo na thread de log. Também é usada para sinalizar a thread de log para acordar.
- `cond_2`: Condicional auxiliar para validar o retorno das Threads ExecutaTarefa, isto é, elas não podem retornam sem que tenha sido impresso o múltiplo de 1.000 atual.
 
### Outras Mudanças

- Substituição do `for` na thread `extra` pelo `while(proximo_multiplo < max_iter)` que apenas encerra quando o próximo múltiplo atingir o número máximo de iterações (=<número de threads ExecutaTarefa> * <ITER>).
- Colocar `while` em todos os `wait` + condição para impedir com que as threads acordem e o estado não seja o incorreto.
