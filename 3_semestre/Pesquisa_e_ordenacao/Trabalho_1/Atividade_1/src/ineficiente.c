#include "ineficiente.h"
#include <stdio.h>
#include <stdlib.h>

struct tlist {
    int valor;
    struct tlist *next;
};

struct tqueue {
    int valor;
    struct tqueue *next;
};

//funções privadas
Tlist *node_lista(int valor){
    Tlist *node = (Tlist*)malloc(sizeof(Tlist));

    // Caso ocorrer um erro na alocação dinâmica, o programa será encerrado
    // gerando uma mensagem na saída de erro padrão.
    if(node == NULL){
        fprintf(stderr, "Erro ao alocar memória para lista\n");
        exit(1);
    }

    node->valor = valor;
    node->next = NULL;

    return node;
}



// funções públicas
Tlist *gerador_lista(int *vetor, int tamanho_vetor){
    
    Tlist *head = NULL;
    Tlist *aux = NULL;

    for(int i=0; i<tamanho_vetor; i++){

        Tlist *node = node_lista(vetor[i]);
        if(head == NULL){
            head = node;
            aux = node;
        } else{
            aux->next = node;
            aux = node;
        }
    }

    return head;
}

void liberar_memoria(Tlist *head){
    Tlist *aux = head;

    while (aux != NULL){
        Tlist *prox = aux->next;
        free(aux);

        aux = prox;
    }
}