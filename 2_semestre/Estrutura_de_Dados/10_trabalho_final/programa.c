#include "agenda.h"
#include <stdio.h>

int main(void){
    Tree sentinel;

    iniciarArvore(&sentinel);
    
    
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(2, "Basaltica", 10.4f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(9, "Trabalho prog", 8.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(11, "DaCasa", 15.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(16, "Boliche", 3.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(14, "kart", 2.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(13, "puteiro", 2.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(12, "Cineminha", 2.0f));
    sentinel.root = adicionarTarefa(sentinel.root, criarTarefa(1, "Cineminha", 2.0f));

    inOrdem(sentinel.root);

    int id = 4;

    if(consultarID(sentinel.root, id)){
        printf("ID encontrado\n");
        exibirTarefa(retornarNodeTarefa(sentinel.root, id));
    }else{
        printf("ID não encontrado\n");
    }

    if(removerTarefa(&sentinel, 2)){
        printf("\nNó 2 removido com sucesso\n");
    }


    inOrdem(sentinel.root);

    destruirArvore(sentinel.root);
    return 0;
}
