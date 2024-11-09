#include <stdio.h>
#include "tabela_hash.h"

int main(void){

    printf("Criando ponteiro\n");
    Hash *tabela_hash;

    printf("Criando tabela hash\n");
    tabela_hash = criar_tabela(23);

    printf("Inserindo de 0 a 100 valores na tabela\n");
    Tlist lista;

    for(int i=0; i<=10; i++){
        lista.valor = i;
        lista.next = NULL;
        inserir_hash(tabela_hash, lista);
    }
    

    printf("Exibindo tabela hash\n");
    exibir_hash(tabela_hash);

    printf("Limpando tabela\n");
    liberar_tabela(tabela_hash);


    return 0;
}