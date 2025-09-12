# Observações sobre o Programa

Arquivos de suporte: `list_int.c` e `list_int.h`
Contém a implementação das seguintes operações: 

- Inserção
- Impressão
- Pertencimento
- Remoção

A implementação por si não é **thread safe**.

Os arquivos abaixos fazem uso da estrutura de dados compartilhada de modo que:

- 98% das operações são de leitura.
- 1% é de escrita.
- 1% é de remoção.

### Primeiro arquivo: `error-main.c`

Descrição: Threads acessam diretamente e concorrentemente a estrutura de dados
sem qualquer proteção à problemas como exclusão mútua, violação de ordem

# Conceitos

Def Wiki pt-br. **Thread safety**: Conceito de programação de computadores
aplicável no contexto de programas multi-thread. Um trecho de código é dito
**thread-safe** se ele manipula estrutura de dados compartilhadas de forma que
garanta execução segura através de múltiplas threads simultaneamente.

Def Wiki en. **Thread safety**: Uma função é dita thread-safe quando pode ser
invocada ou acessada concorrentemente por múltiplas threads sem causar
comportamentos não definidos, condições de corrida ou corrupção de dados.

Wiki en. Para evitarmos **condições de corrida**, existem alguns tipos de abordagens:

- Reentrancia.
- Armazenamento local à thread.
- Objetos imutáveis.
- Exclusão mútua: Acesso a dados compartilhados é serializado por meio de mecanismos que garantem que apenas uma thread leia/grave os dados compartilhados a qualquer momento. Se usada indevidamente pode ocasionar em deadlocks, livelocks e escassez de recursos.
- Operações atômicas: Dados compartilhados são acessados por operações atômicas que não podem ocorrer simultaneamente ou serem interrompidas por outras threads.

Reentrancia (não usa recursos da programação concorrente): Quando uma subrotina pode ser executada
concorrentemente de forma segura. Para atender a essa qualidade a subrotina não
deve armazenar dados estáticos (dados globais) não constantes, nem com
endereços não constantes. Deve trabalhar somente com os dados fornecidos na
chamada da subrotina, bem como não deve depender de exclusão mútua para
recursos compartilhados/criados com modelo Singleton. As rotinas convocadas
pela reentrante original também devem ser reentrantes.
