#include <stdio.h>

void exibirVetor(int *vetor, int N);
void insertionsort(int *vetor, int N);

int main(void){
    int vetor[] = {21, 3, 4, -1};
    int N = sizeof(vetor)/sizeof(vetor[0]);

    printf("Vetor não ordenado:\n");
    exibirVetor(vetor, N);

    insertionsort(vetor, N);

    printf("Vetor ordenado:\n");
    exibirVetor(vetor, N);

    return 0;
}

void exibirVetor(int *vetor, int N){
    for(int i=0; i<N-1; i++)
        printf("%d, ", vetor[i]);
    printf("%d\n", vetor[N-1]);
}

void insertionsort(int *vetor, int N){
    int i, j, aux;

    for(i = 1; i<N; i++){
        aux = vetor[i];

        for(j = i; (j > 0) && (aux < vetor[j - 1]); j--)
            vetor[j] = vetor[j - 1];

        vetor[j] = aux;
    }
}