#include "agenda.h"
#include <stdio.h>

int menu(){
    int opt;
    printf("1 - Adicionar tarefa\n");
    printf("2 - Remover tarefa\n");
    printf("3 - Visualizar todas as tarefas\n");
    printf("4 - Visualizar tarefas ativas\n");
    printf("5 - Visualizar tarefas concluídas\n");
    printf("6 - Concluir tarefa\n");
    printf("-> ");
    scanf("%d", &opt);
    return opt;
}

int main(void){
    Tree sentinel;
    ListaOrdenada lista;

    iniciarArvore(&sentinel);
    iniciarLista(&lista);

    int opt = 0;

    do{
        opt = menu();

    }while (opt != 6);



    destruirArvore(sentinel.root);
    destruirLista(&lista);
    return 0;
}
