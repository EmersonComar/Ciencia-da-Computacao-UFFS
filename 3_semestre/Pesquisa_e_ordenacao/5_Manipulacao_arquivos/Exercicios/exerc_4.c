#include <stdio.h>

int main(void){
    FILE *arquivo = fopen("bin/palavras.txt", "r");
    char procurar;
    char linha[100];

    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    printf("Exibir linha que inicia com o caractere: ");
    scanf("%c", &procurar);

    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        if(linha[0] == procurar){
            printf("%s", linha);
        }
    }

    fclose(arquivo);
    return 0;
}