#include "agenda.h"
#include <stdio.h>

int main(void){
    Tree sentinel;

    iniciarArvore(&sentinel);
    
    
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(2, "Basaltica", 10.4f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(9, "Trabalho prog", 8.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(10, "DaCasa", 15.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(3, "Boliche", 3.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(7, "kart", 2.0f));

    inOrdem(sentinel.root);
    return 0;
}
