#include <stdio.h>


void exibirBit(  char byte){
    for(int i = 7; i >= 0; i--){
        printf("%d", (byte >> i) & 1);
    }
    printf(" ");
}

int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "rb");
    if(arquivo == NULL){
        fprintf(stderr, "Erro ao abrir arquivo %s\n", argv[1]);
        return 1;
    }

      char byte;
    while (fread(&byte, sizeof(  char), 1, arquivo) == 1) {
        exibirBit(byte);
    }

    printf("\n");
    fclose(arquivo);
    return 0;
}