#include <stdio.h>

int main(void){
	int entrada, metade;
	
	printf("Número: ");
	scanf("%d", &entrada);

	if(entrada % 2 != 0){
		metade = (entrada + 1) / 2;
	}else
		metade = entrada / 2;
	
	for(int i=1; i<= entrada; i++){
		printf("%d\n", i);
		if(i == metade)
			printf("Metade\n");
	}

	return 0;
}
