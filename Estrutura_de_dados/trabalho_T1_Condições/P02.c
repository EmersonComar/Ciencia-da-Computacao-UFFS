#include <stdio.h>

int main(void){
    float precoProduto;
    int formaPagamento;

    printf("Preço do produto: ");
    scanf("%f", &precoProduto);

    printf("Forma de pagamento:\n1 - À vista\n2 - A prazo\n-> ");
    scanf("%d", &formaPagamento);

    switch(formaPagamento){
        case 1:
            printf("Preço à vista: %.2f\n", (precoProduto * 0.95f));
            return 0;
        case 2:
            printf("Preço a prazo: %.2f\n", (precoProduto * 1.1f));
            return 0;
        default:
            printf("Forma de pagamento incorreta.\n");
            return 1;
    }
}