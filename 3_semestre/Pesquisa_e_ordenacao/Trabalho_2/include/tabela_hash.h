#ifndef TABELA_HASH_H
#define TABELA_HASH_H

struct tlist{
    int valor;
    struct tlist *next;
};

typedef struct tlist Tlist;
typedef struct hash Hash;

Hash *criar_tabela(int tamanho_tabela);
void liberar_tabela(Hash *tabela_hash);

int inserir_hash(Hash *tabela_hash, Tlist lista);
void exibir_hash(Hash *tabela_hash);

#endif