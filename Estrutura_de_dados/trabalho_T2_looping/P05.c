#include <stdio.h>

int fatorial(int entrada);

int main(void){
	int entrada, fat;

	printf("Digite um valor maior que 1 para calcular o fatorial: ");
	scanf("%d", &entrada);

	if(entrada < 1){
		printf("Digite um valor maior que 1\n");
		return 1;
	}

	fat = fatorial(entrada);
	printf("Fatorial de %d: %d\n", entrada, fat);
	return 0;
}

int fatorial(int entrada){
	int fat = 1;
	
	for(int i = 1; i <= entrada; i++)
		fat *= i;

	return fat;
}
