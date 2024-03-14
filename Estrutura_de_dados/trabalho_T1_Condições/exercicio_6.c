#include <stdio.h>

int main(void){
	int idade;

	printf("Idade: ");
	scanf("%d", &idade);

	if(idade >= 18 && idade <= 70)
		printf("Voto obrigatório\n");
	else if(idade >= 16 || idade > 70)
		printf("Voto facultativo\n");
	else
		printf("Não pode votar\n");

	return 0;
}
