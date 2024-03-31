#include <stdio.h>

typedef struct{
	int dia;
	int mes;
	int ano;
}Data;

int extraiDia(Data data);

int main(void){
	Data data = {15, 2, 1998};
	
	printf("O dia que foi definido na variável criada do tipo data: %d\n", extraiDia(data));

	return 0;
}

int extraiDia(Data data){
	return data.dia;
}
