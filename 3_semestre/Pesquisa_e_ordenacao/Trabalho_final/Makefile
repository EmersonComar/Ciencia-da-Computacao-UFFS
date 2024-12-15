# Configurações do compilador
CC 						= gcc
CFLAGS					= -Wall -Wextra -pedantic
INCLUDE_FLAGS			= -I $(INCLUDE)

# Estrutura de diretórios
SRC 					= ./src
BIN						= ./bin
OBJ						= ./obj
INCLUDE					= ./include
APP						=./app

# Nome do executável
TARGET					= $(BIN)/main

# Arquivos fonte e objeto
SRCS					= $(APP)/main.c $(SRC)/huffman.c
OBJS					= $(OBJ)/main.o $(OBJ)/huffman.o

# Regra padrão
all: $(BIN) $(OBJ) $(TARGET)

# Criação de diretórios
$(BIN):
	@mkdir -p $(BIN)

$(OBJ):
	@mkdir -p $(OBJ)

# Compilação de objetos
$(OBJ)/main.o: $(APP)/main.c
	@echo "Compilando main.c"
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(OBJ)/huffman.o: $(SRC)/huffman.c $(INCLUDE)/huffman.h
	@echo "Compilando huffman.c"
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Linkagem
$(TARGET): $(OBJS)
	@echo  "Linkando aplicativo"
	@$(CC) $(CFLAGS) $^ -o $@

# Execução
run: $(TARGET)
	@echo "Executando aplicativo"
	@$(TARGET)

# Verificação de memória com Valgrind
valgrind: $(TARGET)
	@echo "Executando valgrind"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(TARGET)

# Limpeza
clean:
	@echo "Removendo arquivos compilados"
	@rm -rf $(BIN)/* $(OBJ)/*

rebuild: clean all
