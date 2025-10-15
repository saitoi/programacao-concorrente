CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
LDFLAGS = -lm
TARGET = atividade1
SRC = Atividade\ 1.c

N ?= 100
M ?= 10
I ?= -1
VERBOSE ?=

ifneq ($(VERBOSE),)
	CFLAGS += -DVERBOSE
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: clean $(TARGET)
	./$(TARGET) $(N) $(M) $(I)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
