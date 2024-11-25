#include <stdlib.h>
#include <string.h>
#include "trie.h"

ASCIITrie* ATE_Buscar_R(ASCIITrie* T, unsigned char *chave, int n, int p){

    if(T == NULL){
        return NULL;
    }
    if(n == p){
        return T;
    }

    /**
     * O mapeamento de 1 para 1 está ocorrendo devido à estrutura da
     * trie estar utilizando a mesma quantidade de caracteres da 
     * tabela ASCII
     */
    return ATE_Buscar_R(T->filhos[chave[p]], chave, n, p+1);
}

// Função wrapper
ASCIITrie* ATE_Buscar(ASCIITrie* T, unsigned char *chave){
    return ATE_Buscar_R(T, chave, strlen(chave), 0);
}

ASCIITrie* ATE_Criar(){
    ASCIITrie* noh;
    noh = malloc(sizeof(ASCIITrie));
    noh->estado = ATE_LIVRE;
    noh->val = 0;

    for(int i=0; i < 256; i++){
        noh->filhos[i] = NULL;
    }

    return noh;
}

void ATE_Inserir_R(ASCIITrie **T, unsigned char *chave, int val, int n, int p){

    if(*T == NULL){
        *T = ATE_Criar();
    }
    if(n == p){
        (*T)->val = val;
        (*T)->estado = ATE_OCUPADO;
        return;
    }

    ATE_Inserir_R(&(*T)->filhos[chave[p]], chave, val, n, p+1);
}

void ATE_Inserir(ASCIITrie **T, unsigned char *chave, int val){
    ATE_Inserir_R(T, chave, val, strlen(chave), 0);
}
