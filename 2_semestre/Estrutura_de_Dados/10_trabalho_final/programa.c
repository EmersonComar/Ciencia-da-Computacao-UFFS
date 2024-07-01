#include "agenda.h"
#include <stdio.h>
#include <string.h>

int menu(){
    int opt;
    printf("\n=============\n");
    printf("     MENU\n");
    printf("=============\n");
    printf("1 - Adicionar tarefa\n");
    printf("2 - Remover tarefa\n");
    printf("3 - Visualizar todas as tarefas\n");
    printf("4 - Visualizar tarefas ativas\n");
    printf("5 - Visualizar tarefas concluídas\n");
    printf("6 - Concluir tarefa\n");
    printf("7 - Sair\n");
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

    while ((c = getchar()) != '\n' && c != EOF);

    if(consultarID(sentinel->root, id)){
        printf("\nEste ID já está em uso. Informe um novo\n");
        return;
    }

    printf("Digite uma breve descrição da tarefa: ");
    fgets(descricao, sizeof(descricao), stdin);

    if(descricao[strlen(descricao) - 1] == '\n')
        descricao[strlen(descricao) - 1] = '\0';

    printf("Digite o tempo estimado para a realização da tarefa(em horas): ");
    scanf("%f", &tempoLimite);

    sentinel->root = adicionarTarefa(sentinel->root, criarTarefa(id, descricao, tempoLimite));

    printf("\nA tarefa a seguir foi cadastrada:\n");
    exibirTarefa(retornarNodeTarefa(sentinel->root, id)->tarefa);
    printf("\n");
}

void apagarTarefa(Tree *sentinel){
    int id;

    printf("\n--- Removendo tarefa ---\n");
    printf("Digite um valor inteiro para o ID da tarefa: ");
    scanf("%d", &id);

    if(consultarID(sentinel->root, id)){
        printf("\nA tarefa a seguir será deletada:\n");
        exibirTarefa(retornarNodeTarefa(sentinel->root, id)->tarefa);
        removerTarefa(sentinel, id);
        printf("\n");
    }else{
            printf("\nID não cadastrado\n");
    }
}

int main(void){
    Tree sentinel;
    iniciarArvore(&sentinel);

    int opt = 0;

    do{
        opt = menu();

        switch(opt){
            case 1:
                cadastrarTarefa(&sentinel);
                break;
            case 2:
                apagarTarefa(&sentinel);
                break;
            case 7:
                break;
            default:
                printf("\nEscolha uma opção entre 1 e 6\n");
        }

    }while (opt != 7);



    destruirArvore(sentinel.root);
    return 0;
}
