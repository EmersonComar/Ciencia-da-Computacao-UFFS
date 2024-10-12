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
	gcc -c $(SRC)/eficiente.c -I $(INCLUDE) -o $(OBJ)/eficiente.o

# Irá compilar o main linkando com o arquivo objeto
myapp:
	@echo -e "\nCompilando main"
	gcc $(APP)/main.c $(OBJ)/eficiente.o -I $(INCLUDE) -o $(BIN)/main

# target para execução 
run: $(BIN)/main
	$(BIN)/main

# Apenas para excluir os arquivos "variáveis"
clear: $(BIN)/main $(OBJ)/eficiente.o
	@echo "Apagando os arquivos main e eficiente.o"
	rm $(BIN)/main $(OBJ)/eficiente.o

# Analisar liberação de memória. Necessário instalar pacote valgrind
valgrind: $(BIN)/main
	@echo "Executando analise de memória"
	valgrind $(BIN)/main