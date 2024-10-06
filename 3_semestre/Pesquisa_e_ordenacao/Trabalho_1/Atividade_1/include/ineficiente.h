#ifndef INEFICIENTE_H
#define INEFICIENTE_H

typedef struct tlist Tlist;
typedef struct tqueue Tqueue;

// funções de geração
Tlist *gerar_lista(int *vetor, int tamanho_vetor);
int *gerar_vetor(Tlist *head);

// funções de exibição
void exibir_vetor(int *vetor, int tamanho_vetor);
void exibir_lista(Tlist *head);

// função responsável por ordenar
void selectionsort(int *vetor, int tamanho_vetor);

// funções para limpeza de memória
void liberar_memoria_lista(Tlist *head);
void liberar_memoria_vetor(int *vetor);

#endif