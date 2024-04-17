#include <stdio.h>

#define PI 3.14159F

float area(float r){
	return PI * r * r;
}

int main(void){
	float raio;
	scanf("%f", &raio);

	printf("A área do círculo de raio %f: %.2f", raio, area(raio));
	return 0;

}
