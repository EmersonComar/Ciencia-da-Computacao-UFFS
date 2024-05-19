#include <stdio.h>

struct fraction{
  int numerador;
  int denominador;
};
typedef struct fraction Fraction;

void setFraction(Fraction *fracao, int n, int d);
void exibeFraction(Fraction *fracao);
Fraction multFraction(Fraction *f1, Fraction *f2);

int main(void){
  Fraction f1, f2, f3;
  setFraction(&f1, 15, 43);
  setFraction(&f2, 1, 2);
  f3 = multFraction(&f1, &f2);
  exibeFraction(&f3);
  
}

void setFraction(Fraction *fracao, int n, int d){
  fracao->numerador = n;
  fracao->denominador = d;
}

void exibeFraction(Fraction *fracao){
  printf("Numerador: %d\nDenominador: %d\n", fracao->numerador, fracao->denominador);
}

Fraction multFraction(Fraction *f1, Fraction *f2){
  Fraction f3 = {f1->numerador * f2->numerador, f1->denominador * f2->denominador};
  return f3;
}
