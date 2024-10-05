#include "ineficiente.h"
#include <stdio.h>

int main(void){
    
    int vetor[] = {10, 5, 2, 9, 3, 1, 7, 8, 6};
    int tamanho_vetor = sizeof(vetor)/sizeof(vetor[0]);

    Tlist *head = NULL;

    head = gerador_lista(vetor, tamanho_vetor);

    printf("Lista criada\n");
    liberar_memoria(head);
    printf("Memória liberada!\n");

    return 0;
}