#include <stdio.h>

int main(void){
	int totalFilhos, totalEntradas, entradaFilhos;
	float totalSalarios, entradaSalarios;

	totalFilhos = totalSalarios = totalEntradas = 0;
	while(1){
		printf("Salário (valor < 0 para sair): ");
		scanf("%f", &entradaSalarios);

		totalEntradas++;

		if(entradaSalarios < 0){
			if(totalEntradas > 1)
				totalEntradas--;
			break;
		}

		printf("Filhos: ");
		scanf("%d", &entradaFilhos);

		if(entradaFilhos < 0){
			printf("Digite um valor igual ou maior que zero para filhos\n");
			continue;
		}

		totalSalarios += entradaSalarios;
		totalFilhos += entradaFilhos;
	}

	printf("Média salários: R$ %.2f\n", (float)totalSalarios/totalEntradas);
	printf("Média filhos: %.1f\n", (float)totalFilhos/totalEntradas);

	return 0;
}
