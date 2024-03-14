#include <stdio.h>

int fat(int valor){
	if(valor == 0)
		return 1;
	return valor * fat(valor - 1);

}

int main(void){
	int valor, retorno;

	scanf("%d", &valor);
	retorno = fat(valor);
	printf("Fatorial de %d: %d\n", valor, retorno);

	return 0;
}
