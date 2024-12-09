#include <stdio.h>
#include "huffman.h"


int main(void){
    FILE *amostra = fopen("amostra.txt", "r");
    int *tabela_freq;
    Fila_prioridade *fila;
    char **dicionario;
    char *texto;
    char *codigo;
    char *decodificado;

    if(amostra == NULL){
        fprintf(stderr, "Erro ao abrir arquivo \"amostra.txt\"\n");
        return 1;
    }

    texto = ler_texto(amostra);
    printf("Texto: %s\n", texto);

    tabela_freq = criar_tabela_frequencia(texto);
    exibir_tab_freq(tabela_freq);
    fila = ciar_fila_prioridade();
    preenche_fila_prioridade(fila, tabela_freq);

    printf("Exibindo fila prioridade:\n");
    exibir_fila_priori(fila);


    printf("\nDebugando geração da arvore:\n");
    gerar_arvore_huffman(fila);

    printf("\nExibindo arvore final\n");
    exibir_arvore(fila);
    liberar_tabela_freq(tabela_freq);


    printf("\nCriando e exibindo dicionário:\n");
    dicionario = alocar_dicionario(fila->elementos);
    preencher_dicionario(fila, dicionario);
    exibir_dicionario(dicionario);


    printf("Texto comprimido:\n");
    codigo = codificar(dicionario, texto);
    printf("%s\n", codigo);

    printf("Texto decodificado:\n");
    decodificado = decodificar(fila, codigo);
    printf("%s\n", decodificado);


    fclose(amostra);
    liberar_texto(texto);
    return 0;
}