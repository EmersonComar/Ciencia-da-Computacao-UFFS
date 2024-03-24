#include <stdio.h>

int main() {
    float alturaAntonio = 1.50;
    float alturaCarlos = 1.10; 
    float taxaCrescimentoAntonio = 0.02;
    float taxaCrescimentoCarlos = 0.03;
    int anos = 0; 

    while (alturaCarlos < alturaAntonio) {
        alturaAntonio += alturaAntonio * taxaCrescimentoAntonio;
        alturaCarlos += alturaCarlos * taxaCrescimentoCarlos;
        anos++;
    }

    printf("Serão necessários %d anos para que Carlos tenha a mesma altura que Antonio.\n", anos);

    return 0;
}

