#include <stdio.h>
#include <stdlib.h>

struct item{
    char abre;
    char fecha;
};
typedef struct item Item;

struct estack{
    Item elemento;
    struct estack *next;
};
typedef struct estack EStack;

struct stack{
    EStack *head;
};
typedef struct stack Stack;

void initStack(Stack *pilha);
void pushStack(Stack *pilha, char valor);
int isEmpty(Stack *pilha);
int popStack(Stack *pilha, char retirar);

int main(void){
    Stack pilha;
    char expressao[31];

    initStack(&pilha);
    
    printf("Digite uma expressão de parentese, colchetes e chaves: ");
    scanf("%30s", expressao);

    printf("Validando..\n");

    int valor;
    for(int i=0; expressao[i] != '\0'; i++){

        if(expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{'){
            pushStack(&pilha, expressao[i]);

        }else if(expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}'){
            valor = popStack(&pilha, expressao[i]);
        }

        if(valor == 0){
            printf("Expressão incorreta!\n");
            exit(0);
        }
    }

    if(isEmpty(&pilha)){
        printf("Expressão correta!\n");
    }else{
        printf("Expressão incorreta!\n");
    }


    return 0;
}

void initStack(Stack *pilha){
    pilha->head = NULL;
}

int isEmpty(Stack *pilha){
    return (pilha->head == NULL);
}

void pushStack(Stack *pilha, char valor){
    EStack *novo = (EStack *)malloc(sizeof(EStack));

    novo->next = NULL;
    novo->elemento.abre = valor;
    if(valor == '(')
        novo->elemento.fecha = ')';
    else if(valor == '[')
        novo->elemento.fecha = ']';
    else
        novo->elemento.fecha = '}';
    
    if(isEmpty(pilha)){
        pilha->head = novo;
    }else{
        novo->next = pilha->head;
        pilha->head = novo;
    }
}

int popStack(Stack *pilha, char retirar){
    if(isEmpty(pilha)){
        return 0;
    }

    if(pilha->head->elemento.fecha == retirar){
        EStack *aux = pilha->head;
        pilha->head = pilha->head->next;
        free(aux);
        return 1;
    }

    return 0;
}