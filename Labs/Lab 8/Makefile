CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
LDFLAGS = -lm
TARGET = atividade1
SRC = Atividade\ 1.c

N ?= 100
M ?= 10

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET) $(N) $(M)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
