/* Programa da conversão de temperatura */

#include <stdio.h>

/* função auxiliar */
float converte (float c){
	float f;
	f = 1.8*c + 32;
	return f;
}

/* Funcção principal */
int main(void){
	float t1;
	float t2;

	/* Mostra mensagem para usuário */
	printf("Digite a temperatura em Celsius: ");
	scanf("%f", &t1);

	t2 = converte(t1);

	printf("temperatura em Fahrenheit: %.2f\n", t2);
	return 0;
}
