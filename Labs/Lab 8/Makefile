CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
LDFLAGS = -lm
TARGET = atividade1
SRC = Atividade\ 1.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET) 100 10

clean:
	rm -f $(TARGET)

.PHONY: all run clean
