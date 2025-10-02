#ifndef EXIBE_H
#define EXIBE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tab_fisica
{
  int id;
  char nome_logico[20];
  char nome_fisico[20];
};
typedef struct tab_fisica Tab_fisico;

struct estrutura_metadados
{
  int id;
  char atributo[20];
  char tipo;
  char obrigatorio;
  int tamanho;
};
typedef struct estrutura_metadados Estrutura_metadados;

void exibir_ajuda(char *nome);
void tratando_parametros(int argc, char *argv[], char **tabela_fisica, char **tabela_logica, char **metadados_atributos,
                         int *debug);
int procurar_tab_logica(FILE *arquivo_fisico, char *tabela_logica, Tab_fisico *fisica, int debug);
void capturando_metadados(FILE *arquivo_metadados, Estrutura_metadados **metadados, int *qtd_att, int debug);
void exibindo_dados(FILE *dados_fisico, Estrutura_metadados *metadados, int qtd_att);

#endif