#include <stdio.h>

int main(void){
    FILE *arquivo = fopen("bin/palavras.txt", "r");
    char c, p;
    int qtd = 0;

    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir arquivo.");
        return 1;
    }

    printf("Digite o caractere que deseja contar: ");
    scanf("%c", &p);

    while(!feof(arquivo)){
        c = fgetc(arquivo);
        if(c == p){
            qtd++;
        }
    }

    printf("O caractere \"%c\" aparece %d vezes no texto\n", p, qtd);

    fclose(arquivo);
    return 0;
}