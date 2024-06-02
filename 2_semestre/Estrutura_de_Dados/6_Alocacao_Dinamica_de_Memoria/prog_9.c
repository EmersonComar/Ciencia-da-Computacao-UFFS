#include <stdio.h>
#include <stdlib.h>

struct time{
    char nome;
    int saldoGols;
    int pontos;
    struct time *next;
    struct time *prev;
};
typedef struct time Time;

struct tabela{
    Time *head;
    Time *tail;
};
typedef struct tabela Tabela;

void inicializarTabela(Tabela *brasilerao);
void adicionaTimes(Tabela *brasilerao ,int qtdTimes);
void exibeTimes(Tabela *brasilerao);
void limparTabela(Time *time);

int main(){
    Tabela brasilerao;
    inicializarTabela(&brasilerao);
    adicionaTimes(&brasilerao, 6);
    exibeTimes(&brasilerao);
    limparTabela(brasilerao.head);
    return 0;
}

void inicializarTabela(Tabela *brasilerao){
    brasilerao->head = NULL;
    brasilerao->tail = NULL;
}

void adicionaTimes(Tabela *brasilerao, int qtdTimes){
    Time *aux;
    char time = 65;

    for(int i=1; i<=qtdTimes; i++){
        Time *novo = (Time *)malloc(sizeof(Time));
        novo->nome = time;
        novo->pontos = 0;
        novo->saldoGols = 0;
        novo->next = NULL;
        novo->prev = NULL;

        if(brasilerao->head == NULL){
            brasilerao->head = novo;
            aux = novo;
            brasilerao->tail = novo;
        }else{
            aux->next = novo;
            novo->prev = aux;
            brasilerao->tail = novo;
            aux = novo;
        }
        time++;
    }
}

void exibeTimes(Tabela *brasilerao){
    for(Time *aux = brasilerao->head; aux != NULL; aux = aux->next){
        printf("=============\n");
        printf("Time: %c\n", aux->nome);
        printf("Pontos: %d\n", aux->pontos);
        printf("Saldo de gols: %d\n", aux->saldoGols);
    }
}

void limparTabela(Time *time){
    Time *aux = time;

    if(aux != NULL){
        limparTabela(aux->next);
    }
    free(aux);
}