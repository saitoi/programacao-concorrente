# Respostas das Questões Teóricas

### Questão 3

**Enunciado**: O que é seção crítica do código em um programa concorrente?

R minha: Trecho do código fonte no qual uma variável é acessada por múltiplos fluxos de execução simultaneamente.

R wikipedia: É uma área de código de um programa concorrente que acessa um recurso compartilhado que não pode ser acedido concorrentemente por mais de uma linha de execução. O objetivo é tornar a operação sobre o recurso compartilhado atômica.

**Enunciado**: O que é corrida de dados em um programa concorrente?

R minha: Refere-se à situação na qual o resultado programa depende da ordem de execução dos fluxos disparados pelo mesmo. Isso se deve à presença de regiões críticas nas quais as linhas de execução acessam concorrentemente sem estratégias de sincronização ou controle estabelecidas.

R GPT: É quando dois ou mais fluxos de execução acessam a mesma localização de memória ao mesmo tempo, pelo menos um acesso é escrita, e não há ordem de sincronização (“happens-before”) entre esses acessos—ou os acessos não são atômicos. Nessa situação, o valor lido/escrito é indeterminado e o programa pode se comportar de forma imprevisível.

**Enunciado**: O que é violação de atomicidade em um programa concorrente?

R minha: 

### Questão 10

(a). O que aconteceu para ser impresso o valor 11?

R minha: A thread B não verificou se a condição continua válida ao acordar.

Imagine a seguinte situação:

- x = 9.
- Thread B está aguardando.
- Thread A_1 atualiza x, entra na condição e sinaliza a Thread B.
- Imediatamente, a Thread A_1 termina, libera o lock e a Thread A_2 'pega' o lock.
- Novamente, ela atualiza x, não entra na condição e libera o lock.
- Feito isso, a Thread B pega o lock e então imprime 'X=11'.

Não houve uma verificação adicional assim que a Thread B sai do loop e, portanto, a condição pode acabar não sendo satisfeita.

(b). Como o código pode ser corrigido para que essa situação não se repita?

R minha: Trocando o `if` por um `while` no código da Thread B. O código completo está em `Questao\ 10\ -\ b.c`.

(c). Reescreva os códigos das threads A e B para que B necessariamente imprima X quando seu valor for exatamente igual a 50.

R minha: O código completo está em `Questao\ 10\ -\ c.c`.



