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

void cadastrarTarefa(Tree *sentinel){
    int id, c;
    char descricao[21];
    float tempoLimite;

    printf("\n--- Adicionado tarefa ---\n");
    printf("Digite um valor inteiro para o ID da tarefa: ");
    scanf("%d", &id);

    if(consultarID(sentinel->root, id)){
        printf("\nEste ID já está em uso. Informe um novo\n");
        return;
    }

    printf("Digite uma breve descrição da tarefa: ");
    fgets(descricao, sizeof(descricao), stdin);

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o tempo estimado para a realização da tarefa(em horas): ");
    scanf("%f", &tempoLimite);

    sentinel->root = adicionarTarefa(sentinel->root, criarTarefa(id, descricao, tempoLimite));

    printf("\nTarefa cadastrada!\n");

}

int main(void){
    Tree sentinel;
    ListaOrdenada lista;

    iniciarArvore(&sentinel);
    iniciarLista(&lista);

    int opt = 0;

    do{
        opt = menu();

        switch(opt){
            case 1:
                cadastrarTarefa(&sentinel);
                break;
            case 6:
                break;
            default:
                printf("\nEscolha uma opção entre 1 e 6\n");
        }

    }while (opt != 6);



    destruirArvore(sentinel.root);
    destruirLista(&lista);
    return 0;
}
