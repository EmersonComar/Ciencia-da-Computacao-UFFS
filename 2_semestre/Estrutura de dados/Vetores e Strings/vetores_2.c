#include <stdio.h>

void maior_menor(int *vetor, int tam);

int main(void){
	int vetor[] = {1, 2, 0, 3};
	maior_menor(vetor, 4);

	return 0;
}


void maior_menor(int *vetor, int tam){
	int maior, menor;
	maior = menor = vetor[0];

	for(int i = 0; i < tam; i++){
		if(vetor[i] > maior)
			maior = vetor[i];
		if(vetor[i] < menor)
			menor = vetor[i];
	}

	printf("Maior valor presente no vetor: %d\n", maior);
	printf("Menor valor presente no vetor: %d\n", menor);
}
