#include <stdio.h>
#include <stdlib.h>

void exibeVetor(int *vetor, int inicio, int fim);
void mergesort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);

int main(void){
    int vetor[] = {1, 5, 6, 3, 2, 4};
    int fim = (sizeof(vetor)/sizeof(vetor[0])) - 1;
    int inicio = 0;

    printf("Vetor não ordenado:\n");
    exibeVetor(vetor, inicio, fim);

    mergesort(vetor, inicio, fim);

    printf("Depois de ordenado:\n");
    exibeVetor(vetor, inicio, fim);
    return 0;
}

void exibeVetor(int *vetor, int inicio, int fim){
    for(int i = inicio; i<fim; i++)
        printf("%d, ", vetor[i]);
    printf("%d\n", vetor[fim]);
}

void mergesort(int *vetor, int inicio, int fim){
    int meio;

    if(inicio < fim){
        meio = (int)(inicio + fim)/2;
        mergesort(vetor, inicio, meio);
        mergesort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

void merge(int *vetor, int inicio, int meio, int fim){
    int *temp, i, k, j, p1, p2, tamanho;
    int fim1 = 0, fim2 = 0;

    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;

    temp = (int *)malloc(tamanho * sizeof(int));
    if(temp != NULL){
        for(i=0; i<tamanho; i++){
            if(!fim1 && !fim2){
                if(vetor[p1] < vetor[p2])
                    temp[i] = vetor[p1++];
                else
                    temp[i] = vetor[p2++];

                if(p1 > meio) fim1 = 1;
                if(p2 > fim) fim2 = 1;
            }else{
                if(!fim1)
                    temp[i] = vetor[p1++];
                else
                    temp[i] = vetor[p2++];
            }
        }

        for(j=0, k=inicio; k<tamanho; k++, j++)
            vetor[k] = temp[j];
    }
    free(temp);
}