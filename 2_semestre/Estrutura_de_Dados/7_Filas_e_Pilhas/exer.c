#include <stdio.h>
#include <stdlib.h>

struct letra{
    char letra;
    struct letra *next;
};
typedef struct letra Letra;

struct pilha{
    Letra *top;
};
typedef struct pilha Pilha;

void pilha_cria(Pilha *p);
void pilha_push(Pilha *p, char l);
int pilha_vazia(Pilha *p);
char pilha_pop(Pilha *p);

int main(void){
    Pilha p;
    pilha_cria(&p);
    char palavra[31];

    printf("Digite uma palavra: ");
    scanf("%30s", palavra);

    printf("Criando pilha...\n");
    for(int i=0; palavra[i] != '\0'; i++){
        printf("Adicionando letra: %c\n", palavra[i]);
        pilha_push(&p, palavra[i]);
    }

    printf("Exibindo pilha:\n");
    while(!pilha_vazia(&p)){
        char l = pilha_pop(&p);
        printf("%c\n", l);
    }


    return 0;
}

void pilha_cria(Pilha *p){
    p->top = NULL;
}

void pilha_push(Pilha *p, char l){
    Letra *n = (Letra *) malloc(sizeof(Letra));

    if(n == NULL){
        printf("OOM\n");
        exit(1);
    }

    n->letra = l;
    n->next = p->top;
    p->top = n;
}

int pilha_vazia(Pilha *p){
    return (p->top == NULL);
}

char pilha_pop(Pilha *p){
    Letra *t = p->top;

    if(t == NULL){
        printf("A pilha está vazia!\n");
        exit(1);
    }

    char l = t->letra;
    p->top = t->next;
    free(t);
    return l;
}