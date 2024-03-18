#include <stdio.h>

int main(void){
	int valor1, valor2, sinal, soma;
	sinal = 1;
	soma = 0;

	printf("Digite o primeiro valor: ");
	scanf("%d", &valor1);

	printf("Digite o segundo valor: ");
	scanf("%d", &valor2);

	if(valor2 < 0)
		sinal = -1;

	valor2 *= sinal;
	for(int i = 1; i <= valor2; i++)
		soma += valor1;

	valor2 *= sinal;
	soma *= sinal;

	printf("%d x %d = %d\n", valor1, valor2, soma);

	return 0;
}
