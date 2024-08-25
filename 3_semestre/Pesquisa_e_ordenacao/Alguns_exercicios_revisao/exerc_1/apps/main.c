#include "estudante.h"
#include <stdio.h>

int main(void){
    Node *head;
    inicializa_lista(head);

    adicionar_aluno(head, cadastrar_aluno("Emerson", 26, 6.7));
    adicionar_aluno(head, cadastrar_aluno("Francisco", 24, 7.2));
    adicionar_aluno(head, cadastrar_aluno("Victor", 23, 8.4));

    percorrer_lista(head);

    limpar_lista(head);
    return 0;
}