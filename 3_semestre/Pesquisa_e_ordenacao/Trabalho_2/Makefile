SRC 		= ./src
BIN 		= ./bin
OBJ 		= ./obj
INCLUDE 	= ./include
APP 		= ./app

all: lib myapp

lib: $(SRC)/tabela_hash.c $(INCLUDE)/tabela_hash.h
	@echo "Compilando arquivo objeto"
	gcc -c $(SRC)/tabela_hash.c -I $(INCLUDE) -o $(OBJ)/tabela_hash.o

myapp: $(OBJ)/tabela_hash.o
	@echo "\nCompilando app"
	gcc $(APP)/main.c $(OBJ)tabela_hash.o -I $(INCLUDE) -o $(BIN)/main


run: $(BIN)/main
	$(BIN)/main

clear: $(BIN)/main $(OBJ)/tabela_hash.o
	@echo "Apagando arquivos main e tabela_hash.o"
	rm $(BIN)/main $(OBJ)/tabela_hash.o