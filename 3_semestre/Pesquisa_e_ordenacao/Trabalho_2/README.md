# Pesquisa e Ordenação de Dados - Tabela Hash com Lista Encadeada

Implementação de uma tabela hash com listas encadeadas para operações eficientes de inserção e busca de valores inteiros. Este projeto foi desenvolvido em C e tem como objetivo estudar e demonstrar o uso da estruturas de dados hash para otimização de armazenamento e busca de dados.

## Descrição do Projeto

Esta aplicação em C implementa uma estrutura de dados de tabela hash utilizando listas encadeadas como método de resolução de colisões. Os dados são lidos de um arquivo, armazenados na tabela hash e organizados em listas encadeadas nas posições correspondentes.

### Funcionalidades Principais
- Inserção de valores inteiros em uma tabela hash.
- Conversão de caracteres lidos de arquivo em valores inteiros.
- Exibição de conteúdo da tabela hash.
- Liberação de memória alocada para a estrutura de dados.

## Estrutura do Projeto

- `src/`: Contém os arquivos de código-fonte de implementação
- `include/`: Contém os arquivos de cabeçalho do projeto
- `app/`: Arquivo principal para execução do programa
- `docs/`: Diretório para a documentação do projeto gerada pelo Doxygen
- `README.md`: Arquivo de introdução ao projeto

##  Pré-requisitos

Para compilar e rodar o projeto, é necessário ter:
- **GCC** ou outro compilador C instalado.
- **Doxygen** (para gerar a documentação).

### Instalação de Dependências

No Ubuntu/Debian:
```bash
$ sudo apt update
$ sudo apt install build-essential doxygen valgrind texlive-minimal
```
## Processo de compilação e execução

O processo de compilação pode ser realizado seguindo os passos:

```bash
$ cd Trabalho_2
$ make
$ make run
```

Existe uma target que pode ser utilizada para analisar o uso de memória:
```bash
$ make valgrind
```

## Gerando documentação

A ferramenta utilizada para gerar esta documentação foi o **Doxygen**. O passo-a-passo a seguir detalha o procedimento:

Primeiro é necessário gerar o arquivo de configuração:

```bash
$ doxygen -g
```
Após gerado, alguns parâmetros básicos para edição:

- **INPUT**: Incluir os diretórios que contém os códigos que deseja gerar a documentação
- **EXCLUDE**: Excluir os diretórios aqui listados para não incluir na documentação

Após ajustados os parâmetros desejados, basta gerar a documentação de fato:
```bash
$ doxygen Doxyfile
```

### Gerando PDF's

Primeiramente precisa gerar a documentação acima, porém ajustando o parâmetro `GENERATE_LATEX         = YES`. Após,
acessar o diretório e rodar os seguintes comandos algumas vezes:

```bash
pdflatex refman.tex
makeindex refman.idx
pdflatex refman.tex
pdflatex refman.tex
```