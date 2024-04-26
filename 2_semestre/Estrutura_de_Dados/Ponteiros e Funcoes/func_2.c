#include <stdio.h>

int maiorDeDois(int a, int b);

int main(void){
	int a, b;
	
	printf("Digite o primeiro valor: ");
	scanf("%d", &a);


	printf("Digite o segundo valor: ");
	scanf("%d", &b);

	printf("O maior valor é: %d\n", maiorDeDois(a, b));
	return 0;
}

int maiorDeDois(int a, int b){
	if (a > b)
		return a;
	else
		return b;
}
