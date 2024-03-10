#include <stdio.h>

void troca(int *px, int *py){
	int tmp = *px;
	*px = *py;
	*py = tmp;
}

int main(void){
	int a = 5, b = 7;
	troca(&a, &b);
	printf("%d %d\n", a, b);
	return 0;
}
