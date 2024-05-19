#include <stdio.h>
#include <stdlib.h>

int **criar_matriz(int lin, int col);
void desalocar_matriz(int **matriz, int col);
void preencher_matriz(int **matriz, int lin, int col);
void exibir_matriz(int **matriz, int lin, int col);

int main(void){
	int **matriz;
	int lin, col;
	lin = col = 5;

	matriz = criar_matriz(lin, col);
	preencher_matriz(matriz, lin, col);
	exibir_matriz(matriz, lin, col);
	desalocar_matriz(matriz, col);

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

void desalocar_matriz(int **matriz, int col){
	for(int i=0; i<col; i++)
		free(matriz[i]);
	free(matriz);
}

void preencher_matriz(int **matriz, int lin, int col){
	for(int i=0; i<lin; i++)
		for(int j=0; j<col; j++){
			if(i != j)
				matriz[i][j] = 0;
			else
				matriz[i][j] = 1;
		}
}

void exibir_matriz(int **matriz, int lin, int col){
	for(int i=0; i<lin; i++)
		for(int j=0; j<col; j++)
			printf("Matriz[%d][%d]: %d\n", i, j, matriz[i][j]);
}
