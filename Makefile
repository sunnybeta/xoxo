CC = cc
CFLAGS  = -ggdb -Wall -Werror -Wextra -pedantic -ansi -std=c89
LDFLAGS = 

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: dirs clean

all: dirs ttt

dirs:
	mkdir -p ./bin

ttt: $(OBJ)
	$(CC) -o $(BIN)/ttt $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
