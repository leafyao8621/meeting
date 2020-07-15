CC = gcc
SRC = $(wildcard src/tools/*.c) $(wildcard src/util/*.c) $(wildcard src/main.c)
OBJ = $(SRC:.c=.o)
BIN = main
CFLAGS = $(shell mysql_config --cflags)
LIBS = $(shell mysql_config --libs)

%.o: %.c
	$(CC) -g -c $< -o $@ $(CFLAGS)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

.PHONY: clean
clean: $(BIN)
	@rm $(OBJ) $(BIN)
