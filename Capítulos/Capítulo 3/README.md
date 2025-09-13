### Conceitos e Definições

**Sincronização por exclusão mútua**: Tipo de sincronização que visa garantir
que os trechos de código em cada thread que acessam objetos compartilhados não
sejam executados ao mesmo tempo, ou que uma vez iniciados sejam executados até
o fim sem que outra thread inicie a execução do trecho equivalente.

A solução para a exclusão mútua é definida agrupando sequências contínuas de ações atômicas de hardware em **seções críticas** de software.

**Seções críticas**: Trechos de código que acessam objetos compartilhados (por mais de um fluxo/fio de execução).

- O que fazer? Devem ser transformadas em ações atômicas de modo que sua
  execução não possa ocorrer concorrentemente com outra *seção crítica que
  referencia a mesma variável*.

Há duas abordagens básicas para implementar a sincronização por exclusão mútua:

1. Sincronização por espera ocupada: Thread fica continuamente testando o valor de uma determinada variável até que esse valor lhe permita executar a seção crítica com exclusividade.

Casos nos quais essa abordagem é válida:

    - Não há nada melhor para a CPU fazer enquanto espera.
    - O tempo de espera é menor que o tempo requerido para a troca de contexto entre as threads.

2. Sincronização por escalonamento (mais usual): A thread é bloqueada temporariamente enquanto a CPU é cedida a outra thread, evitando desperdício de recursos da CPU.

- 
