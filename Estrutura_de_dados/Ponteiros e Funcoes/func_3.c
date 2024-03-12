#include <stdio.h>

int maiorDeDois(int a, int b);
int maiorDeTres(int a, int b, int c);

int main(void){
	int a, b, c;

	printf("Digite o primeiro valor: ");
	scanf("%d", &a);

	printf("Digite o segundo valor: ");
	scanf("%d", &b);

	printf("Digite o terceiro valor: ");
	scanf("%d", &c);

	printf("O maior valor digitado: %d\n", maiorDeTres(a, b, c));

	return 0;
}

int maiorDeDois(int a, int b){
	if(a > b)
		return a;
	return b;
}

int maiorDeTres(int a, int b, int c){
	int maior = maiorDeDois(a, b);

	if (maior > c)
		return maiorDeDois(a, b);
	return c;
}
