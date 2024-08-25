#include "dupla.h"
#include <stdio.h>


int main(void){
    Lista *lista;

    iniciar_lista(lista);

    adicionar_valor_final(lista, 4);
    adicionar_valor_final(lista, 5);
    adicionar_valor_final(lista, 3);
    adicionar_valor_final(lista, 8);
    adicinar_valor_inicio(lista, 1);

    percorrer_lista(lista);

    limpar_lista(lista);

    return 0;

}