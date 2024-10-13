#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *arquivo = fopen("bin/palavras.txt", "a");
    char texto[30];

    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo\n");
        return 1;
    }

    printf("Digite o texto que deseja incluir no arquivo:\n");
    scanf("%29[^\n]s", texto);

    if(fputs(texto, arquivo)){
        printf("Texto escrito com sucesso!\n");
    }else{
        fprintf(stderr, "Erro ao escrever texto no arquivo\n");
        return 1;
    }

    fclose(arquivo);
    return 0;
}