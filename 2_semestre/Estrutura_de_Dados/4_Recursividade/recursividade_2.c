#include <stdio.h>
#include <stdlib.h>

int *criar_vetor(int n);
void remover_vetor(int *vetor);
void preencher_vetor(int *vetor, int n);
int somaV(int *vetor, int n);

int main(void){
  int *vetor, n;
  n = 5;
  
  vetor = criar_vetor(n);
  preencher_vetor(vetor, n);
  printf("Soma do vetor: %d\n", somaV(vetor, n));
  remover_vetor(vetor);
  
  return 0;
}

int *criar_vetor(int n){
  int *vetor = (int *) malloc(n * sizeof(int));
  if(vetor == NULL){
    printf("Memória Insuficiente!!\n");
    exit(1);
  }
  
  return vetor;
}

void remover_vetor(int *vetor){
  free(vetor);
}

void preencher_vetor(int *vetor, int n){
  for(int i=0; i<n; i++)
    vetor[i] = i;
}

int somaV(int *vetor, int n){
  if(n == 0)
    return vetor[0];
  return vetor[n] + somaV(vetor, n-1);
}
