#ifndef PILHA_H
#define PILHA_H

typedef struct Pilha Pilha;

Pilha *criar_pilha(int capacidade);
void empilhar(Pilha *p, int elemento);
int desempilhar(Pilha *p);
int esta_vazia(Pilha *p);
void liberar_pilha(Pilha *p);

#endif