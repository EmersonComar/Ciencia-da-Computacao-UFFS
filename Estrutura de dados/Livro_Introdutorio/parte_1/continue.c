#include  <stdio.h>

int main(void){
	int i;
	for(i = 0; i < 10; i++){
		if (i ==5) continue;
		printf("%d ", i);
	}
	printf("Fim\n");

	return 0;
}
