#include "agenda.h"
#include <stdio.h>

int main(void){
    Tree sentinel;

    iniciarArvore(&sentinel);

    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(1));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(4));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(6));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(2));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(7));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(9));

    inOrdem(sentinel.root);
    return 0;
}