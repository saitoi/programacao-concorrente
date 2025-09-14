CC = gcc
CFLAGS = -Wall -Wextra -O2

SEQ_SRC = Atividade\ 4\ -\ Seq.c
CONC_SRC = Atividade\ 4.c

SEQ_BIN = seq
CONC_BIN = conc

# Defaults (podem ser sobrescritos: make run N=100000 T=8)
N ?= 1000
T ?= 4

.PHONY: all run run-seq run-conc clean

all: $(SEQ_BIN) $(CONC_BIN)

$(SEQ_BIN): $(SEQ_SRC)
	$(CC) $(CFLAGS) -o $@ $(SEQ_SRC)

$(CONC_BIN): $(CONC_SRC)
	$(CC) $(CFLAGS) -pthread -o $@ $(CONC_SRC)

run: $(SEQ_BIN) $(CONC_BIN)
	./$(SEQ_BIN) $(N)
	./$(CONC_BIN) $(T) $(N)

run-seq: $(SEQ_BIN)
	./$(SEQ_BIN) $(N)

run-conc: $(CONC_BIN)
	./$(CONC_BIN) $(T) $(N)

clean:
	rm -f $(SEQ_BIN) $(CONC_BIN)
