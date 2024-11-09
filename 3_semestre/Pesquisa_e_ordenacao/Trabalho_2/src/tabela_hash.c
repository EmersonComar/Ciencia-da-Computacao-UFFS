#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"



struct hash{
    int quantidade, tamanho_tabela;
    Tlist **itens;
};

Hash *criar_tabela(int tamanho_tabela){

    Hash *tabela_hash = (Hash *) malloc(sizeof(Hash));
    if(tabela_hash == NULL){
        return NULL;
    }

    tabela_hash->tamanho_tabela = tamanho_tabela;
    tabela_hash->itens = (Tlist **) malloc(tamanho_tabela * sizeof(Tlist));
    
    if(tabela_hash->itens == NULL){
        free(tabela_hash);
        return NULL;
    }

    tabela_hash->quantidade = 0;
    for(int i=0; i < tabela_hash->tamanho_tabela; i++){
        tabela_hash->itens[i] = NULL;
    }

    return tabela_hash;
}

void limpar_lista(Tlist *lista){
    Tlist *aux = lista;
    while(aux != NULL){
        Tlist *prox = aux->next;
        free(aux);
        aux = prox;
    }
}

void liberar_tabela(Hash *tabela_hash){
    if(tabela_hash != NULL){
        for(int i=0; i < tabela_hash->tamanho_tabela; i++){
            if(tabela_hash->itens[i] != NULL){
                limpar_lista(tabela_hash->itens[i]);
            }
        }
        free(tabela_hash->itens);
        free(tabela_hash);
    }
}

int chaveDivisao(int chave, int tamanho_tabela){
    return chave % tamanho_tabela; 
}

int inserir_hash(Hash *tabela_hash, Tlist lista){
    if(tabela_hash == NULL){
        return 0;
    }

    int chave = lista.valor;
    int posicao;

    posicao = chaveDivisao(chave, tabela_hash->tamanho_tabela);

    Tlist *novo = (Tlist *) malloc(sizeof(Tlist));
    if(novo == NULL){
        return 0;
    }

    *novo = lista;

    if(tabela_hash->itens[posicao] == NULL){
        tabela_hash->itens[posicao] = novo;
    }else{
        Tlist *aux;
        for(aux = tabela_hash->itens[posicao]; aux->next != NULL; aux = aux->next);
        aux->next = novo;
    }

    tabela_hash->quantidade++;

    return 1;
}

void exibir_hash(Hash *tabela_hash){
    if(tabela_hash == NULL){
        return;
    }

    for(int i=0; i < tabela_hash->tamanho_tabela; i++){
        if(tabela_hash->itens[i] == NULL){
            printf("[%d] - NULL\n", i);
        } else {
            printf("[%d] - ", i);
            for(Tlist *aux = tabela_hash->itens[i]; aux != NULL; aux = aux->next){
                printf("%d -> ", aux->valor);
            }
            printf("NULL\n");
        }
    }
}