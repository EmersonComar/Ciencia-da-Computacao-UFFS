#ifndef TABELA_HASH_H
#define TABELA_HASH_H


typedef struct tlist Tlist;
typedef struct hash Hash;
typedef struct lista Lista;

Hash *criar_tabela(int tamanho_tabela);
void liberar_tabela(Hash *tabela_hash);

int inserir_hash(Hash *tabela_hash, Tlist lista);
void exibir_hash(Hash *tabela_hash);

Tlist *criar_tlist(FILE *arquivo);

#endif