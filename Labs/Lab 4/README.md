# Observações do Programa

### Arquivo `soma.c`

Porque esse programa exemplifica o problema de **corrida de dados**?

R: Por causa do acesso à variável global `soma` sem nenhuma forma de
sincronização. A variável `soma ` é compartilhada entre todas as threads, de
modo que cada thread executa a função `ExecutaTarefa` onde é feito: `soma++`.
