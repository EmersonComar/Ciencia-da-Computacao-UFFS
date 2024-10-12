#include <stdio.h>


void exibirVetor(int *vetor, int n);
void radixsort(int *vetor, int n);
int definirMaior(int *vetor, int n);
void countingSort(int *vetor, int n, int i);

int main(void){
    int vetor[] = {10, 5, 3, 6, 2, 1, 7, 8, 9, 4};
    int n = sizeof(vetor)/sizeof(vetor[0]);

    printf("Vetor não ordenado:\n");
    exibirVetor(vetor, n);

    radixsort(vetor, n);

    printf("Vetor ordenado:\n");
    exibirVetor(vetor, n);

    return 0;
}

void exibirVetor(int *vetor, int n){
    for(int i=0; i<n-1; i++){
        printf("%d, ", vetor[i]);
    }
    printf("%d\n", vetor[n-1]);
}

void radixsort(int *vetor, int n) {
    int maior = definirMaior(vetor, n);
    for (int exp = 1; maior / exp > 0; exp *= 10) {
        countingSort(vetor, n, exp);
    }
}

void countingSort(int *vetor, int n, int exp) {
    int aux[n];  
    int count[10] = {0};  

    for (int i = 0; i < n; i++) {
        int digito = (vetor[i] / exp) % 10;
        count[digito]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        aux[count[(vetor[i] / exp) % 10] - 1] = vetor[i];
        count[(vetor[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        vetor[i] = aux[i];
    }
}

int definirMaior(int *vetor, int n) {
    int maior = vetor[0];
    for (int i = 1; i < n; i++) {
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }
    return maior;
}