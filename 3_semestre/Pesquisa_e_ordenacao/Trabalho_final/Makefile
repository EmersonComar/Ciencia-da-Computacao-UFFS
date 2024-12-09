SRC 		= ./src
BIN 		= ./bin
OBJ 		= ./obj
INCLUDE 	= ./include
APP 		= ./app

all: lib myapp

lib: $(SRC)/huffman.c $(INCLUDE)/huffman.h
	@echo "Compilando arquivo objeto"
	gcc -c $(SRC)/huffman.c -I $(INCLUDE) -o $(OBJ)/huffman.o

myapp: $(OBJ)/huffman.o
	@echo -e "\nCompilando app"
	gcc $(APP)/main.c $(OBJ)/huffman.o -I $(INCLUDE) -o $(BIN)/main


run: $(BIN)/main
	$(BIN)/main

clear: $(BIN)/main $(OBJ)/huffman.o
	@echo "Apagando arquivos main e huffman.o"
	rm $(BIN)/main $(OBJ)/huffman.o