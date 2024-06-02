#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

struct funcionario{
    int id;
    double salario;
    Data nascimento;
    struct funcionario *next;
    struct funcionario *prev;
};
typedef struct funcionario Funcionario;

Funcionario *criarLista(int qtd);
void exibirLista(Funcionario *head);

int main(){
    Funcionario *head=NULL;

    head = criarLista(7);
    exibirLista(head);

    return EXIT_SUCCESS;
}

Funcionario *criarLista(int qtd){
    Funcionario *head=NULL, *aux;
    
    for(int i=1; i<=qtd; i++){
        Funcionario *novo = (Funcionario *) malloc(sizeof(Funcionario));
        
        novo->id = i;
        novo->salario = 1123.0 * i;
        novo->next = NULL;
        novo->prev = NULL;
        novo->nascimento.ano = 2000 + i;
        novo->nascimento.mes = (int)(i % 12) + 1;
        novo->nascimento.dia = (int)(i % 28) + 1;

        if(head == NULL){
            head = novo;
            aux = novo;
        }else{
            aux->next = novo;
            novo->prev = aux;
            aux = novo;
        }
        printf("Criado funcionario %d\n", i);
    }
    return head;
}

void exibirLista(Funcionario *head){
    for(Funcionario *aux = head; aux != NULL; aux = aux->next){
        printf("==============\n");
        printf("ID: %d\n", aux->id);
        printf("Data de nascimento: %d/%d/%d\n", aux->nascimento.dia, aux->nascimento.mes, aux->nascimento.ano);
        printf("Salário: R$%.2f\n", aux->salario);
    }
}