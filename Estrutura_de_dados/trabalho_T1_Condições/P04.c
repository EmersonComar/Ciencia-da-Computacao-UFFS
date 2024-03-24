#include <stdio.h>

int main(void){
	int valor, negativo, positivo;

	negativo = positivo = 0;
	for(int i=1; i<=4; i++){
		printf("N%d: ", i);
		scanf("%d", &valor);

		if(valor >= 0)
			positivo++;
		else
			negativo++;
	}

	printf("%d (+) e %d (-)\n", positivo, negativo);

	return 0;
}
