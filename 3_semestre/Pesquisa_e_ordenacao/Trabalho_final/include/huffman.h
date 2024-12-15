#ifndef HUFFMAN_H
#define HUFFMAN_H

struct node{
    char caractere;
    int frequencia;
    struct node *dir;
    struct node *esq;
    struct node *prox;
};
typedef struct node Node;

struct fila_prioridade{
    int quantidade;
    struct node *elementos;
};
typedef struct fila_prioridade Fila_prioridade;


// Funções para ler e liberar o texto do arquivo amostra
char *ler_texto(FILE *amostra);

// Funções referentes à geração de tabela de frequencia
int *criar_tabela_frequencia(char *texto);

// funções fila_prioridade
Fila_prioridade *ciar_fila_prioridade();
Node *criar_node(char caractere,   int frequencia);
void preencher_fila_prioridade(Fila_prioridade *fila, int *tabela_frequencia);
void gerar_arvore_huffman(Fila_prioridade *fila);

// funções para gerar tabela de código
char **alocar_dicionario(Node *node);
void preencher_dicionario(Fila_prioridade *fila, char **dicionario);


// funções para codificar string
char *codificar(char **dicionario, char *texto);

// funções para decodificar string
char *decodificar(Fila_prioridade *fila, char *texto);

// funções para compactar
void compactar(char *texto);

// funções para descompactar
char *descompactar(Fila_prioridade *fila);

// funções exibir
void exibir_dicionario(char **dicionario);

// funções limpeza
void limpar_strings(char *texto);
void limpar_tabela_frequencia(int *tabela_frequencia);
void limpar_fila_prioridade(Fila_prioridade *fila);
void limpar_dicionario(char **dicionario);
#endif