APP = ./app
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src


all: lib myapp


lib:
	@echo "Compilando arquivo objeto"
	gcc -c $(SRC)/ineficiente.c -I $(INCLUDE) -o $(OBJ)/ineficiente.o

myapp:
	@echo "Compilando main"
	gcc $(APP)/main.c $(OBJ)/* -I $(INCLUDE) -o $(BIN)/main


run: $(BIN)/main
	$(BIN)/main

clear: $(BIN)/main $(OBJ)/ineficiente.o
	@echo "Apagando os arquivos main e ineficiente.o"
	rm $(BIN)/main $(OBJ)/ineficiente.o