#include <stdio.h>
#include "tabela_hash.h"

#define TAM_TABELA 7

int main(void){

    printf("Criando tabela hash\n");
    Hash *tabela_hash = criar_tabela(TAM_TABELA);

    printf("Abrindo arquivo \"casos_de_teste.txt\"\n");
    FILE *arquivo = fopen("casos_de_teste.txt", "r");

    if(arquivo == NULL){
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }


    printf("Descobrindo valores numéricos no arquivo\n"); 
    Tlist *lista_tlist = criar_tlist(arquivo);

    printf("Transferindo valores de lista_tlist para tabela hash\n");
    inserir_hash(tabela_hash, lista_tlist);

    printf("\nExibindo tabela hash\n");
    exibir_hash(tabela_hash);

    printf("Limpando tabela\n");
    liberar_tabela(tabela_hash);

    printf("Fechando arquivo\n");
    fclose(arquivo);
    return 0;
}