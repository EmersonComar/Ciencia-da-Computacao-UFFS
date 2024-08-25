#include "numero.h"
#include <stdio.h>

int main(void){
    Node *head;
    inicializa_node(head);


    adiciona_node(head, 3);
    adiciona_node(head, 5);
    adiciona_node(head, 6);
    adiciona_node(head, 8);
    adiciona_node(head, 2);
    adiciona_node(head, 5);

    percorrer_lista(head);

    limpar_lista(head);
}