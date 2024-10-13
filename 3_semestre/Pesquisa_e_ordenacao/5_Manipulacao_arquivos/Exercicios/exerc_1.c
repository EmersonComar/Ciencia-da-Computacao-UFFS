#include <stdio.h>

int main(void){
    FILE *arquivo = fopen("bin/palavras.txt", "r");
    char c;
    int qtd = 0;

    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir arquivo. Existe?\n");
        return 1;
    }

    while(!feof(arquivo)){
        c = fgetc(arquivo);
        printf("%c", c);
        if(c == ' ' || c == '\n'){
            qtd++;
        }
    }

    printf("\n O texto acima possui %d palavras\n", qtd);


    fclose(arquivo);
    return 0;
}