#include <stdio.h>
#include <stdlib.h>

struct sxy {
 
   int x;
   int y;
   struct sxy *next, *prev;
};
typedef struct sxy txy;

struct stag {
   txy *head;
   txy *tail;
};

typedef struct stag ttag;

void init_lista(ttag *t)
{
	t->head=NULL;
	t->tail=NULL;
}
void incluir (ttag *t,int x, int y)
{
   txy *novo = (txy *) malloc(sizeof(txy));
   novo->x = x;
   novo->y = y;
   novo->next = NULL;
   novo->prev = NULL;

   if(t->head == NULL){
      t->head = novo;
      t->tail = novo;
      printf("\nInserido com sucesso!\n\n");
      return;
   }

   txy *aux;
   for(aux = t->head; aux->next != NULL; aux = aux->next);
   aux->next = novo;
   aux->next->prev = t->tail;
   t->tail = novo;
   printf("\nInserido com sucesso!\n\n");
   return;

}

void consultar (ttag t,int x, int y)
{
   if(t.head == NULL){
      printf("\nNão existem elementos na lista\n\n");
      return;
   }
   
   txy *aux;

   for(aux = t.head; aux != NULL; aux = aux->next){
      if(aux->x == x && aux->y == y){
         printf("Endereço de memória: %p\n", aux);
	 printf(" X-> %d  Y-> %d\n", aux->x, aux->y);
	 printf("next aponta para: %p\n", aux->next);
	 printf("prev aponta para: %p\n", aux->prev);
	 printf("-------------\n");
	 return;
      }
   }
   printf("\nElemento não encontrado\n\n");
   return;
}

void excluir (ttag *t,int x, int y)
{
   if (t->head==NULL)
   {
      printf("\nNão existem elementos na lista\n\n");
      return;
   }
   
   txy *aux;
   
   for(aux = t->head; aux != NULL; aux = aux->next){
      if(aux->x == x && aux->y == y){
          printf("Endereço de memória do elemento: %p\n", aux);
	  if(aux == t->head){
	     if(aux->next == NULL){
	        t->head = NULL;
		t->tail = NULL;
	     }else{
	        t->head = aux->next;
		t->head->prev = NULL;
	     }
	  }else if(aux == t->tail){
	     t->tail = aux->prev;
	     t->tail->next = NULL;
	  }else{
	     aux->next->prev = aux->prev;
	     aux->prev->next = aux->next;
	  }

	  free(aux);
	  printf("Elemento localizado e excluído com suceso\n\n");
	  return;
      }
   }
   printf("\nElementos não encontrados\n\n");
   return;
}

void lista_todos(ttag t)
{
   if (t.head==NULL)
   {
      printf("\nNão existem elementos na lista\n\n");
      return;
   }
   
   txy *aux;
   printf("Valores presentes na lista:\n");
   for(aux = t.head; aux != NULL; aux = aux->next){
      printf("Endereço de memória: %p\n", aux);
      printf(" X-> %d  Y-> %d\n", aux->x, aux->y);
      printf("next aponta para: %p\n", aux->next);
      printf("prev aponta para: %p\n", aux->prev);
      printf("-----------------\n");
   }
   printf("Endereço de memória ao sair do loop: %p\n", aux);
   printf("\n");
}

int menu()
{
    int op;
    printf("1 - Incluir\n2 - Consultar\n3 - Excluir\n4 - Listar \n0 - Finalizar\n: ");
    scanf("%d",&op);
    return op;
}
//
int main()
{
   ttag tag;
   int op, x,y;
   init_lista(&tag);
   op=menu();
   while (op!=0)
   {
      switch(op)
      {
         case 1: scanf("%d %d",&x,&y);
                 incluir(&tag,x,y);
                 break;
         case 2: scanf("%d %d",&x,&y);
                 consultar(tag,x,y);
                 break;
         case 3: scanf("%d %d",&x,&y);
                 excluir(&tag,x,y);
                 break;
         case 4: lista_todos(tag);
                 break;
      }
      op=menu();
   }

}
