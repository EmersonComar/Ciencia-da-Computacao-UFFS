SRC = ./src
INCLUDE = ./include
OBJ = ./obj
APPS = ./apps
BIN = ./bin

all: libed app

libed:
	gcc -c $(SRC)/pilha.c -I $(INCLUDE) -o $(OBJ)/pilha.o


app:
	gcc $(APPS)/main.c $(OBJ)/*.o -I $(INCLUDE) -o $(BIN)/main

run:
	./bin/main

clean: $(OBJ)/pilha.o $(BIN)/main
	rm ./bin/* ./obj/*