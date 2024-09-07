#include <stdio.h>

void exibirVetor(int *vetor, int N);
void bubblesort_flag(int *vetor, int N);

int main(void){

    int vetor[] = {1, 2, 3, 4, 5};

    int N = sizeof(vetor)/sizeof(vetor[0]);

    printf("Vetor desordenado:\n");
    exibirVetor(vetor, N);

    bubblesort_flag(vetor, N);

    printf("Vetor ordenado:\n");
    exibirVetor(vetor, N);

    return 0;
}

void exibirVetor(int *vetor, int N){
    for(int i=0; i<N-1; i++)
        printf("%d, ", vetor[i]);
    printf("%d", vetor[N-1]);
    printf("\n");
}

void bubblesort_flag(int *vetor, int N){
    for (int i= N-1; i>0; i--){
        printf("Estado vetor:\n");
        exibirVetor(vetor, N);
        printf("\nPosição de i: %d\nValor de i: %d\n", i, vetor[i]);
        int flag = 0;

        for(int j=0; j<i; j++){
            printf("\tPosição de j: %d\n", j);
            printf("\t\tValor de vetor[j]: %d\n\t\tValor de vetor[j+1]: %d\n", vetor[j], vetor[j+1]);
            if(vetor[j] > vetor[j+1]){
                printf("\t\t\tTrocou %d por %d\n", vetor[j], vetor[j+1]);
                int aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
                flag = 1;
            }
        }

        printf("\n");

        if(flag == 0)
            break;
    }
}