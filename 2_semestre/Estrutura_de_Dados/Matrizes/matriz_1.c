#include <stdio.h>
#include <stdlib.h>

int **criar_matriz(int lin, int col);
void finalizar_matriz(int **matriz, int col);
void preencher_matriz(int **matriz, int lin, int col);
void exibir_diagonal(int **matriz, int lin);

int main(void){
	int **matriz;
	int lin, col;

	lin = col = 4;
	matriz = criar_matriz(lin, col);
	preencher_matriz(matriz, lin, col);
	exibir_diagonal(matriz, lin);
	finalizar_matriz(matriz, col);



	return 0;
}

int **criar_matriz(int lin, int col){
	int **matriz;

	matriz = (int **) malloc(lin * sizeof(int *));

	if(matriz == NULL){
		printf("Memória insuficiente!!\n");
		exit(1);
	}

	for(int i=0; i<col; i++){
		matriz[i] = (int *) malloc(col * sizeof(int));
		if(matriz[i] == NULL){
			printf("Memória insuficiente!!\n");
			exit(1);
		}
	}

	return matriz;
}

void finalizar_matriz(int **matriz, int col){
	for(int i=0; i<col; i++)
		free(matriz[i]);
	free(matriz);
}

void preencher_matriz(int **matriz, int lin, int col){
	for(int i=0; i<lin; i++)
		for(int j=0; j<col; j++){
			printf("Preencha vetor[%d][%d]: ", i+1, j+1);
			scanf("%d", &matriz[i][j]);
		}
}

void exibir_diagonal(int **matriz, int lin){
	for(int i=0; i<lin; i++)
		printf("Vetor[%d][%d]: %d\n", i+1, i+1, matriz[i][i]);
}
