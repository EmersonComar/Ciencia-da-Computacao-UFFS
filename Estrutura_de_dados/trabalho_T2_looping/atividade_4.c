#include <stdio.h>

int main(void){
	int operacao;
	float valor1, valor2, resultado;

	printf("== Calculadora ==\n");
	printf("Digite o primeiro valor: ");
	scanf("%f", &valor1);

	printf("Digite o segundo valor: ");
	scanf("%f", &valor2);

	printf("Operações: \n");
	printf("1 - Soma\n");
	printf("2 - Subtração\n");
	printf("3 - Multiplicação\n");
	printf("4 - Divisão\n");
	printf("-> ");
	scanf("%d", &operacao);


	switch(operacao){
		case 1:
			resultado = valor1 + valor2;
			break;
		case 2:
			resultado = valor1 - valor2;
			break;
		case 3:
			resultado = valor1 * valor2;
			break;
		case 4:
			resultado = valor1 / valor2;
			break;
		default:
			printf("Digite um valor entre 1 e 4\n");
			return 1;
	}

	printf(" = %.2f\n", resultado);
	return 0;
}
