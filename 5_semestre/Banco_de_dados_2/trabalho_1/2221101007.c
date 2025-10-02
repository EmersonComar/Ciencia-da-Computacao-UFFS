#include <stdio.h>
#include <stdlib.h>

#define MAXATT 10

struct cabecalho
{
  char atributo[16];
  char tipo;
  int tamanho;
};
typedef struct cabecalho Cabecalho;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Modo de uso: %s <arquivo>\n", argv[0]);
    return 1;
  }

  char *dir_arquivo = argv[1];

  FILE *arquivo = fopen(dir_arquivo, "rb");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir arquivo %s\n", dir_arquivo);
    return 2;
  }


  Cabecalho cabecalho[MAXATT];
  int qtd_att = 0;

  while (1)
  {
    if (qtd_att >= MAXATT)
    {
      printf("Quantidade máxima de parâmetros excedida\n");
      return 3;
    }

    int lidos = fread(&cabecalho[qtd_att].atributo, 1, 15, arquivo);
    if (lidos < 15)
    {
      printf("Esquema de dados do cabeçalho está diferente do padrão.");
      return 4;
    }

    if (cabecalho[qtd_att].atributo[0] == '#')
    {
      fseek(arquivo, -14, SEEK_CUR);
      break;
    }

    fread(&cabecalho[qtd_att].tipo, 1, 1, arquivo);
    fread(&cabecalho[qtd_att].tamanho, sizeof(int), 1, arquivo);
    qtd_att++;
  }

  // imprime nomes das colunas
  for (int i = 0; i < qtd_att; i++)
  {
    printf("%-*s ", cabecalho[i].tamanho, cabecalho[i].atributo);
  }
  printf("\n");

  // Lógica para imprimir os dados
  while (1)
  {
    int fim = 0;

    for (int i = 0; i < qtd_att; i++)
    {
      void *atributo = malloc(cabecalho[i].tamanho);
      if (atributo == NULL)
      {
        printf("Erro ao alocar memória para exibir atributo\n");
        return 5;
      }

      int lidos = fread(atributo, 1, cabecalho[i].tamanho, arquivo);
      if (lidos < cabecalho[i].tamanho)
      {
        free(atributo);
        fim = 1;
        break;
      }

      // exibição alinhada
      switch (cabecalho[i].tipo)
      {
      case 'S':
        printf("%-*s ", cabecalho[i].tamanho, (char *)atributo);
        break;
      case 'I':
        printf("%-*d ", cabecalho[i].tamanho, *(int *)atributo);
        break;
      case 'F':
        printf("%-*.3f ", cabecalho[i].tamanho, *(float *)atributo);
        break;
      case 'C':
        printf("%-*c ", cabecalho[i].tamanho, *(char *)atributo);
        break;
      default:
        printf("%-*s ", cabecalho[i].tamanho, "?");
      }

      free(atributo);
    }

    if (fim)
      break;

    printf("\n");
  }

  fclose(arquivo);
  return 0;
}
