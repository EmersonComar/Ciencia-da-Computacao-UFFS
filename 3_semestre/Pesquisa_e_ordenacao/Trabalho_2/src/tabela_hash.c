#include <stdio.h>
#include <stdlib.h>
#include "tabela_hash.h"

#define MAX_CASAS 10

struct tlist{
    int valor;
    struct tlist *next;
};

struct hash{
    int quantidade, tamanho_tabela;
    Tlist **itens;
};

struct lista{
    char casas[MAX_CASAS];
    int quantidade;
};

Hash *criar_tabela(int tamanho_tabela){

    Hash *tabela_hash = (Hash *) malloc(sizeof(Hash));
    if(tabela_hash == NULL){
        return NULL;
    }

    tabela_hash->tamanho_tabela = tamanho_tabela;
    tabela_hash->itens = (Tlist **) malloc(tamanho_tabela * sizeof(Tlist *));
    
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

int potencia(int base, int expoente){
    int total = 1;
    for(int i=0; i<expoente; i++){
        total *= base;
    }
    return total;
}

int extrair_valor(Lista *lista_valores){
    int valor = 0;
    int expoente = lista_valores->quantidade - 1;
    for(int i = 0; i < lista_valores->quantidade; i++){
        valor += lista_valores->casas[i] * potencia(10, expoente);
        expoente--;
    }

    return valor;
}

void insere_tlist(Tlist **lista_tlist, int valor){
    Tlist *novo = (Tlist*) malloc(sizeof(Tlist));
    if(novo == NULL){
        printf("Erro ao alocar memória !!\n");
        exit(1);
    }

    novo->valor = valor;
    novo->next = NULL;

    if(*lista_tlist == NULL){
        *lista_tlist = novo;
    } else{
        Tlist *aux;
        for(aux = *lista_tlist; aux->next != NULL; aux = aux->next);
        aux->next = novo;
    }
}

Tlist *criar_tlist(FILE *arquivo) {
    Lista lista_valores;
    int valor_extraido = 0;
    char caractere;
    Tlist *lista_tlist = NULL;

    lista_valores.quantidade = 0;

    while ((caractere = fgetc(arquivo)) != EOF){
        if( caractere != ';'){
            if (lista_valores.quantidade <= MAX_CASAS){
                lista_valores.casas[lista_valores.quantidade] = caractere - '0';
                lista_valores.quantidade++;
            }
        } else {
            valor_extraido = extrair_valor(&lista_valores);
            lista_valores.quantidade = 0;
            insere_tlist(&lista_tlist, valor_extraido);
        }
    }

    if(lista_valores.quantidade > 0){
        valor_extraido = extrair_valor(&lista_valores);
        lista_valores.quantidade = 0;
        insere_tlist(&lista_tlist, valor_extraido);
    }

}