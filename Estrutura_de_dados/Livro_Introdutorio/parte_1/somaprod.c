#include <stdio.h>

void somaprod(int a, int b, int *s, int *p){
	*s = a + b;
	*p = a * b;
}

int main(void){
	int s, p;
	somaprod(3 , 5, &s, &p);
	printf("Soma: %d\nProduto: %d\n", s, p);
	return 0;
}
