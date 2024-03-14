#include <stdio.h>

int main(void){

	float num1, num2, resul;
	char op;

	printf("Digite: número op número\n");
	scanf("%f %c %f", &num1, &op, &num2);

	switch(op){
		case '+':
			resul = num1 + num2;
			break;
		case '-':
			resul = num1 - num2;
			break;
		case '*':
			resul = num1 * num2;
			break;
		case '/':
			resul = num1 / num2;
			break;
		default:
			printf("Operador inválido\n");
			return 0;
	}

	printf(" = %f\n", resul);

	return 0;
}
