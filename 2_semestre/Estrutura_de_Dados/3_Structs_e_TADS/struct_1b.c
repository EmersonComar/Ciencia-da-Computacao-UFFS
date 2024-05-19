#include <stdio.h>

typedef struct{
	int dia;
	int mes;
	int ano;
}Data;

int comparaDatas(Data data1, Data data2);

int main(void){
	Data data1 = {15, 2, 1998};
	Data data2 = {15, 3, 1998};

	printf("Status de retorno: %d\n", comparaDatas(data1, data2));

	return 0;
}

int comparaDatas(Data data1, Data data2){
	if(data2.ano > data1.ano)
	  return -1;
	else if(data1.ano > data2.ano)
	  return 1;
	else if(data2.mes > data1.mes)
	  return -1;
	else if(data1.mes > data2.mes)
	  return 1;
	else if(data2.dia > data1.dia)
	  return -1;
	else if(data1.dia > data2.dia)
	  return 1;
	else
	  return 0;
}
