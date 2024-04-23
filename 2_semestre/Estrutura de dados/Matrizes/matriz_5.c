#include <stdio.h>
#include <stdlib.h>

int **cria_matriz(int lin, int col);
void desaloca_matriz(int **matriz, int col);
void preenche_matriz(int **matriz, int lin, int col);
void exibe_matriz(int **matriz, int lin, int col);

int main(void){
  int **matriz;
  int lin, col;
  lin = col = 4;
  
  matriz = cria_matriz(lin, col);
  preenche_matriz(matriz, lin, col);
  exibe_matriz(matriz, lin, col);
  desaloca_matriz(matriz, col);

  return 0;
}

int **cria_matriz(int lin, int col){
  int **matriz;
  
  matriz = (int **) malloc(lin * sizeof(int *));
  if(matriz == NULL){
    printf("Memória Insuficiente!!\n");
    exit(1);
  }
  
  for(int i=0; i<col; i++){
    matriz[i] = (int *) malloc(col * sizeof(int));
    if(matriz[i] == NULL){
      printf("Memória Insuficiente!!\n");
      exit(1);
    }
  }
  
  return matriz;
}

void desaloca_matriz(int **matriz, int col){
  for(int i=0; i<col; i++)
    free(matriz[i]);
  free(matriz);
}

void preenche_matriz(int **matriz, int lin, int col){
  for(int i=0; i<lin; i++)
    for(int j=0; j<col; j++){
      matriz[i][j] = i;
    }
}

void exibe_matriz(int **matriz, int lin, int col){
  
  printf("\t\t");
  for(int i=0; i<lin; i++)
    printf("%d\t", i);
  
  printf("\n");
  for(int i=0; i<lin; i++){
    printf("Linha %d\t\t", i);
    for(int j=0; j<col; j++){
      if(i <= j){
        printf("%d\t", matriz[i][j]);
      }
    }
    printf("\n");
  }
}
