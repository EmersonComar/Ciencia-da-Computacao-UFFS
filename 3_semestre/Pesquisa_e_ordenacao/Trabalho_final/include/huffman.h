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
void liberar_texto(char *texto);

// Funções referentes à geração de tabela de frequencia
int *criar_tabela_frequencia(char *texto);
void liberar_tabela_freq(int *tabela);

// funções fila_prioridade
Fila_prioridade *ciar_fila_prioridade();
Node *criar_node(char caractere, int frequencia);
void preenche_fila_prioridade(Fila_prioridade *fila, int *tabela_frequencia);
void gerar_arvore_huffman(Fila_prioridade *fila);

// funções para gerar tabela de código


// funções debug
void exibir_tab_freq(int *tabela);
void exibir_fila_priori(Fila_prioridade *fila);
void exibir_arvore(Fila_prioridade *fila);

#endif