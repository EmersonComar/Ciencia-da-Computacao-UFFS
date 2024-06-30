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


void iniciarLista(ListaOrdenada *lista);
void iniciarArvore(Tree *tree);
Tarefa *criarTarefa(int id, char *descricao, float tempoLimite);
Node *criarNo(Tarefa *tarefa);
Node *adicionarTarefa(Node *root, Tarefa *Tarefa);
void inOrdem(Node *root);
void exibirTarefa(Tarefa *tarefa);
void destruirArvore(Node *root);
int consultarID(Node *root, int valorID);
Node *retornarNodeTarefa(Node *root, int valorID);
int removerTarefa(Tree *sentinel, int valorID);
Node *removeAtual(Node *atual);
ListaOrdenada *criarLista(Tarefa *tarefa);
void ordenarTarefasAtivasTempo(Node *root, ListaOrdenada *lista);
void exibirLista(ListaOrdenada *lista);
void destruirLista(ListaOrdenada *lista);