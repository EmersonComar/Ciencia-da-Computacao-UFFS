#include <stdio.h>

int main(void){
	char operacao;
	float valor1, valor2, resul;
	
	while (1){
		printf("\nDigite a operação que deseja realizar:\n");
		printf("/ (divisão)\n");
		printf("* (multiplicação)\n");
		printf("- (subtração)\n");
		printf("+ (soma)\n");
		printf("@ -> sair do programa\n");
		printf("-> ");
		scanf("%c", &operacao);
		

		if(operacao == '@')
			return 0;

		if(operacao != '/' && operacao != '*' && operacao != '-' && operacao != '+'){
			printf("\nDigite uma operação válida\n");
			continue;
		}

		printf("Digite o primeiro valor: ");
		scanf("%f", &valor1);

		printf("Digite o segundo valor: ");
		scanf("%f", &valor2);

		switch(operacao){
			case '/':
				resul = valor1 / valor2;
				break;
			case '*':
				resul = valor1 * valor2;
				break;
			case '-':
				resul = valor1 - valor2;
				break;
			case '+':
				resul = valor1 + valor2;
				break;
		}

		printf("\nResultado: %.2f %c %.2f = %.2f\n", valor1, operacao, valor2, resul);
	}
	return 0;
}
