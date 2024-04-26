#include <stdio.h>

float media (int n, float *v){
	int i;
	float s = 0.0f;
	for (i = 0; i < n; i++)
		s += v[i];
	return s/n;
}

float variancia (int n, float *v, float m){
	int i;
	float s = 0.0f;
	for (i = 0; i < n; i++)
		s += (v[i] - m) * (v[i] - m);
	return s/n;
}

int main(void){
	float v[10];
	float med, var;
	int i;

	for (i = 0; i < 10; i++){
		printf("Valor %d: ", i+1);
		scanf("%f", &v[i]);
	}

	med = media(10 , v);
	var = variancia(10, v, med);
	
	printf("Média: %.2f  Variância: %.2f\n", med, var);

	return 0;
}
