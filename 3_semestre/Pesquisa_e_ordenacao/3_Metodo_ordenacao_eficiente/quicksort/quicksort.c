#include <stdio.h>


void exibeVetor(int *vetor, int n);
void quicksort(int *vetor, int inicio, int fim);
int particao(int *vetor, int inicio, int fim);
void troca(int *a, int *b);


int main(void){

    int vetor[] = {7, 5, 3, 2, 1, 15};
    int n = sizeof(vetor)/sizeof(vetor[0]);

    printf("Vetor não ordenado:\n");
    exibeVetor(vetor, n);

    quicksort(vetor, 0, n);

    printf("Vetor ordenado:\n");
    exibeVetor(vetor, n);

    return 0;
}

void exibeVetor(int *vetor, int n){
    for(int i=0; i<n-1; i++)
        printf("%d, ", vetor[i]);
    printf("%d\n", vetor[n-1]);
}

void quicksort(int *vetor, int inicio, int fim){
    if (inicio < fim){
        int pivo = particao(vetor, inicio, fim);
        quicksort(vetor, 0, pivo-1);
        quicksort(vetor, pivo+1, fim);
    }
}

int particao(int *vetor, int inicio, int fim){
    int pivo = vetor[fim];
    int k = inicio - 1;

    for(int i = inicio; i<fim; i++){
        if(vetor[i] <= pivo){
            k++;
            troca(&vetor[k], &vetor[i]);
        }
    }
   // if(vetor[k] > vetor[fim])
        troca(&vetor[k + 1], &vetor[fim]);

    return k + 1;
}

void troca(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}
