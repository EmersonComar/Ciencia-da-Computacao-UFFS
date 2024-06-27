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

void exibirTarefa(Node *root){
    printf("ID: %d\n", root->tarefa->id);
    printf("Descrição: %s\n", root->tarefa->descricao);
    printf("Tempo limite: %.2fh\n", root->tarefa->tempoLimite);
    printf("Situação: %s\n\n", root->tarefa->situacao);
}

void inOrdem(Node *root){
    if(root == NULL) return;

    inOrdem(root->left);
    exibirTarefa(root);
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