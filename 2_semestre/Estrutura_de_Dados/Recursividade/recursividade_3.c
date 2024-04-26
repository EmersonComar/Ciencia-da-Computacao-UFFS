#include <stdio.h>

int mdc(int m, int n);

int main(void){
  int m, n;
  
  printf("Primeiro valor: ");
  scanf("%d", &m);
  
  printf("Segundo valor: ");
  scanf("%d", &n);
  
  if(m < 0 || n < 0){
    printf("Digite apenas valores não negativos\n");
    return 1;
  }
  
  printf("MDC(%d, %d): %d\n", m, n, mdc(m ,n));
  
  return 0;
}

int mdc(int m, int n){
  if(n == 0)
    return m;
  return mdc(n, m%n);
}
