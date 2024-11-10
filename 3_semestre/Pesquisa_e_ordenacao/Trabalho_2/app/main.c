#include <stdio.h>
#include "tabela_hash.h"

int main(void){

    printf("Criando ponteiro\n");
    Hash *tabela_hash;

    printf("Criando tabela hash\n");
    tabela_hash = criar_tabela(23);

    printf("Abrindo arquivo casos_de_teste.txt\n");
    FILE *arquivo = fopen("casos_de_teste.txt", "r");

    if(arquivo == NULL){
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }


    printf("Descobrindo valores numéricos no arquivo\n"); 
    criar_tlist(arquivo);

    printf("\nExibindo tabela hash\n");
    exibir_hash(tabela_hash);

    printf("Limpando tabela\n");
    liberar_tabela(tabela_hash);

    printf("Fechando arquivo\n");
    fclose(arquivo);
    return 0;
}