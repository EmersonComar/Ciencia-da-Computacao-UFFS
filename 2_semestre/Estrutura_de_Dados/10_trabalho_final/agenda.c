#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct t{
    int id;
    char descricao[21];
    float tempoLimite;
    char situacao[11];
};
typedef struct t Tarefa;

struct node{
    Tarefa *tarefa;
    struct node *left;
    struct node *right;
};
typedef struct node Node;

struct tree{
    Node *root;
};
typedef struct tree Tree;

struct lo{
    Tarefa *tarefa;
    struct lo *next;
};
typedef struct lo ListaOrdenada;


void iniciarLista(ListaOrdenada *lista){
    lista->next = NULL;
    lista->tarefa = NULL;
}

void iniciarArvore(Tree *tree){
    tree->root = NULL;
}

Tarefa *criarTarefa(int id, char *descricao, float tempoLimite){
    Tarefa *novo = (Tarefa *) malloc(sizeof(Tarefa));

    novo->id = id;
    novo->tempoLimite = tempoLimite;
    strcpy(novo->descricao, descricao);
    strcpy(novo->situacao, "ativo");

    
    return novo;
}

Node *criarNo(Tarefa *tarefa){
    Node *novo = (Node *) malloc(sizeof(Node));

    novo->tarefa = tarefa;
    novo->left = NULL;
    novo->right = NULL;

    return novo;
}

Node *adicionarTarefa(Node *root, Tarefa *tarefa){
    if(root == NULL){
        return criarNo(tarefa);
    }

    if(tarefa->id >= root->tarefa->id){
        root->right = adicionarTarefa(root->right, tarefa);
    }else{
        root->left = adicionarTarefa(root->left, tarefa);
    }

    return root;
}

void exibirTarefa(Tarefa *tarefa){
    printf("ID: %d\n", tarefa->id);
    printf("Descrição: %s\n", tarefa->descricao);
    printf("Tempo limite: %.2fh\n", tarefa->tempoLimite);
    printf("Situação: %s\n\n", tarefa->situacao);
}

void inOrdem(Node *root){
    if(root == NULL) return;

    inOrdem(root->left);
    exibirTarefa(root->tarefa);
    inOrdem(root->right);
}

void destruirArvore(Node *root){
    if(root == NULL) return;

    destruirArvore(root->left);
    destruirArvore(root->right);
    free(root->tarefa);
    free(root);
    root = NULL;
}

int consultarID(Node *root, int valorID){
    if(root == NULL) return 0;

    if(valorID == root->tarefa->id){
        return 1;
    }
    else if(valorID > root->tarefa->id){
        return consultarID(root->right, valorID);
    }else if(valorID < root->tarefa->id){
        return consultarID(root->left, valorID);
    }

    return 0;
}

Node *retornarNodeTarefa(Node *root, int valorID){
    if(root->tarefa->id == valorID) return root;

    else if(root->tarefa->id > valorID){
        return retornarNodeTarefa(root->left, valorID);
    } else if(root->tarefa->id < valorID){
        return retornarNodeTarefa(root->right, valorID);
    }

    return NULL;
}

Node *removeAtual(Node *atual){
    Node *no1, *no2;

    if(atual->left == NULL){
        no2 = atual->right;
        free(atual);
        return no2;
    }

    no1 = atual;
    no2 = atual->left;

    while(no2->right != NULL){
        no1 = no2;
        no2 = no2->right;
    }

    if(no1 != atual){
        no1->right = no2->left;
        no2->left = atual->left;
    }

    no2->right = atual->right;
    free(atual);
    return no2;
}

int removerTarefa(Tree *sentinel, int valorID){
    if(sentinel->root == NULL) return 0;

    Node *anterior = NULL;
    Node *atual = sentinel->root;

    while(atual != NULL){
        if(valorID == atual->tarefa->id){
            if(atual == sentinel->root){
                sentinel->root = removeAtual(atual);
            }else{
                if(anterior->left == atual)
                    anterior->left = removeAtual(atual);
                else
                    anterior->right = removeAtual(atual);
            }

            return 1;
        }

        anterior = atual;
        if(valorID > atual->tarefa->id)
            atual = atual->right;
        else
            atual = atual->left;
    }

    return 0;
}

ListaOrdenada *criarLista(Tarefa *tarefa){
    ListaOrdenada *novo = (ListaOrdenada *)malloc(sizeof(ListaOrdenada));

    novo->tarefa = tarefa;
    novo->next = NULL;

    return novo;
}

void popularLista(ListaOrdenada *lista, ListaOrdenada *novo){
    if(lista->next == NULL){
        lista->next = novo;
        return;
    }

    ListaOrdenada *anterior = NULL;
    ListaOrdenada *aux = lista->next;

    while(aux->next != NULL){
        anterior = aux;
        aux = aux->next;
    }

    if(novo->tarefa->tempoLimite < aux->tarefa->tempoLimite){
        if(anterior != NULL){
            anterior->next = novo;
            novo->next = aux;
        }else{
            lista->next = novo;
            novo->next = aux;
        }
    }else{
        aux->next = novo;
    }

}

void exibirLista(ListaOrdenada *lista){
    for(ListaOrdenada *aux = lista->next; aux != NULL; aux = aux->next){
        exibirTarefa(aux->tarefa);
    }
}


void destruirLista(ListaOrdenada *lista){
    ListaOrdenada *aux = lista->next;

    while(aux != NULL){
        ListaOrdenada *atual = aux;
        aux = aux->next;
        free(atual);
    }
}

void ordenarSituacao(Node *root, ListaOrdenada *lista, char *situacao){
    if(root == NULL) return;

    ordenarSituacao(root->left, lista, situacao);
    ordenarSituacao(root->right, lista, situacao);

    if(strcmp(root->tarefa->situacao, situacao) == 0){
        ListaOrdenada *novo = criarLista(root->tarefa);
        popularLista(lista, novo);
    }
}

void alterarStatus(Tarefa *tarefa){
    if(strcmp(tarefa->situacao, "ativo") == 0)
        strcpy(tarefa->situacao, "concluido");
}