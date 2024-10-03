#include <stdio.h>

void exibirVetor(int *vetor, int n);
void heapsort(int *vetor, int n);
void criarHeap(int *vetor, int raiz, int n);
void troca(int *a, int *b);

int main(void){
    int vetor[] = {3, 6, 2, 5, 4, 1};
    int n = sizeof(vetor)/sizeof(vetor[0]);

    printf("Vetor não ordenado:\n");
    exibirVetor(vetor, n);

    heapsort(vetor, n);

    // printf("Heap max criado:\n");
    // exibirVetor(vetor, n);

    printf("Vetor ordenado:\n");
    exibirVetor(vetor, n);

    return 0;
}

void exibirVetor(int *vetor, int n){
    for(int i=0; i<n-1; i++)
        printf("%d, ", vetor[i]);
    printf("%d\n", vetor[n-1]);
}

void heapsort(int *vetor, int n){
    for(int k = n/2-1; k>=0; k--)
        criarHeap(vetor, k, n);

    for(int i = n-1; i>=1; i--){
        troca(&vetor[0], &vetor[i]);
        criarHeap(vetor, 0, i);
    }
}

void criarHeap(int *vetor, int raiz, int n){
    int maior = raiz;
    int l = 2 * raiz + 1;
    int r = 2 * raiz + 2;
    if(l < n && vetor[l] > vetor[raiz]) maior = l;
    if(r < n && vetor[r] > vetor[maior]) maior = r;
    if(maior != raiz){
        troca(&vetor[maior], &vetor[raiz]);
        criarHeap(vetor, maior, n);
    }
}

void troca(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}