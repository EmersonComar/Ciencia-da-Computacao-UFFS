#include <stdio.h>
#include <stdlib.h>

struct lista{
    int valor;
    struct lista *next;
};
typedef struct lista Lista;

struct pilha{
    Lista *primeiro;
};
typedef struct pilha Pilha;

Pilha *pilha_cria();
void pilha_push(Pilha *p, int valor);
int pilha_pop(Pilha *p);
int pilha_vazia(Pilha *p);
void pilha_libera(Pilha *p);

int main(void){

    Pilha *p = pilha_cria();

    return 0;
}

Pilha *pilha_cria(){
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    p->primeiro = NULL;
    return p;
}

void pilha_push(Pilha *p, int valor){
    Lista *n = (Lista *) malloc(sizeof(Lista));
    n->valor = valor;
    n->next = p->primeiro;
    p->primeiro = n;
}

int pilha_pop(Pilha *p){
    Lista *t;
    int v;
    if(pilha_vazia(p)){
        printf("A pilha está vazia\n");
        exit(1);
    }

    t = p->primeiro;
    v = t->valor;
    p->primeiro = t->next;
    free(t);
    return v;
}

int pilha_vazia(Pilha *p){
    return (p->primeiro == NULL);
}


void pilha_libera(Pilha *p){
    Lista *q = p->primeiro;
    while(q!=NULL){
        Lista *t = q->next;
        free(q);
        q = t;
    }
    free(p);
}