#include <stdio.h>
#include <stdlib.h>

int **criar_vetor(int linha, int coluna);
void preencher_vetor(int **vetor, int linha, int coluna);
void exibir_vetor(int **vetor, int linha, int coluna);
void limpar_vetor(int **vetor, int coluna);

int main(void){
	int **vetor;
	int linha, coluna;

	printf("Digite o número de linhas: ");
	scanf("%d", &linha);

	printf("Digite o número de colunas: ");
	scanf("%d", &coluna);

	vetor = criar_vetor(linha, coluna);
	preencher_vetor(vetor, linha, coluna);
	exibir_vetor(vetor, linha, coluna);
	limpar_vetor(vetor, coluna);

	return 0;
}

int **criar_vetor(int linha, int coluna){
	int **vetor = (int **) malloc(linha*sizeof(int *));

	for(int i=0; i<linha; i++)
		vetor[i] = (int *) malloc(coluna*sizeof(int));

	return vetor;
}

void preencher_vetor(int **vetor, int linha, int coluna){
	for(int i=0; i<linha; i++)
		for(int j=0; j<coluna; j++){
			printf("Vetor[%d][%d]: ", i+1, j+1);
			scanf("%d", &vetor[i][j]);
		}
}

void exibir_vetor(int **vetor, int linha, int coluna){
	for(int i=0; i<linha; i++)
		for(int j=0; j<coluna; j++)
			printf("Vetor[%d][%d] = %d\n", i+1, j+1, vetor[i][j]);
}

void limpar_vetor(int **vetor, int coluna){
	for(int i=0; i<coluna; i++)
		free(vetor[i]);
	free(vetor);
}
