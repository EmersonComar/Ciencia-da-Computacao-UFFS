#pragma once

typedef enum ASCIITrie_ESTADO {
    ATE_LIVRE,
    ATE_OCUPADO
} ASCIITrie_ESTADO;

typedef struct ASCIITrie{
    int val;
    ASCIITrie_ESTADO estado;
    struct ASCIITrie *filhos[256];
} ASCIITrie;

ASCIITrie* ATE_Buscar(ASCIITrie* T, unsigned char *chave);
void ATE_Inserir(ASCIITrie **T, unsigned char *chave, int val);
ASCIITrie* ATE_Criar();