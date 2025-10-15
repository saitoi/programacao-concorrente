# Requisitos

Programa implementando o padrão produtor-consumidor com semáforos:

- 1 thread produtora gera N inteiros (aleatórios ou sequenciais)
- 4 threads consumidoras verificam primalidade dos números
- Canal/buffer compartilhado de tamanho M < N
- Sincronização via semáforos

## Compilação e Execução

Compilação manual:

```bash
gcc -pthread -lm Atividade\ 1.c
./a.out 1000 10 0 # <Qtd. inteiros gerados> <Tam do canal> <inicio (intervalo sequencial)>
```

Execução com Makefile **(Preferencial)**:

```bash
make run
```

Parâmetros do Makefile:

| Parâmetro | Padrão | Descrição |
|-----------|--------|-----------|
| `N` | 100 | Quantidade de inteiros gerados pela thread produtora |
| `M` | 10 | Tamanho do buffer/canal (deve ser M < N) |
| `I` | -1 | Início do intervalo sequencial (-1 = aleatório) |
| `VERBOSE` | - | Ativa logs de debug (qualquer valor não vazio) |

### Exemplos de Uso

Executando o binário:

```bash
# Uso: ./a.out <N> <M> <inicio>
# Parâmetro <inicio> é opcional
./a.out 100 10
```

Inteiros gerados aleatoriamente:

```bash
make run
make run N=1000 M=50
```

Intervalo sequencial [0, 1.000):

```bash
make run I=0 N=1000 M=100
```

Intervalo sequencial [1.000, 2.000):

```bash
make run I=1000 N=1000 M=50
```

Com log por meio da flag de compilação VERBOSE:

```bash
make run VERBOSE=1
make run N=500 M=25 I=0 VERBOSE=1
```

## Casos de Teste de Corretude

A corretude do programa foi avaliada tendo como base o programa sequencial. O programa permite gerar um intervalo sequencial (ex. [0, 1.000.000] com N = 1.000.000) ou gerar inteiros aleatórios (padrão).

Para facilitar a avaliação da corretude, use a flag `-DVERBOSE` durante a compilação (ou `VERBOSE=1` no `make run`) para habilitar o log de cada thread e a execução do programa sequencial para comparação.

### Testes com intervalo sequencial (M = 5)

| Comando | Intervalo | Primos Obtidos |
|---------|-----------|----------------|
| `make run I=0 N=100 M=5` | [0, 99] | 25 |
| `make run I=0 N=1000 M=5` | [0, 999] | 168 |
| `make run I=0 N=10000 M=5` | [0, 9999] | 1229 |

### Testes com valores aleatórios

| Comando | Qtd. Inteiros | Primos Obtidos |
|---------|---------------|----------------|
| `make run N=1000000 M=10` | 1.000.000 | 167724 |
| `make run N=100000000 M=100` | 100.000.000 | 16782318 |

**Observação**: Nos testes com valores aleatórios, a quantidade de inteiros pode exceder bastante o tamanho do canal, testando a robustez da sincronização.

### Tratamento de erro

O programa valida se:
- A quantidade de inteiros gerados é maior que o tamanho do canal (M < N)
- Ambos os valores N e M são positivos

Exemplo de erro:

```bash
# Uso: ./atividade1 <N> <M> (<inicio> opcional)
./atividade1 10 100
Entrada de qtd. inteiros gerados ou o tamanho do canal são inválidos.
- Ambas as entradas devem ser positivas.
- O tamanho do canal deve ser estritamente menor que a qtd. de inteiros.
```



## Validação

O programa imprime ao final:

- **Quantidade total de primos**: Resultado das threads consumidoras (concorrente)

- **Quantidade total de primos (seq)**: Verificação sequencial para comparação

- **Thread vencedora**: Thread que encontrou mais primos, juntamente com o número de primos coletado por ela

Com a macro `VERBOSE` definida (via `VERBOSE=1` no `make run`), o programa também imprime:
- Log detalhado de cada thread durante a execução
- Quantidade de primos coletada individualmente por cada thread consumidora
- Execução completa do programa sequencial para comparação
