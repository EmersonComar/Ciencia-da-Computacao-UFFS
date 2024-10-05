#ifndef INEFICIENTE_H
#define INEFICIENTE_H

typedef struct tlist Tlist;
typedef struct tqueue Tqueue;

Tlist *gerador_lista(int *vetor, int tamanho_vetor);
void liberar_memoria(Tlist *head);

#endif