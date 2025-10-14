# Requisitos

Programa implementando o padrão produtor-consumidor com semáforos:

- 1 thread produtora gera N inteiros (aleatórios ou sequenciais)
- 4 threads consumidoras verificam primalidade dos números
- Canal/buffer compartilhado de tamanho M < N
- Sincronização via semáforos

## Compilação e Execução

Compilação manual:

```bash
gcc -Wall -Wextra -O2 -pthread Atividade\ 1.c -o atividade1 -lm
```

Execução com Makefile:

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

Os testes verificam se a contagem de primos concorrente corresponde à sequencial.

Características avaliadas:

| Comando | Intervalo | Primos Esperados |
|---------|-----------|------------------|
| `make run I=0 N=10000 M=500` | [0, 10000) | 1229 |
| `make run I=0 N=50000 M=1000` | [0, 50000) | 5133 |
| `make run I=0 N=100000 M=2000` | [0, 100000) | 9592 |

### Casos Especiais

**Buffer pequeno (teste de sincronização):**
```bash
make run I=0 N=1000 M=10  # Deve dar 168 primos
make run I=0 N=1000 M=1   # Buffer mínimo - 168 primos
```

Números aleatórios (não determinístico):

```bash
make run N=10000 M=500  # Verificar apenas se seq == concorrente
```

## Validação

O programa imprime três valores ao final:

- **Quantidade total de primos**: Resultado das threads consumidoras

- **Quantidade total de primos (seq)**: Verificação sequencial

- **Thread vencedora**: Thread que encontrou mais primos
