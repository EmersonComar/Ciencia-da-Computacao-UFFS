#include <stdlib.h>
#include <string.h>
#include "tabelahash.h"

struct hash{
    int qtd, TABLE_SIZE;
    struct aluno **itens;
};

Hash *criaHash(int TABLE_SIZE) {
    Hash *ha = (Hash *)malloc(sizeof(Hash));

    if (ha == NULL){
        return NULL;
    }

    ha->TABLE_SIZE = TABLE_SIZE;
    ha->itens = (Hash **)malloc(TABLE_SIZE * sizeof(struct aluno*));

    if(ha->itens == NULL){
        free(ha);
        return NULL;
    }

    ha->qtd = 0;
    for(int i=0; i < ha->TABLE_SIZE; i++){
        ha->itens[i] = NULL;
    }

    return ha;
}

void liberaHash(Hash *ha){
    if(ha != NULL){
        for(int i = 0; i < ha->TABLE_SIZE; i++){
            if(ha->itens[i] != NULL){
                free(ha->itens[i]);
            }
        }
        free(ha->itens);
        free(ha);
    }
}