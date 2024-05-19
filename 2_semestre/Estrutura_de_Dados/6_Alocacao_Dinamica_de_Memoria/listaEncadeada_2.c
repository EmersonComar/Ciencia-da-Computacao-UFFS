#include <stdio.h>
#include <stdlib.h>

struct date{
  int dia;
  int mes;
  int ano;
};
typedef struct date Date;

struct employee{
  int id;
  char name[41];
  double income;
  Date dbirth;
  struct employee *next;
};
typedef struct employee Employee;

Employee *preenche_lista();
void exibe_lista(Employee *head);
void finaliza_lista(Employee *head);

int main(void){
  Employee *head;
  
  head = preenche_lista();
  exibe_lista(head);
  finaliza_lista(head);
  
  return 0;
}

void finaliza_lista(Employee *head){
  Employee *atual = head;
  Employee *prox;
  
  while(atual != NULL){
    prox = atual->next;
    free(atual);
    atual = prox;
  }
}

void exibe_lista(Employee *head){
  for(Employee *aux = head; aux != NULL; aux = aux->next){
    printf("ID: %d\n", aux->id);
    printf("Nome: %s\n", aux->name);
    printf("Renda: R$ %.2f\n", aux->income);
    printf("Data de nascimento: %d/%2d/%d\n\n", aux->dbirth.dia, aux->dbirth.mes, aux->dbirth.ano);
  }
}

Employee *preenche_lista(){
  Employee *aux, *head=NULL;
  
  for(;;){
    Employee *novo = (Employee *) malloc(sizeof(Employee));
    printf("ID do funcionário (0 = sair): ");
    scanf("%d", &novo->id);
    
    if(novo->id == 0){
      free(novo);
      return head;
    }
    
    __fpurge(stdin);
    
    printf("Funcionário ID %d\n", novo->id);
    printf("Nome: ");
    scanf("%41s", novo->name);
    
    printf("Renda: ");
    scanf("%lf", &novo->income);
    
    printf("Data de nascimento:\n");
    printf("Dia: ");
    scanf("%d", &novo->dbirth.dia);
    printf("Mês: ");
    scanf("%d", &novo->dbirth.mes);
    printf("Ano: ");
    scanf("%d", &novo->dbirth.ano);
    
    novo->next = NULL;
    
    if(head != NULL){
      aux->next = novo;
      aux = novo;
    }else{
      head = novo;
      aux = novo;
    }
    printf("\n");
  }
}
