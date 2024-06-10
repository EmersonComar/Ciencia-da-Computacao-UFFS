#include <stdio.h>
#include <stdlib.h>

struct item{
    char abre;
    char fecha;
    struct item *next;
};
typedef struct item Item;

struct pilha{
    Item *top;
};
typedef struct pilha Pilha;

void pilha_cria(Pilha *p);
int pilha_validar(Pilha *p, char expressao[]);
void pilha_push(Pilha *p, char l);
int pilha_pop(Pilha *p, char l);
void pilha_limpar(Pilha *p);

int main(){
    Pilha p;
    pilha_cria(&p);
    char expressao[31];

    printf("Escreva uma expressão de []{}(): ");
    scanf("%30s", expressao);

    if(!pilha_validar(&p, expressao)){
        printf("Expressão incorreta!\n");

    }else{
        printf("Expressão correta!\n");

    }

    pilha_limpar(&p);
    return 0;
}

void pilha_cria(Pilha *p){
    p->top = NULL;
}

int pilha_validar(Pilha *p, char expressao[]){
    int validar = 1;

    for(int i=0; expressao[i] != '\0'; i++){
        if(expressao[i] == '[' || expressao[i] == '(' || expressao[i] == '{'){
            pilha_push(p, expressao[i]);

        }else if(expressao[i] == '}' || expressao[i] == ')' || expressao[i] == ']'){
            validar = pilha_pop(p, expressao[i]);
        }

        if(!validar)
            return validar;
    }

    return validar;
}

void pilha_push(Pilha *p, char l){
    Item *n = (Item *)malloc(sizeof(Item));

    if(n == NULL){
        printf("OOM\n");
        exit(1);
    }

    n->abre = l;

    if(l == '['){
        n->fecha = ']';

    }else if(l == '('){
        n->fecha = ')';

    }else if(l == '{'){
        n->fecha = '}';

    }else{
        printf("Erro inesperado\n");
        exit(1);
    }

    n->next = p->top;
    p->top = n;
}

int pilha_pop(Pilha *p, char l){
    if(p->top == NULL){
        return 0;
    }

    Item *t = p->top;
    char valor = t->fecha;

    p->top = t->next;
    free(t);

    return (valor == l);
}

void pilha_limpar(Pilha *p){
    Item *t = p->top;

    while(t != NULL){
        Item *n = t->next;

        free(t);
        t = n;
    }
}