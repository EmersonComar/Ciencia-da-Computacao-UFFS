#include <stdio.h>
#include "pilha.h"

int main(){
    Pilha *p = criar_pilha(10);
    empilhar(p, 5);
    empilhar(p, 10);

    printf("Desempilhando: %d\n", desempilhar(p));
    printf("Desempilhando: %d\n", desempilhar(p));

    liberar_pilha(p);
    return 0;
}