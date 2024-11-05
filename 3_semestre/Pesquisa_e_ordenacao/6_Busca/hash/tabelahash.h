struct aluno {
    int matricula;
    char nome[20];
    float n1,n2;
};
typedef struct hash Hash;

Hash *criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);
int valorString(char *str);


int insereHash_SemColisao(Hash *ha, struct aluno al);
int buscaHash_SemColisao(Hash *ha, int mat, struct aluno* al);



int insereHash_EnderAberto(Hash *ha, struct aluno al);
int buscaHash_EnderAberto(Hash *ha, int mat, struct aluno* al);