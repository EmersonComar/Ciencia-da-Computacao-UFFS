#include <stdio.h>
#define TAM 5

int main(void){
	int vetor[TAM];

	for(int i = 0; i < TAM; i++){
		printf("Valor %d de %d: ", i+1, TAM);
		scanf("%d", &vetor[i]);
	}

	printf("\nValores digitados: \n");

	for(int i = 0; i < TAM; i++)
		printf("Vetor[%d]: %d\n", i, vetor[i]);


	return 0;
}
