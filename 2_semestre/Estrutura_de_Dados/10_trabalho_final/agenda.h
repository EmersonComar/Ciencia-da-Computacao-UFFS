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

void iniciarArvore(Tree *tree);
Tarefa *criarTarefa(int id);
Node *criarNo(Tarefa *tarefa);

Node *adicionarTarefa(Node *root, Tarefa *Tarefa);