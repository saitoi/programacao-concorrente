JAVAC = javac
JAVA  = java
SEQ   = PrimoSequencial
CONC  = MyPool
N     = 50
NTHR  = 10

TESTS = -100 -50 -1 0 10 20 30 50 75 100 150 200 250 300 350 400 450 500 550 1000 10000 100000 1000000 10000000
NTHREADS = 1 2 4 6 8 16 32

GREEN = $(shell tput setaf 2)
RED = $(shell tput setaf 1)
RESET = $(shell tput sgr0)

all:
	$(JAVAC) $(SEQ).java
	$(JAVAC) $(CONC).java

run-seq:
	$(JAVA) $(SEQ) $(N)

run:
	$(JAVA) $(CONC) $(N) $(NTHR)

test: all
	@for NTHREAD in $(NTHREADS) ; do \
		echo "$(GREEN)Testando com $$NTHREAD threads$(RESET)"; \
		for N in $(TESTS) ; do \
			echo -n "  N=$$N, NTHREADS=$$NTHREAD..."; \
			$(JAVA) $(SEQ)  $$N | grep -E '^[0-9]+$$' | sort -n | uniq > seq.out; \
			$(JAVA) $(CONC) $$N $$NTHREAD | grep -E '^[0-9]+$$' | sort -n | uniq > conc.out; \
			if diff -q seq.out conc.out >/dev/null ; then \
				echo "$(GREEN)OK$(RESET)"; \
			else \
				echo "$(RED)FALHA para N=$$N, NTHREADS=$$NTHREAD$(RESET)"; \
				diff -y --width=120 seq.out conc.out; \
				exit 1; \
			fi; \
		done; \
	done
	@echo "$(GREEN)Todos os testes passaram!$(RESET)"


clean:
	rm -f *.class seq.out conc.out
