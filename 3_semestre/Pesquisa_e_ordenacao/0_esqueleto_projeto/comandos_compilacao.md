## Casos básicos:
### Compilações onde todos os arquivos estão no mesmo nível de diretório

- Compilar um programa sem dependencia externa:

```bash
gcc programa.c -o programa
```
- Compilar código apenas da implementação para a geração do código objeto, ou seja, de um programa sem a função main():

```bash        
gcc -c pilha.c -o pilha.o
```

- Compilar código fonte dos programas e código de implementação de uma vez:

```bash
gcc main.c pilha.c -o principal
```


## Compilações de projetos TAD

### Esqueleto básico

```bash
├── app
│   └── main.c
├── bin
│   └── main
├── include
│   └── arquivos_header.h
├── obj
│   └── arquivos_obj.o
└── src
    └── implementacoes.c
```


### Diretório obj
- obj: diretório onde serão separados os arquivos objetos(.o)

```bash  
gcc -c pilha.c -o obj/pilha.o
```

### Diretório include
- include: diretório que ficarão as especificações(.h)

```bash
gcc -c pilha.c -I include/ -o obj/pilha.o
```

### Diretório src
- src: diretório para armazenar as implementações dos TADs(.c)

```bash
gcc -c src/pilha.c -I include/ -o obj/pilha.o
```
- Observação: Em alguns projetos, os arquivos de implementações ficam no mesmo diretório das implementações(src), dessa forma, a compilação fica simplificada:

```bash
gcc -c src/pilha.c -o obj/pilha.o
```

### Diretório apps
- apps: usado para guardar o código fonte dos programas executaveis
    
    - bin: os binários compilados dos programas executaveis
    
    ```bash
        gcc apps/main.c obj/pilha.o -I include/ -o bin/main
    ```
    - Observação: Caso sejam utilizados outras implementações, deverá ser passado o código objeto no momento de compilação:
    ```bash
        gcc apps/main.c obj/pilha.o obj/outrocodigo.o -I include/ -o bin/main
    ```

    - Mas também pode ser utilizado o coringa * para passar todos os arquivos objetos durante a compilação:

    ```bash
        gcc apps/main.c obj/*.o -I include/ -o bin/main
    ```

## Makefile

- O processo de compilação dos programas irão ficar cada vez mais complexo conforme a aplicação cresce. o arquivo `Makefile` serve para automatizar os processos de compilação dos códigos, na qual dentro dele terá diversas diretivas explicitando como será realizado o processo de compilação.

- O comando utilizado para executar as diretivas do arquivo **Makefile** será o `make`. É necessário executá-lo no mesmo diretório onde estará o arquivo **Makefile**

### Basico de Makefile

- Basicamente, as instruções dentro do Makefile estarão dentro de **targets**(ou flags) sendo que a target **all** será padrão. A identação precisa ser obrigatóriamente com [TAB].

```Makefile
all:
    echo "Olá mundo"
```

- Podemos criar nossas próprias *targets*

```Makefile
hello:
    echo "Olá
```
- O exemplo acima será executado com: `make hello`

- É possível utilizar variáveis para deixar as diretivas mais organizadas

```Makefile
SRC = ./src
INCLUDE = ./include
OBJ = ./obj

all:
    gcc -c $(SRC)/pilha.c -I $(INCLUDE) -o $(OBJ)/pilha.o
```

- As targets podem possuir dependencias. Dentre outras aplicações, as dependencias podem ser utilizadas para uma target chamar outras:

```Makefile
all: hello word

hello:
    echo "Hello "

word:
    echo "word"
```

- A dependencia também pode ser um arquivo, conforme o exemplo abaixo:

```Makefile
all: arquivo.c arquivo.h
    echo "Só irei executar se os dois arquivos anteriores existirem"
```