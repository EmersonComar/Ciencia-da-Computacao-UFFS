#include <stdio.h>
#include <stdlib.h>


void exibeVetor(int *vetor, int n);
int maiorValor(int *vetor, int n);
void preencheZero(int *vetor, int m);
void contagemValores(int *vetor, int *aux, int n);
void somaAcumulada(int *vetor, int m);
void insereOutput(int *vetor, int *aux, int *output, int n);
void transfereOutput(int *vetor, int *output, int n);

int main(void){

    int vetor[] = {13, 5, 8, 2, 3, 5, 12, 5, 4, 7};
    int n = sizeof(vetor)/sizeof(vetor[0]);

    printf("Vetor não ordenado:\n");
    exibeVetor(vetor, n);

    int m = maiorValor(vetor, n) + 1;
    int *aux = (int *)malloc(m * sizeof(int));
    preencheZero(aux, m);

   // printf("Vetor auxiliar:\n");
   // exibeVetor(aux, m);

    contagemValores(vetor, aux, n);


   // printf("Vetor contado inicial:\n");
   // exibeVetor(aux, m);

    somaAcumulada(aux, m);

  //  printf("Soma acumulada:\n");
  //  exibeVetor(aux, m);


    int *output = (int *)malloc(n * sizeof(int));
    preencheZero(output, n);

    insereOutput(vetor, aux, output, n);
    transfereOutput(vetor, output, n);
    free(aux);
    free(output);

    printf("Vetor ordenado:\n");
    exibeVetor(vetor, n);

    return 0;
}

void exibeVetor(int *vetor, int n){
    for(int i=0; i<n-1; i++)
        printf("%d, ", vetor[i]);
    printf("%d\n", vetor[n-1]);
}

int maiorValor(int *vetor, int n){
    int maior = vetor[0];
    for(int i=1; i<n; i++){
        if(vetor[i] > maior)
            maior = vetor[i];
    }

    return maior;
}

void preencheZero(int *vetor, int m){
    for(int i=0; i<m; i++)
        vetor[i] = 0;
}

void contagemValores(int *vetor, int *aux, int n){
    for(int i=0; i<n; i++)
        aux[vetor[i]]++;
}

void somaAcumulada(int *vetor, int m){
    for(int i=1; i<m; i++)
        vetor[i] += vetor[i - 1];
}

void insereOutput(int *vetor, int *aux, int *output, int n){
    for(int i = (n-1); i>=0; i--){
        aux[vetor[i]] -= 1;
        output[aux[vetor[i]]] = vetor[i];
    }
}

void transfereOutput(int *vetor, int *output, int n){
    for(int i=0; i<n; i++)
        vetor[i] = output[i];
}