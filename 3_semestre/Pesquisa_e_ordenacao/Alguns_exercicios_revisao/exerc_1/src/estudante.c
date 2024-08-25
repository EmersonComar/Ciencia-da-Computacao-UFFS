#include "estudante.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Estudante{
    char nome[50];
    int idade;
    float media;
};

struct Node{
    Estudante *estudante;
    struct Node *next;
};

void inicializa_lista(Node *head){
    head = NULL;
}


void adicionar_aluno(Node *head, Estudante *aluno){
    Node *novo = (Node *)malloc(sizeof(Node));

    novo->estudante = aluno;
    novo->next = NULL;

    if(head == NULL){
        head->next = novo;
    } else{

        Node *aux;
        for(aux = head; aux->next != NULL; aux = aux->next);
        
        aux->next = novo;
    }
}
 
Estudante *cadastrar_aluno(char *nome, int idade, float media){
    Estudante *novo = (Estudante *) malloc(sizeof(Estudante));

    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->media = media;

    return novo;
}

void percorrer_lista(Node *head){
    if(head == NULL){
        printf("Lista vazia! \n");
        return;
    }

    for(Node *aux = head->next; aux != NULL; aux = aux->next){
        printf("Nome: %s\n", aux->estudante->nome);
        printf("Idade: %d\n", aux->estudante->idade);
        printf("Média: %.2f\n", aux->estudante->media);
        printf("=====\n");
    }
}

void limpar_lista(Node *head){
    Node *atual = head->next;
    Node *prox;

    while(atual != NULL){
        prox = atual->next;
        free(atual->estudante);
        free(atual);
        atual = prox;
    }
}