#include "agenda.h"
#include <stdio.h>
#include <string.h>

void limpezaBuffer();
void retornarMenu();
void limparTela();
int menu();
void cadastrarTarefa(Tree *sentinel);
void apagarTarefa(Tree *sentinel);
void listarTodos(Tree *sentinel);
void concluirTarefa(Tree *sentinel);
void listarAtivas(Tree *sentinel);
void listarConcluidas(Tree *sentinel);
void listarInOrdem(Tree *sentinel);

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
            case 3:
                concluirTarefa(&sentinel);
                break;
            case 4:
                listarTodos(&sentinel);
                break;
            case 5:
                listarAtivas(&sentinel);
                break;
            case 6:
                listarConcluidas(&sentinel);
                break;
            case 7:
                listarInOrdem(&sentinel);
                break;
            case 8:
                break;
            default:
                printf("\nEscolha uma opção entre 1 e 6\n");
                retornarMenu();
        }

    }while (opt != 8);



    destruirArvore(sentinel.root);
    return 0;
}

void limparTela(){
    printf("\033[2J\033[1;1H");
}

void listarInOrdem(Tree *sentinel){
    limparTela();
    printf("\n--- Exibindo as tarefas em ordem ID ---\n");
    inOrdem(sentinel->root);
    retornarMenu();
}

void listarConcluidas(Tree *sentinel){
    limparTela();
    ListaOrdenada listaConcluido;

    iniciarLista(&listaConcluido);

    ordenarSituacao(sentinel->root, &listaConcluido, "concluido");
    
    printf("\n--- Exibindo as tarefas concluidas ---\n");
    exibirLista(&listaConcluido);

    retornarMenu();
    destruirLista(&listaConcluido);
}

void listarAtivas(Tree *sentinel){
    limparTela();
    ListaOrdenada listaAtivo;

    iniciarLista(&listaAtivo);

    ordenarSituacao(sentinel->root, &listaAtivo, "ativo");
    
    printf("\n--- Exibindo as tarefas ativas ---\n");
    exibirLista(&listaAtivo);

    retornarMenu();

    destruirLista(&listaAtivo);
}

void retornarMenu(){
    printf("\n--Aperte [enter] para retornar--\n");
    getchar();
    limpezaBuffer();
}

void limpezaBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

int menu(){
    int opt;
    printf("\033[2J\033[1;1H");
    printf("\n=============\n");
    printf("     MENU\n");
    printf("=============\n");
    printf("1 - Adicionar tarefa\n");
    printf("2 - Remover tarefa\n");
    printf("3 - Concluir tarefa\n");
    printf("------\n");
    printf("4 - Visualizar todas as tarefas\n");
    printf("5 - Visualizar tarefas ativas\n");
    printf("6 - Visualizar tarefas concluídas\n");
    printf("7 - Visualizar tarefas em ordem ID\n");
    printf("------\n");
    printf("8 - Sair\n");
    printf("-> ");
    scanf("%d", &opt);
    return opt;
}

void cadastrarTarefa(Tree *sentinel){
    limparTela();

    int id;
    char descricao[21];
    float tempoLimite;

    printf("\n--- Adicionado tarefa ---\n");
    printf("Digite um valor inteiro para o ID da tarefa: ");
    scanf("%d", &id);

    limpezaBuffer();

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

    retornarMenu();
}

void apagarTarefa(Tree *sentinel){
    limparTela();
    int id;

    printf("\n--- Removendo tarefa ---\n");
    printf("Digite um valor inteiro para o ID da tarefa: ");
    scanf("%d", &id);

    if(consultarID(sentinel->root, id)){
        printf("\nA tarefa a seguir será deletada:\n");
        exibirTarefa(retornarNodeTarefa(sentinel->root, id)->tarefa);
        removerTarefa(sentinel, id);
    }else{
            printf("\nTarefa não cadastrada");
    }

    retornarMenu();
}

void listarTodos(Tree *sentinel){
    limparTela();
    
    ListaOrdenada listaAtivo;
    ListaOrdenada listaConcluido;

    iniciarLista(&listaAtivo);
    iniciarLista(&listaConcluido);

    ordenarSituacao(sentinel->root, &listaAtivo, "ativo");
    ordenarSituacao(sentinel->root, &listaConcluido, "concluido");
    
    printf("\n--- Exibindo todas as tarefa ---\n");
    exibirLista(&listaAtivo);
    exibirLista(&listaConcluido);

    retornarMenu();

    destruirLista(&listaAtivo);
    destruirLista(&listaConcluido);

    
}

void concluirTarefa(Tree *sentinel){
    int id;

    printf("\n--- Concluindo tarefa ---\n");
    printf("Digite um valor inteiro para o ID da tarefa: ");
    scanf("%d", &id);

    if(consultarID(sentinel->root, id)){
        printf("\nA tarefa a seguir foi marcada como concluída:\n");
        alterarStatus(sentinel->root->tarefa);
        exibirTarefa(retornarNodeTarefa(sentinel->root, id)->tarefa);
    }else{
            printf("\nTarefa não cadastrada");
    }

    retornarMenu();
}

