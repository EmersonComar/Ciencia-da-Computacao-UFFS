#include <stdio.h>

void imprime(float a){
	static int n = 1;

	printf(" %f ", a);
	if(n % 5 == 0) printf(" \n");
	n++;
}

int main(void){
	float vetor[] = {1.2, 3.3, 54.4, 53.4, 87.2, 37.4, 1.1, 46.3, 3.6, 53.6, 43.2};
	int len = sizeof(vetor)/sizeof(vetor[0]);

	for(int i = 0; i < len; i++){
		imprime(vetor[i]);
	}

	return 0;

}
