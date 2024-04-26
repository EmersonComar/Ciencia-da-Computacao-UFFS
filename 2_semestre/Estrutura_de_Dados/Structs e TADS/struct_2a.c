#include <stdio.h>

struct fraction{
  int numerador;
  int denominador;
};
typedef struct fraction Fraction;

void setFraction(Fraction *fracao, int n, int d);
void exibeFraction(Fraction *fracao);

int main(void){
  Fraction f;
  setFraction(&f, 15, 43);
  exibeFraction(&f);
  
}

void setFraction(Fraction *fracao, int n, int d){
  fracao->numerador = n;
  fracao->denominador = d;
}

void exibeFraction(Fraction *fracao){
  printf("Numerador: %d\nDenominador: %d\n", fracao->numerador, fracao->denominador);
}
