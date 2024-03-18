#include <stdio.h>

int main(void){
	int entrada, soma, sinal;
	soma = 0;
	sinal = 1;

	printf("Digite um valor inteiro: ");
	scanf("%d", &entrada);

	if(entrada < 0)
		sinal = -1;

	entrada *= sinal;

	for(int i = 0; i <= entrada; i++)
		soma += i;

	entrada *= sinal;
	soma *= sinal;

	printf("Soma de 0 até %d: %d\n", entrada, soma);

	return 0;
}
