#include <stdio.h>

int main(void){
	int entrada, fat;
	fat = 1;


	printf("Digite um valor que deseja calcular o fatorial: ");
	scanf("%d", &entrada);

	if(entrada < 0){
		printf("Digite um valor positivo\n");
		return 1;
	}

	for(int i = 1; i <= entrada; i++){
		fat *= i;
	}

	printf(" = %d\n", fat);


	return 0;
}
