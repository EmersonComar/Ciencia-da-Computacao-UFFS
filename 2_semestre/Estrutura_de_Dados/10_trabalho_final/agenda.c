#include <stdlib.h>
#include <stdio.h>

struct t{
    int id;
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

Tarefa *criarTarefa(int id){
    Tarefa *novo = (Tarefa *) malloc(sizeof(Tarefa));

    novo->id = id;

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
    }else if(tarefa->id < root->tarefa->id){
        root->left = adicionarTarefa(root->left, tarefa);
    }

    return root;
}

void inOrdem(Node *root){
    if(root == NULL) return;

    inOrdem(root->left);
    printf("ID %d\n", root->tarefa->id);
    inOrdem(root->right);
}