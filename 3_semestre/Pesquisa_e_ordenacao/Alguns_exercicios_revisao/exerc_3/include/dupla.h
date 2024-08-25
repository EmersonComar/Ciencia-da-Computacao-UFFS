#ifndef DUPLA_H
#define DUPLA_H

typedef struct Node Node;
typedef struct Lista Lista;


void iniciar_lista(Lista *lista);
void adicionar_valor_final(Lista *lista, int valor);
void adicinar_valor_inicio(Lista *lista, int valor);
void percorrer_lista(Lista *lista);
void limpar_lista(Lista *lista);

#endif