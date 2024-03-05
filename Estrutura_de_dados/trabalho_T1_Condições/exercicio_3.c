#include <stdio.h>

int main(void){
    int inicio, fim, diferenca;
    printf("Início: ");
    scanf("%d", &inicio);

    printf("Fim: ");
    scanf("%d", &fim);

    if(inicio < 0 || inicio > 23 || fim < 0 || fim > 23){
        printf("Digite valores entre 0 e 23\n");
        return 1;
    }

    if (fim >= inicio)
        diferenca = fim - inicio;
    else 
        diferenca = 24 - inicio + fim;
    
    printf("Duração: %d hora(s)\n", diferenca);
    return 0;
}