#include <stdio.h>

int main(void){
	int valor1, valor2, sinal, soma;
	soma = 0;
	sinal = 1;
	
	printf("Primeiro valor: ");
	scanf("%d", &valor1);

	printf("Segundo valor: ");
	scanf("%d", &valor2);

	if (valor2 < 0)
		sinal = -1;

	valor2 *= sinal;
	while (valor2 >= 1){
		soma += valor1;
		valor2--;
	}

	soma *= sinal;

	printf("= %d\n", soma);

	return 0;
}
