#include <stdio.h>

int main(void){
	int entrada, total, esperado;
	float porcent;
	total = esperado = 0;

	do{
		printf("Número: ");
		scanf("%d", &entrada);
		total++;

		if(entrada >= 10 && entrada <= 20)
			esperado++;
	}while(entrada > 0);
	if(total != 1)
		total--;

	porcent = (float)esperado/total;
	
	printf("Porcentagem entre 10 e 20: %.0f\%\n", porcent * 100);
	return 0;
}
