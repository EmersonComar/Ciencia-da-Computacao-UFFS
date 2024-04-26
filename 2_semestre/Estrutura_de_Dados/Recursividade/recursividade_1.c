#include <stdio.h>

int potencia(int base, int expoente);

int main(void){
  int base, expoente;
  
  printf("Digite a base: ");
  scanf("%d", &base);
  
  printf("Digite o expoente (e>=0): ");
  scanf("%d", &expoente);
  
  if(expoente < 0){
    printf("Digite um expoente não negativo\n");
    return 1;
  }
  
  printf("%d ^ %d: %d\n", base, expoente, potencia(base, expoente));
  
  return 0;
}

int potencia(int base, int expoente){
  if(expoente == 0)
    return 1;
  if(expoente == 1)
    return base;
  
  return base * potencia(base, expoente-1);
}
