#ifndef NUMERO_H
#define NUMERO_H

typedef struct Node Node;


void inicializa_node(Node *head);
void adiciona_node(Node *head, int valor);
void percorrer_lista(Node *head);
void limpar_lista(Node *head);

#endif