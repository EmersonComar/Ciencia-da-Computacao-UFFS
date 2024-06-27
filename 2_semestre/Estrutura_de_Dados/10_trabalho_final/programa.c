#include "agenda.h"
#include <stdio.h>

int main(void){
    Tree sentinel;

    iniciarArvore(&sentinel);

    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(1));

    return 0;
}