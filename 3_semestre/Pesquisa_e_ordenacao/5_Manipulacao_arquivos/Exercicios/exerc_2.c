#include <stdio.h>
#include <stdlib.h>

FILE *abrir_arquivo(char *diretorio, char *modo);
void copiando_texto(FILE *scr, FILE* dst);
void fechando_arquivos(FILE *arquivo);

int main(void){
    FILE *arquivo = abrir_arquivo("bin/palavras.txt", "r");
    FILE *novo = abrir_arquivo("bin/novo_palavras.txt", "w");

    printf("Iniciando cópia do arquivo\n");
    copiando_texto(arquivo, novo);
    printf("Texto copiado com sucesso!\n");

    fechando_arquivos(arquivo);
    fechando_arquivos(novo);
    return 0;
}

FILE *abrir_arquivo(char *diretorio, char *modo){
    FILE *arquivo = fopen(diretorio, modo);

    if (arquivo == NULL){
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(1);
    }

    return arquivo;
}

void copiando_texto(FILE *scr, FILE* dst){
    char c;
    while (!feof(scr)){
        c = fgetc(scr);
        fprintf(dst, "%c", c);
    }
}

void fechando_arquivos(FILE *arquivo){
    fclose(arquivo);
}