# Variáveis onde são definidos os diretórios padrões
APP = ./app
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

# Ao rodar o comando make, esta target será chamada
all: lib myapp

# Responsável em compilar o arquivo objeto
lib:
	@echo "Compilando arquivo objeto"
	gcc -c $(SRC)/ineficiente.c -I $(INCLUDE) -o $(OBJ)/ineficiente.o

# Irá compilar o main linkando com o arquivo objeto
myapp:
	@echo -e "\nCompilando main"
	gcc $(APP)/main.c $(OBJ)/* -I $(INCLUDE) -o $(BIN)/main

# target para execução 
run: $(BIN)/main
	$(BIN)/main

# Apenas para excluir os arquivos "variáveis"
clear: $(BIN)/main $(OBJ)/ineficiente.o
	@echo "Apagando os arquivos main e ineficiente.o"
	rm $(BIN)/main $(OBJ)/ineficiente.o

# Analisar liberação de memória. Necessário instalar pacote valgrind
valgrind: $(BIN)/main
	@echo "Executando analise de memória"
	valgrind $(BIN)/main