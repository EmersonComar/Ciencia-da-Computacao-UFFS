#include <stdio.h>
#include <stdlib.h>

#define N 10

struct pilha{
    int n;
    int vet[N];
};
typedef struct pilha Pilha;

Pilha *pilha_cria();
void pilha_push(Pilha *p, int v);
int pilha_pop(Pilha *p);
int pilha_vazia(Pilha *p);
void pilha_libera(Pilha *p);
void pilha_exibir(Pilha *p);

int menu();

int main(void){
    Pilha *p = pilha_cria();
    int m, valor;

    for(;;){
        
        m = menu();

        switch(m){
            case 1:
                printf("\nDigite um valor inteiro para inserir na pilha: ");
                scanf("%d", &valor);
                pilha_push(p, valor);
                printf("Adicionado %d na pilha\n", valor);
                break;
            case 2:
                if(!pilha_vazia(p)){
                    printf("\nValor retirado da pilha: %d\n", pilha_pop(p));
                }else{
                    printf("\nA pilha está vazia\n");
                }
                break;
            case 3:
                if(pilha_vazia(p)){
                    printf("\nA pilha está vazia\n");
                }else{
                    printf("\nA pilha não está vazia\n");
                }
                break;
            case 4:
                pilha_libera(p);
                printf("\nPilha destruida\n");
                return 0;
            case 5:
                pilha_exibir(p);
                break;
            case 6:
                printf("\nSaindo..\n");
                pilha_libera(p);
                return 0;
            default:
                printf("\nOpção inválida\n");
                break;
        }
    }


    return 0;
}

int menu(){
    int i;
    printf("\n1 - Adicionar valor na pilha\n");
    printf("2 - Retirar topo da pilha\n");
    printf("3 - Validar se a pilha está ou não vazia\n");
    printf("4 - Limpar pilha\n");
    printf("5 - Exibir pilha\n");
    printf("6 - Sair\n");
    printf("-> ");
    scanf("%d", &i);
    return i;
}

Pilha *pilha_cria(){
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    if(pilha == NULL){
        printf("Não possui espaço disponível para alocar\n");
        exit(1);
    }

    return pilha;
}

void pilha_push(Pilha *p, int v){
    if(p->n == N){
        printf("A pilha estourou!!\n");
        pilha_libera(p);
        exit(1);
    }

    p->vet[p->n] = v;
    p->n++;
}

int pilha_pop(Pilha *p){
    int valor = p->vet[p->n - 1];
    p->n--;
    return valor;

}

int pilha_vazia(Pilha *p){
    return (p->n == 0);
}

void pilha_libera(Pilha *p){
    free(p);
}

void pilha_exibir(Pilha *p){
    for(int i=0; i<p->n; i++){
        printf("====");
    }
    printf("\n");

    printf("|");

    for(int i=0; i<p->n; i++){
        printf("%d   ", p->vet[i]);
    }
    printf("\n");

    for(int i=0; i<p->n; i++){
        printf("====");
    }
    printf("\n");

}