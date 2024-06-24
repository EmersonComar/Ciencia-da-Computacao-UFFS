#include <stdio.h>
#include <stdlib.h>

struct estack{
    char letra;
    struct estack *next;
};

typedef struct estack EStack;

struct stack{
    EStack *head;
};
typedef struct stack Stack;

void initStack(Stack *pilha);
void popStack(Stack *pilha, char letra);
EStack pushStack(Stack *pilha);
int isEmpty(Stack *pilha);

int main(void){
    Stack pilha;
    char palavra[21];

    initStack(&pilha);

    printf("Digite uma palavra: ");
    scanf("%20s", palavra);

    printf("Criando e insendo elementos na pilha...\n");

    for(int i=0; palavra[i] != '\0'; i++){
        popStack(&pilha, palavra[i]);
        printf("Letra %c inserida\n", palavra[i]);
    }

    printf("\nDesempilhando...\n");

    while(!isEmpty(&pilha)){
        EStack aux = pushStack(&pilha);

        if(aux.letra != -1){
            printf("%c ", aux.letra);
        }
    }
    printf("\n");

    return 0;
}

void initStack(Stack *pilha){
    pilha->head = NULL;
}

int isEmpty(Stack *pilha){
    return (pilha->head == NULL);
}

void popStack(Stack *pilha, char letra){
    EStack *novo = (EStack *)malloc(sizeof(EStack));

    novo->letra = letra;
    novo->next = NULL;

    if(isEmpty(pilha)){
        pilha->head = novo;
    }else{
        novo->next = pilha->head;
        pilha->head = novo;
    }
}

EStack pushStack(Stack *pilha){
    EStack aux;

    if(isEmpty(pilha)){
        aux.letra = -1;
        aux.next = NULL;
        return aux;
    }

    EStack *liberar = pilha->head;
    aux.letra = pilha->head->letra;

    pilha->head = pilha->head->next;
    free(liberar);

    return aux;
}