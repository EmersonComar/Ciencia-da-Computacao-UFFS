#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct Pilha{
    int *dados;
    int topo;
    int capacidade;
};

Pilha *criar_pilha(int capacidade){
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));

    p->dados = (int *)malloc(capacidade * sizeof(int));
    p->topo = -1;
    p->capacidade = capacidade;
    return p;
}

void empilhar(Pilha *p, int elemento){
    if(p->topo < p->capacidade - 1){
        p->dados[++(p->topo)] = elemento;
    } else {
        printf("Erro: Pilha cheia! \n");
    }
}

int desempilhar(Pilha *p){
    if(!esta_vazia(p)){
        return p->dados[(p->topo)--];
    }else {
        printf("Erro: Pilha vazia! \n");
        return -1;
    }
}

int esta_vazia(Pilha *p){
    return p->topo == -1;
}

void liberar_pilha(Pilha *p){
    free(p->dados);
    free(p);
}