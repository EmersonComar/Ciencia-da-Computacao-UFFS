#include <stdio.h>

struct ponto{
	float x;
	float y;
};

int main(void){
	struct ponto p;

	printf("Digite as coordenadas do ponto(x y): ");
	scanf("%f %f", &p.x, &p.y);

	printf("O ponto fornecido foi: (%.2f, %.2f)\n", p.x, p.y);
	printf("O tamanho da estrutura de dados em bytes: %ld\n", sizeof(p));
	return 0;

}
