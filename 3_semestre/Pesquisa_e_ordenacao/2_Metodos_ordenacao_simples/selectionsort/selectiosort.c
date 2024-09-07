#include <stdio.h>

void exibirVetor(int *vetor, int N);
void selectionsort(int *vetor, int N);

int main(void){
    int vetor[] = {2, 4, 3, 5, 1, 6};
    int N = sizeof(vetor)/sizeof(vetor[0]);

    printf("Vetor não ordenado:\n");

    exibirVetor(vetor, N);

    selectionsort(vetor, N);

    printf("Vetor ordenado:\n");
    exibirVetor(vetor, N);

    return 0;
}

void exibirVetor(int *vetor, int N){
    for(int i=0; i<N-1; i++)
        printf("%d, ", vetor[i]);
    printf("%d\n", vetor[N-1]);
}

void selectionsort(int *vetor, int N){
    for(int i=0; i<N-1; i++){
        int menor = i;

        for(int j=i+1; j<N; j++){
            if(vetor[menor] > vetor[j]){
                menor = j;
            }
        }

        int aux = vetor[menor];
        vetor[menor] = vetor[i];
        vetor[i] = aux;
    }
}