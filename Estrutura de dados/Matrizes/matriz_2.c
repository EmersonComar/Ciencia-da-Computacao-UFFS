#include <stdio.h>
#include <stdlib.h>

int **criar_matriz(int lin, int col);
void desalocar_matriz(int **matriz, int col);

void preencher_matriz(int **matriz, int lin, int col);
void maior_valor(int **matriz, int lin, int col, int *maior);

int main(void){
	int **matriz;
	int maior[2];
	int lin, col;

	lin = col = 4;

	matriz = criar_matriz(lin, col);
	preencher_matriz(matriz, lin, col);
	maior_valor(matriz, lin, col, maior);
	
	printf("Maior valor Matriz[%d][%d] = %d\n", maior[0], maior[1], matriz[maior[0]][maior[1]]);

	desalocar_matriz(matriz, col);
	

	return 0;
}

int **criar_matriz(int lin, int col){
	int **matriz;

	matriz = (int **) malloc(lin*sizeof(int *));
	if(matriz == NULL){
		printf("Memória insuficiente!!\n");
		exit(1);
	}

	for(int i=0; i<col; i++){
		matriz[i] = (int *) malloc(col*sizeof(int));
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
			printf("Preecha vetor[%d][%d]: ", i, j);
			scanf("%d", &matriz[i][j]);
		}
}

void maior_valor(int **matriz, int lin, int col, int *maior){
	int x, y;

	x = y = 0;

	for(int i=0; i<lin; i++)
		for(int j=0; j<col; j++){
			if(matriz[i][j] > matriz[x][y]){
				x = i;
				y = j;
			}
		}
	maior[0] = x;
	maior[1] = y;
}
