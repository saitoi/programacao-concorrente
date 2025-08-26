prefixo        ?= ex
numero_testes  ?= 5
dimensao_vetor ?= 100
numero_threads ?= 4

ifeq ($(numero_testes),0)
$(error numero_testes é zero, abortando..)
endif

CC     := gcc
CFLAGS := -Wall -Wextra -pedantic
dir    := tst_bin
out    := results.txt

all: run

tt: gerar_casos_teste.c
	$(CC) $(CFLAGS) -o $@ $<

gg: exercicio_1.c
	$(CC) $(CFLAGS) -o $@ $<

run: tt gg
	mkdir -p $(dir)
	rm -f $(out)
	for i in $$(seq 1 $(numero_testes)); do \
		./tt $(dimensao_vetor) $(dir)/$(prefixo)_$$i >> $(out) || echo "Erro gerando vetores para $$i"; \
		./gg $(numero_threads) $(dir)/$(prefixo)_$$i >> $(out) || echo "Erro executando programa concorrente para $$i"; \
	done

clean:
	rm -rf $(dir) $(out) tt gg
