#include <stdio.h>

char maiuscula(char c){
	if(c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
	return c;
}

int main(void){
	char l;
	
	printf("Digite uma letra minuscula: ");
	scanf("%c", &l);

	printf("Representante maiúscula: %c\n", maiuscula(l));
	return 0;
}
