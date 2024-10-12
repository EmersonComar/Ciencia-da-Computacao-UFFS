// Include guard para evitar problemas de múltiplas inclusões
#ifndef LINEAR_H
#define LINEAR_H

typedef struct tlist Tlist;
typedef struct tqueue Tqueue;

// funções de geração
Tlist *gerar_lista(int *vetor, int tamanho_vetor);
int *gerar_vetor(Tlist *head);
void gerar_fila(Tqueue **head, Tqueue **tail, int *vetor, int tamanho_vetor);

// funções de exibição
void exibir_vetor(int *vetor, int tamanho_vetor);
void exibir_lista(Tlist *head);
void exibir_fila(Tqueue *head);

// função responsável por ordenar
void radixsort(int *vetor, int tamanho_vetor);

// funções para limpeza de memória
void liberar_memoria_lista(Tlist *head);
void liberar_memoria_vetor(int *vetor);
void liberar_memoria_fila(Tqueue *head);

#endif