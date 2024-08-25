#include "dupla.h"
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int valor;
    struct Node *prox;
    struct Node *ant;
};

struct Lista{
    Node *head;
    Node *tail;
};

void iniciar_lista(Lista *lista){
    lista->head = NULL;
    lista->tail = NULL;
}

void adicionar_valor_final(Lista *lista, int valor){
    Node *novo = (Node *)malloc(sizeof(Node));

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if(lista->head == NULL){
        lista->head = novo;
        lista->tail = novo;
    } else{
        lista->tail->prox = novo;
        novo->ant = lista->tail;

        lista->tail = novo;
    }
}

void limpar_lista(Lista *lista){
    Node *atual = lista->head;
    Node *prox;

    while(atual != NULL){
        prox = atual->prox;

        free(atual);
        atual = prox;
    }
}

void percorrer_lista(Lista *lista){
    for(Node *aux = lista->head; aux != NULL; aux = aux->prox){
        printf("Endereço atual: %p\n", aux);
        printf("Valor: %d\n", aux->valor);
        printf("Endereço anterior: %p\n", aux->ant);
        printf("Endereço próximo: %p\n", aux->prox);
        printf("===\n");
    }
}

void adicinar_valor_inicio(Lista *lista, int valor){
    Node *novo = (Node *)malloc(sizeof(Node));

    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = NULL;

    if(lista->head == NULL){
        lista->head = novo;
        lista->tail = novo;
    } else{
        lista->head->ant = novo;
        novo->prox = lista->head;

        lista->head = novo;
    }
}