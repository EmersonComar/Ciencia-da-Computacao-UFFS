#include "eficiente.h"
#include <stdio.h>
#include <stdlib.h>


// ============== Declaração das structs ============
struct tlist {
    int valor;
    struct tlist *next;
};

struct tqueue {
    int valor;
    struct tqueue *next;
};
//=========================

// ============== funções privadas ===================

Tlist *node_lista(int valor){
    Tlist *node = (Tlist*)malloc(sizeof(Tlist));

    if(node == NULL){
        fprintf(stderr, "Erro ao alocar memória para lista\n");
        exit(1);
    }

    node->valor = valor;
    node->next = NULL;

    return node;
}

void troca(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

Tqueue *node_fila(int valor){
    Tqueue *node = (Tqueue *)malloc(sizeof(Tqueue));

    if(node == NULL){
        fprintf(stderr, "Erro ao alocar memória para fila!\n");
        exit(1);
    }

    node->valor = valor;
    node->next = NULL;

    return node;
}

int particao(int *vetor, int inicio, int fim){
    int pivo = vetor[fim];
    int k = inicio - 1;

    for(int i = inicio; i<fim; i++){
        if(vetor[i] <= pivo){
            k++;
            troca(&vetor[k], &vetor[i]);
        }
    }
   // if(vetor[k] > vetor[fim])
        troca(&vetor[k + 1], &vetor[fim]);

    return k + 1;
}
// ====================================================


// ============== funções públicas ====================

// Funções de geração

Tlist *gerar_lista(int *vetor, int tamanho_vetor){
    
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

/*
 * Primeiramente irá precorrer a lista encadeada calculando a quantidade de nodes. Depois, irá 
 * alocar o espaço de memória corretamente. E, por fim, percorrer novamente a lista encadeada 
 * adicionando os valores ao vetor
*/
int *gerar_vetor(Tlist *head){
    int tamanho_vetor = 0;
    int *vetor = NULL;

    for(Tlist *aux = head; aux != NULL; aux = aux->next){
        tamanho_vetor++;
    }

    vetor = (int *)malloc(tamanho_vetor * sizeof(int));

    if(vetor == NULL){
        fprintf(stderr, "Erro ao gerar vetor\n");
        exit(1);
    }

    int i=0;
    for(Tlist *aux = head; aux != NULL; aux = aux->next){
        vetor[i] = aux->valor;
        i++;
    }

    return vetor;
}

/*
 * Será necessário utilizar ponteiros para ponteiros para que a alteração se 
 * aplique nas variáveis originais. 
*/

void gerar_fila(Tqueue **head, Tqueue **tail, int *vetor, int tamanho_vetor){

    for(int i=0; i<tamanho_vetor; i++){

        Tqueue *node = node_fila(vetor[i]);
        if(*head == NULL){
            *head = node;
            *tail = node;
        } else {
            (*tail)->next = node;
            *tail = node;
        }
    }
}
// ================================


// Funções de exibição

void exibir_vetor(int *vetor, int n){
    printf("{");
    for(int i=0; i<n-1; i++){
        printf("%d, ", vetor[i]);
    }
    printf("%d}\n", vetor[n-1]);
}

void exibir_lista(Tlist *head){
    if(head == NULL){
        printf("Lista vazia!\n");
        return;
    }

    Tlist *aux;    
    for(aux = head; aux->next != NULL; aux = aux->next){
        printf("%d -> ", aux->valor);
    }

    printf("%d\n", aux->valor);
}

void exibir_fila(Tqueue *head){
    if(head == NULL){
        printf("Fila vazia!\n");
        return;
    }

    Tqueue *aux;
    for(aux = head; aux->next != NULL; aux = aux->next){
        printf("%d < ", aux->valor);
    }
    printf("%d\n", aux->valor);
}
// =======================================

// Algoritmo de ordenação
void quicksort(int *vetor, int inicio, int fim){
    if (inicio < fim){
        int pivo = particao(vetor, inicio, fim);
        quicksort(vetor, 0, pivo-1);
        quicksort(vetor, pivo+1, fim);
    }
}
// ==================================

// Limpezas de memória
void liberar_memoria_lista(Tlist *head){
    Tlist *aux = head;

    while (aux != NULL){
        Tlist *prox = aux->next;
        free(aux);
        aux = prox;
    }
}

void liberar_memoria_vetor(int *vetor){
    free(vetor);
}

void liberar_memoria_fila(Tqueue *head){
    Tqueue *aux = head;
    while(aux != NULL){
        Tqueue *prox = aux->next;
        free(aux);
        aux = prox;
    }
}
// ==================================