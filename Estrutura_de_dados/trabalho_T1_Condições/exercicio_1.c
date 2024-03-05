#include <stdio.h>

int main(void){
    int horasTrabalhadas;
    float valorHora, acrescimo;

    acrescimo = 1.0f;
    printf("Horas trabalhadas: ");
    scanf("%d", &horasTrabalhadas);

    printf("Valor da hora: ");
    scanf("%f", &valorHora);

    if(horasTrabalhadas > 200)
        acrescimo = 1.05f;
    
    printf("Salário: %.2f\n", (horasTrabalhadas * valorHora * acrescimo));
    return 0;
}