#include <stdio.h>

int main(void){

	int valor;
	
	printf("Posição: ");
	scanf("%d", &valor);

	if(valor < 0 || valor > 100)
		printf("Digite um valor entre 0 e 100\n");
	else if(valor <= 5)
		printf("Top 5\n");
	else if(valor <= 10)
		printf("Top 10\n");
	else if(valor <= 20)
		printf("Top 20\n");
	else if(valor <= 30)
		printf("Top 30\n");
	else
		printf("Top 100");

	return 0;
}
