# Respostas das Questões Teóricas

### Questão 3

**Enunciado**: O que é seção crítica do código em um programa concorrente?

R minha: Trecho do código fonte no qual uma variável é acessada por múltiplos
fluxos de execução simultaneamente.

R wikipedia: É uma área de código de um programa concorrente que acessa um
recurso compartilhado que não pode ser acedido concorrentemente por mais de uma
linha de execução. O objetivo é tornar a operação sobre o recurso compartilhado
atômica.

**Enunciado**: O que é corrida de dados em um programa concorrente?

R minha: Refere-se à situação na qual o resultado programa depende da ordem de
execução dos fluxos disparados pelo mesmo. Isso se deve à presença de regiões
críticas nas quais as linhas de execução acessam concorrentemente sem
estratégias de sincronização ou controle estabelecidas.

R GPT: É quando dois ou mais fluxos de execução acessam a mesma localização de
memória ao mesmo tempo, pelo menos um acesso é escrita, e não há ordem de
sincronização (“happens-before”) entre esses acessos—ou os acessos não são
atômicos. Nessa situação, o valor lido/escrito é indeterminado e o programa
pode se comportar de forma imprevisível.

    - Mais de um acesso simultaneo à mesma localização de memória.
    - Pelo menos um é de escrita (N acessos somente-leitura não interferem).
    - Não há: **Ordem de execução/Sincronização entre as threads** ou **acessos não são atômicos**.
    - Resultado: Valor lido/escrito é indeterminado e o programa é imprevisível.

R site: Ocorre quando uma thread acessa um objeto mutável enquanto outra thread
está escrevendo neste objeto (semelhante à definição do GPT).

Definição ainda mais formal: Um programa contém uma corrida de dados se existirem duas ações conflitantes em threads distintas, verificando-se:

    1. Pelo menos uma das ações é uma escrita na mesma localização de memória.
    2. As duas ações acessam exatamente o mesmo endereço de memória.
    3. Podem ocorrer concorrente ou simultaneamente, nenhuma ordenação entre elas é garantida.
    4. Pelo menos uma das ações não é atômica (ou não está protegida por sincronização adequada).

**Enunciado**: O que é **violação de atomicidade** em um programa concorrente?

R minha: Uma violação de atomicidade ocorre quando duas ou mais operações de
acesso à memória não respeitam a seriação esperada. Portanto, as operações que
**esperávamos** ser atômicas, acabam se entrelaçando entre si ao serem
executadas por mais de uma thread, de modo que o comportamento do programa é
inesperado.

**Enunciado**: O que é **violação de ordem (ou violação de condição lógica)**
em um programa concorrente?

R minha: Ocorre quando a ordem de execução desejada entre duas operações de
acessos à memória é invertida. A ordem correta das operações não é garantida no
tempo de execução por mais que exista uma ordem de precedência exigida.

**Enunciado**: Como funciona a sincronização por exclusão mútua?

R minha: 

### Questão 6

R minha: 

### Questão 7

R minha: Sim, é possível que o saldo da aplicação fique negativo. Considere o seguinte caso:

- Temos duas threads: T0 e T1;
- T0: deseja retirar 5 unidades.
- T0: Lê o saldo atual com lock e retorna 10.
- T1: Recupera o lock e realiza ambas operação leitura e retirada.
- T1: Lê o saldo atual com e retorna 10 assim como T0.
- T1: Retira uma quantia de 10, restando 0 unidades no saldo.
- T0: Recupera o lock e então retira as 5 unidades.
- Saldo final: `saldo == -5.0`.

### Questão 8

R minha: O código referente a essa questão consta aqui: `./Questao\ 8.c`.

### Questão 9



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

### Questão 11

(a). O que irá acontecer se as duas threads tentarem acessar a seção crítica ao mesmo tempo?

R minha: Apenas uma das threads irá ter acesso à seção crítica, pois a
sincronização depende da ordem de execução da instrução atômica de atribuição
`turno = ...`. Isto é, se ambas as threads forem disparadas simultaneamente,
aquela que executar a instrução na linha 4 por último dará direito para a outra
executar.

No entanto, a seriação dessas atribuição só é possível de ser determinada em
tempo de execução, ou seja, não sabemos a priori se a Thread 1 executará e
vice-versa. Assim que uma das threads sair da seção crítica, ela 'setará'
`querEntrar...=...` que, por sua vez, permitirá com que a outra Thread prossiga
com a execução.

(b). O que irá acontecer se uma das threads tentar acessar sozinha a seção
crítica por várias vezes seguidas? Ela sofrerá alguma forma de contenção nesse
caso?

R minha: O acesso à seção crítica é feito de forma intercalada entre as threads.

Suponha que a Thread 0 esteja acessando a seção crítica. Assim que ela sair da
SC, ela setará `querEntrar0=0` e isso terá como consequência a liberação Thread 1.
Assim que a Thread 1 atingir o `while`, ela terá setado `turno = 1` que continuará permitindo a execução da outra Thread e que terá como consequência o seu próprio bloqueio.

(c). O que acontecerá se uma thread tentar acessar a seção crítica quando a
outra thread já estiver acessando e esta mesma thread (a que está na seção
crítica), quando sair da seção crítica, tentar acessá-la novamente antes da
thread que está esperando ganhar a CPU novamente?

R minha: A própria Thread garante o seu próprio bloqueio por meio da definição da variável `turno`.

(d). O código proposto garante a exclusão mútua no acesso à seção crítica?

R minha: Sim, o código proposto garante a exclusão mútua e o acesso alternado e não simultaneo à SC.
 

