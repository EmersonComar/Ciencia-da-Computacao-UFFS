#include <stdio.h>

int main(void){
	int entrada, soma, sinal;
	sinal = 1;
	soma = 0;

	printf("Digite o valor: ");
	scanf("%d", &entrada);

	if(entrada < 0)
		sinal = -1;

	entrada *= sinal;
	for(int i=1; i <= entrada; i++){
		soma += i;
	}

	soma *= sinal;
	entrada *= sinal;
	printf("Somando de 0 até %d: %d\n", entrada, soma);

	return 0;
}
