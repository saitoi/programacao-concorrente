JAVAC = javac
JAVA  = java
SEQ   = PrimoSequencial
CONC  = MyPool
N     = 50

TESTS = -100 -50 -1 0 10 20 30 50 75 100 150 200 250 300 350 400 450 500 550 1000 10000 100000 1000000 10000000

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
		fi; \
	done
	@echo "$(GREEN)Todos os testes passaram!$(RESET)"


clean:
	rm -f *.class seq.out conc.out
