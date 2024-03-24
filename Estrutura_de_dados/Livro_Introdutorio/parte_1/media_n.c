#include <stdio.h>

int main(void){
	int i;
	int n;
	float med = 0.0f;

	printf("Número de valores: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++){
		float v;
		printf("Valor %d: ", i+1);
		scanf("%f", &v);
		med = med + v;
	}

	med = med / n;

	printf("Valor da média: %.2f\n", med);


	return 0;
}
