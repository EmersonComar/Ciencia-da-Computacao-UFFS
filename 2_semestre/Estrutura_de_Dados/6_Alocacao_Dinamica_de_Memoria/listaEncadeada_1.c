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
  struct emloyee *next;
};
typedef struct employee Employee;



int main(void){
  Employee *head=NULL, *aux, *novo;
  
  for(int i=0; i<3; i++){
    novo = (Employee *) malloc(sizeof(Employee));
    novo->id = i;
    
    printf("Funcionário %d\n", i+1);
    printf("Nome: ");
    fgets(novo->name, 41, stdin);
    
    printf("Renda: ");
    scanf("%lf", &novo->income);
  
    printf("Aniversário:\n");
    printf("Dia: ");
    scanf("%d", &novo->dbirth.dia);
    printf("Mês: ");
    scanf("%d", &novo->dbirth.mes);
    printf("Ano: ");
    scanf("%d", &novo->dbirth.ano);
    
    __fpurge(stdin);
    
    novo->next = NULL;
    
    if(head == NULL){
      head = novo;
      aux = novo;
    }else{
      aux->next = novo;
      aux = novo;
    }
  }
  
  
  for(aux = head; aux != NULL; aux = aux->next){
    printf("ID: %d\n", aux->id);
    printf("Nome: %s", aux->name);
    printf("Renda: R$ %.2f\n", aux->income);
    printf("Aniversário: %d/%d/%d\n\n", aux->dbirth.dia, aux->dbirth.mes, aux->dbirth.ano);
  }


  return 0;
}
