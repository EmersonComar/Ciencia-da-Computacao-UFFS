#ifndef ESTUDANTE_H
#define ESTUDANTE_H

typedef struct Estudante Estudante;
typedef struct Node Node;

void inicializa_lista(Node *head);
Estudante *cadastrar_aluno(char *nome, int idade, float media);
void adicionar_aluno(Node *head, Estudante *aluno);
void percorrer_lista(Node *head);
void limpar_lista(Node *head);
#endif