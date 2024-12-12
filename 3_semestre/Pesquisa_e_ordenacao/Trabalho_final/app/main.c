#include <stdio.h>
#include "huffman.h"


int main(void){

    Fila_prioridade *fila;
    unsigned char *texto;
    unsigned int *tabela_frequencia;
    unsigned char **dicionario;
    unsigned char *codificado;
    unsigned char *decodificado;
    unsigned char *descompactado;
    
    FILE *amostra = fopen("amostra.txt", "r");
    if(amostra == NULL){
        fprintf(stderr, "Erro ao abrir arquivo amostra.txt\n");
        return 1;
    }

    FILE *arq_decodificado = fopen("decodificado.txt", "w");
    if(arq_decodificado == NULL){
        fprintf(stderr, "Erro ao abrir arquivo decodificado.txt");
        return 1;
    }

    texto = ler_texto(amostra);
    tabela_frequencia = criar_tabela_frequencia(texto);

    fila = ciar_fila_prioridade();
    preencher_fila_prioridade(fila, tabela_frequencia);
    gerar_arvore_huffman(fila);

    dicionario = alocar_dicionario(fila->elementos);
    preencher_dicionario(fila, dicionario);
    exibir_dicionario(dicionario);

    codificado = codificar(dicionario, texto);
    decodificado = decodificar(fila, codificado);
    
    compactar(codificado);
    descompactado =  descompactar(fila);
    fputs(descompactado, arq_decodificado);


    fclose(amostra);
    fclose(arq_decodificado);
    limpar_tabela_frequencia(tabela_frequencia);
    limpar_fila_prioridade(fila);
    limpar_strings(texto);
    limpar_strings(codificado);
    limpar_strings(decodificado);
    limpar_strings(descompactado);
    limpar_dicionario(dicionario);

    return 0;
}