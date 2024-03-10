#include <stdio.h>

int main(void){
	char c;
	int i;
	float f;
	double d;

	int ic, ii, ifloat, id;

	ic = scanf("%c", &c);
	ii = scanf("%d", &i);
	ifloat = scanf("%f", &f);
	id = scanf("%lf", &d);


	printf("Valor de %c retorno %d\n", c, ic);
	printf("Valor de %d retorno %d\n", i, ii);
	printf("Valor de %f retorno %d\n", f, ifloat);
	printf("Valor de %lf retorno %d\n", d, id);

	return 0;
}
