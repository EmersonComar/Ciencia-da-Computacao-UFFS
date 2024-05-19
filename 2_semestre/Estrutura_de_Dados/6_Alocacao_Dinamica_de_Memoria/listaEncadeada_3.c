#include <stdio.h>
#include <stdlib.h>

struct funcionario{
  int id;
  struct funcionario *next;
};
typedef struct funcionario Funcionario;

void criar_lista(Funcionario **head, int tam);
void exibir_lista(Funcionario *head);
void inserir_depois(Funcionario **head, Funcionario *t, int id);
void liberar_lista(Funcionario *head);

int main(void){
  Funcionario *head=NULL;
  Funcionario *t = (Funcionario *) malloc(sizeof(Funcionario));
  
  t->id = 5;
  t->next = NULL;
  
  criar_lista(&head, 4);
  printf("Antes:\n");
  exibir_lista(head);
  inserir_depois(&head, t, 3);
  printf("Depois:\n");
  exibir_lista(head);
  liberar_lista(head);

  return 0;
}

void criar_lista(Funcionario **head, int tam){
  Funcionario *novo, *aux;
  
  for(int i=tam-1; i>=0; i--){
    novo = (Funcionario *) malloc(sizeof(Funcionario));
    novo->id = i;
    novo->next = NULL;
    
    if(*head == NULL){
      *head = novo;
      aux = novo;
    }else{
      aux->next = novo;
      aux = novo;
    }
  }
}

void exibir_lista(Funcionario *head){
  for(Funcionario *aux = head; aux != NULL; aux = aux->next)
    printf("ID [%d]\n", aux->id);
}

void liberar_lista(Funcionario *head){
  Funcionario *atual = head;
  Funcionario *prox;
  
  while(atual != NULL){
    prox = atual->next;
    free(atual);
    atual = prox;
  }
}

void inserir_depois(Funcionario **head, Funcionario *novo, int id){
  if(*head == NULL){
    *head = novo;
    return;
  }
  
  Funcionario *aux;
  
  for(aux=*head; aux->next != NULL; aux = aux->next){
    if(aux->id == id)
      break;
  }
  
  novo->next = aux->next;
  aux->next = novo;
}
