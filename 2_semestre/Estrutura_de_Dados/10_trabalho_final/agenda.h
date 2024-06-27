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




void iniciarArvore(Tree *tree);
Tarefa *criarTarefa(int id, char *descricao, float tempoLimite);
Node *criarNo(Tarefa *tarefa);
Node *adicionarTarefa(Node *root, Tarefa *Tarefa);
void inOrdem(Node *root);
void exibirTarefa(Node *root);
void destruirArvore(Node *root);