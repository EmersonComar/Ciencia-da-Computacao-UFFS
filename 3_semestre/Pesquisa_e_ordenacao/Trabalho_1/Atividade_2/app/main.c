#include "eficiente.h"
#include <stdio.h>

int main(void){
    
    // irá criar e calcular o tamanho do vetor
    int vetor[] = {0, 0, -1, -2, 5};
    int tamanho_vetor = sizeof(vetor)/sizeof(vetor[0]);
    
    Tlist *head_lista = NULL;

    Tqueue *head_fila = NULL;
    Tqueue *tail_fila = NULL;

    printf("Vetor inicial: ");
    exibir_vetor(vetor, tamanho_vetor);


    head_lista = gerar_lista(vetor, tamanho_vetor);
    printf("Lista gerada:\n");
    exibir_lista(head_lista);

    int *vet_temp = gerar_vetor(head_lista);
    printf("\nVetor temporário para ordenação: ");
    exibir_vetor(vet_temp, tamanho_vetor);

    quicksort(vet_temp, 0, tamanho_vetor);
    printf("Vetor temporário ordenado usando QuickSort: ");
    exibir_vetor(vet_temp, tamanho_vetor);

    gerar_fila(&head_fila, &tail_fila, vet_temp, tamanho_vetor);
    printf("\nFila ordenada gerada a partir de vetor temporário:\n");
    exibir_fila(head_fila);

    liberar_memoria_lista(head_lista);
    liberar_memoria_vetor(vet_temp);
    liberar_memoria_fila(head_fila);
    return 0;
}