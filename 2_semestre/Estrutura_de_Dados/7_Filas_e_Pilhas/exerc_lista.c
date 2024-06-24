#include <stdio.h>
#include <stdlib.h>

struct equeue{
    char letra;
    struct equeue *next;
};
typedef struct equeue EQueue;

struct queue{
    EQueue *head;
    EQueue *tail;
};
typedef struct queue Queue;


void initQueue(Queue *fila);
void enQueue(Queue *fila, char letra);
int isEmpty(Queue *fila);
EQueue deQueue(Queue *fila);

int main(){
    Queue fila;
    char palavra[21];


    initQueue(&fila);

    printf("Digite uma palavra: ");
    scanf("%20s", palavra);

    printf("Palavra: %s\n", palavra);
    printf("Criando e alimantando a lista...\n");



    for(int i=0; palavra[i]!='\0'; i++){
        enQueue(&fila, palavra[i]);
        printf("letra %c adicionada\n", palavra[i]);
    }

    printf("\nExibindo...\n");

    while(!isEmpty(&fila)){
        EQueue aux = deQueue(&fila);

        if(aux.letra != -1)
            printf("%c ", aux.letra);
        
    }
    printf("\n");
    return 0;
}

void initQueue(Queue *fila){
    fila->head = NULL;
    fila->tail = NULL;
}

int isEmpty(Queue *fila){
    return (fila->head == NULL);
}

void enQueue(Queue *fila, char letra){
    EQueue *novo = (EQueue *)malloc(sizeof(EQueue));

    novo->letra = letra;
    novo->next = NULL;

    if(isEmpty(fila)){
        fila->head = novo;
        fila->tail = novo;
    }else{
        fila->tail->next = novo;
        fila->tail = novo;
    }
}

EQueue deQueue(Queue *fila){
    EQueue aux;

    if(isEmpty(fila)){
        aux.letra = -1;
        aux.next = NULL;
        return aux;
    }

    EQueue *liberar = fila->head;
    aux.letra = fila->head->letra;

    if(fila->head == fila->tail){
        initQueue(fila);
    }else{
        fila->head = fila->head->next;
    }

    free(liberar);
    return aux;
}