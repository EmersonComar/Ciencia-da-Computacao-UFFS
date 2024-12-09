#ifndef HUFFMAN_H
#define HUFFMAN_H

struct node{
    unsigned char caractere;
    unsigned int frequencia;
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
unsigned char *ler_texto(FILE *amostra);

// Funções referentes à geração de tabela de frequencia
unsigned int *criar_tabela_frequencia(unsigned char *texto);

// funções fila_prioridade
Fila_prioridade *ciar_fila_prioridade();
Node *criar_node(unsigned char caractere, unsigned int frequencia);
void preencher_fila_prioridade(Fila_prioridade *fila, unsigned int *tabela_frequencia);
void gerar_arvore_huffman(Fila_prioridade *fila);

// funções para gerar tabela de código
unsigned char **alocar_dicionario(Node *node);
void preencher_dicionario(Fila_prioridade *fila, unsigned char **dicionario);


// funções para codificar string
unsigned char *codificar(unsigned char **dicionario, unsigned char *texto);

// funções para decodificar string
unsigned char *decodificar(Fila_prioridade *fila, unsigned char *texto);

// funções para compactar
void compactar(unsigned char *texto);

// funções para descompactar
char *descompactar(Fila_prioridade *fila);

// funções exibir
void exibir_dicionario(unsigned char **dicionario);
#endif