#include <stdio.h>

float celxfahren(float cel);
float fahrenxcel(float fahren);

int main(void){
	int menu;
	float entrada, retorno;

	printf("Escolha a conversão: \n");
	printf("1 - Fahrenheit para Celsius\n");
	printf("2 - Celsius para Fahrenheit\n");
	printf("-> ");
	scanf("%d", &menu);
	
	printf("Digite a temperatura que deseja converter: ");
	scanf("%f", &entrada);

	switch(menu){
		case 1:
			retorno = fahrenxcel(entrada);
			break;
		case 2:
			retorno = celxfahren(entrada);
			break;
		default:
			printf("Digite a opção 1 ou 2\n");
			return 1;
	}

	printf("A temperatura convertida é: %.2f\n", retorno);
	return 0;
}

float fahrenxcel(float fahren){
	return 5 * (fahren - 32)/9;
}

float celxfahren(float cel){
	return (9 * cel / 5) + 32;
}
