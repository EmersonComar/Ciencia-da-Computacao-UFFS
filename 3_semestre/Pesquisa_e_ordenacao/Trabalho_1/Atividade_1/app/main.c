#include "ineficiente.h"
#include <stdio.h>

int main(void){
    
    // irá criar e calcular o tamanho do vetor
    int vetor[] = {0, 10, 5, 2, 9, 3, 1, 7, 8, 6, 11, 0, -1};
    int tamanho_vetor = sizeof(vetor)/sizeof(vetor[0]);
    
    Tlist *head_lista = NULL;

    printf("Vetor inicial: ");
    exibir_vetor(vetor, tamanho_vetor);


    head_lista = gerar_lista(vetor, tamanho_vetor);
    printf("Lista gerada:\n");
    exibir_lista(head_lista);

    int *vet_temp = gerar_vetor(head_lista);
    printf("\nVetor temporário para ordenação: ");
    exibir_vetor(vet_temp, tamanho_vetor);

    selectionsort(vet_temp, tamanho_vetor);
    printf("Vetor temporário ordenado usando SelectionSort: ");
    exibir_vetor(vet_temp, tamanho_vetor);


    liberar_memoria_lista(head_lista);
    liberar_memoria_vetor(vet_temp);
    return 0;
}