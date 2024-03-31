#include <stdio.h>

int soma(int a, int b){
	int c;
	c = a + b;
	return c;
}

int main(void){
	int s;

	s = soma(3, 5);
	printf("Soma = %d\n", s);
	return 0;
}
