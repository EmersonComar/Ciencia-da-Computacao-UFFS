#include "numero.h"
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int valor;
    struct Node *prox;
};

void inicializa_node(Node *head){
    head->prox = NULL;
}

void adiciona_node(Node *head, int valor){
    Node *novo = (Node *)malloc(sizeof(Node));

    novo->valor = valor;
    novo->prox = NULL;

    if(head->prox == NULL){
        head->prox = novo;
    }else{

        Node *aux;
        for(aux = head->prox; aux->prox != NULL; aux = aux->prox);
        aux->prox = novo;
    }
}

void percorrer_lista(Node *head){
    if(head == NULL){
        printf("Lista vazia!\n");
        return;
    }

    for(Node *aux = head->prox; aux != NULL; aux = aux->prox){
        printf("Valor: %d\n", aux->valor);
        printf("===\n");
    }
}

void limpar_lista(Node *head){
    Node *atual = head->prox;
    Node *prox;

    while(atual != NULL){
        prox = atual->prox;

        free(atual);
        atual = prox;
    }
}