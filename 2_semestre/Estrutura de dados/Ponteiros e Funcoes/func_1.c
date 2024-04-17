#include <stdio.h>

void diferencaEntreDois();
int main(void){
	diferencaEntreDois();	
	return 0;
}

void diferencaEntreDois(){
	int a, b;
	
	printf("Digite o primeiro valor: ");
	scanf("%d", &a);

	printf("Digite o segundo valor: ");
	scanf("%d", &b);

	printf("Diferença: %d\n", a-b);
}
