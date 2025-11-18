JAVAC = javac
JAVA  = java
SEQ   = QuantosPrimosSeq
CONC  = FuturePool
N     = 50

TESTS = -100 -50 -1 0 10 20 30 50 75 100 123 150 189 200 231 250 289 300 333 350 355 400 450 500 550 999 1000 1890 10000 12399 100000 109089 1000000 1959823 10000000

GREEN = $(shell tput setaf 2)
RED = $(shell tput setaf 1)
RESET = $(shell tput sgr0)

all:
	$(JAVAC) $(SEQ).java
	$(JAVAC) $(CONC).java

run-seq:
	$(JAVA) $(SEQ) $(N)

run:
	$(JAVA) $(CONC) $(N)

test: all
	@for N in $(TESTS) ; do \
		echo -n "Testando N=$$N..."; \
		$(JAVA) $(SEQ)  $$N | grep -E '^[0-9]+$$' | sort -n | uniq > seq.out; \
		$(JAVA) $(CONC) $$N | grep -E '^[0-9]+$$' | sort -n | uniq > conc.out; \
		if diff -q seq.out conc.out >/dev/null ; then \
			echo "$(GREEN)OK: Primos iguais N=$$N$(RESET)"; \
		else \
			echo "$(RED)FALHA para N=$$N$(RESET)"; \
			diff -y --width=120 seq.out conc.out; \
			exit 1; \
		fi; \
	done
	@echo "$(GREEN)Todos os testes passaram!$(RESET)"


clean:
	rm -f *.class seq.out conc.out
