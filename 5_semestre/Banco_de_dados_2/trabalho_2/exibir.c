#include "exibir.h"

void exibir_ajuda(char *nome)
{
  printf("\n[uso] %s -f TABELA_FÍSICA -l TABELA_LÓGICA -m METADADOS_ATT [-v]\n\n\
          -h\t\t\t exibe essa tela e sai.\n\
          -f TABELA_FÍSICA\t seta o nome da tabela físcia (table.dic).\n\
          -l TABELA_LÓGICA\t seta o nome da tabela lógica (owner).\n\
          -m METADADOS_ATT\t seta o arquivo de metadados dos atributos (att.dic).\n\
          -v\t\t\t exibir todas as mensagens (modo verboso).\n",
         nome);

  exit(0);
}

void tratando_parametros(int argc, char *argv[], char **tabela_fisica, char **tabela_logica, char **metadados_atributos, int *debug)
{
  int opt;
  extern char *optarg;
  while ((opt = getopt(argc, argv, "f:l:m:hv")) > 0)
  {
    switch (opt)
    {
    case 'f':
      *tabela_fisica = optarg;
      break;
    case 'l':
      *tabela_logica = optarg;
      break;
    case 'm':
      *metadados_atributos = optarg;
      break;
    case 'h':
      exibir_ajuda(argv[0]);
    case 'v':
      *debug = 1;
      break;
    default:
      exibir_ajuda(argv[0]);
      exit(1);
    }
  }
}

int procurar_tab_logica(FILE *arquivo_fisico, char *tabela_logica, Tab_fisico *fisica, int debug)
{
  Tab_fisico disco;
  while (1)
  {
    if (fread(&disco, sizeof(Tab_fisico), 1, arquivo_fisico) != 1)
      return 0;

    if (debug)
    {
      printf("%d - %s - %s\n", disco.id, disco.nome_logico, disco.nome_fisico);
    }

    int restult = strcmp(disco.nome_logico, tabela_logica);
    if (restult == 0)
    {
      *fisica = disco;
      return 1;
    }
  }

  return 0;
}

void capturando_metadados(FILE *arquivo_metadados, Estrutura_metadados **metadados, int *qtd_att, int debug)
{
  fseek(arquivo_metadados, 0, SEEK_END);
  long tamanho = ftell(arquivo_metadados);
  rewind(arquivo_metadados);
  *qtd_att = tamanho / sizeof(Estrutura_metadados);
  if (debug)
    printf("Quantidade de linhas de atributos: %d\n", *qtd_att);

  *metadados = (Estrutura_metadados *)malloc(*qtd_att * sizeof(Estrutura_metadados));
  if (*metadados == NULL)
  {
    printf("Erro na alocação de memória para guardar metadados\n");
    exit(1);
  }

  for (int i = 0; i < *qtd_att; i++)
  {
    if (fread(&(*metadados)[i], sizeof(Estrutura_metadados), 1, arquivo_metadados) != 1)
      break;

    if (debug)
      printf("%d - %s - %c - %d - %d\n", (*metadados)[i].id, (*metadados)[i].atributo, (*metadados)[i].tipo, (*metadados)[i].obrigatorio, (*metadados)[i].tamanho);
  }
}

void exibindo_dados(FILE *dados_fisico, Estrutura_metadados *metadados, int qtd_att)
{
  for (int i = 0; i < qtd_att; i++)
  {
    printf("%-*s ", metadados[i].tamanho, metadados[i].atributo);
  }

  printf("\n\n");

  while (1)
  {
    int fim = 0;

    for (int i = 0; i < qtd_att; i++)
    {
      void *atributo = malloc(metadados[i].tamanho);
      if (atributo == NULL)
      {
        printf("Erro ao alocar memória para exibição de dados\n");
        exit(1);
      }

      int lidos = fread(atributo, 1, metadados[i].tamanho, dados_fisico);
      if (lidos < metadados[i].tamanho)
      {
        fim = 1;
        free(atributo);
        break;
      }

      switch (metadados[i].tipo)
      {
      case 'S':
        printf("%-*s ", metadados[i].tamanho, (char *)atributo);
        break;
      case 'I':
        printf("%-*d ", metadados[i].tamanho, *(int *)atributo);
        break;
      case 'F':
        printf("%-*.3f ", metadados[i].tamanho, *(float *)atributo);
        break;
      default:
        printf("?");
        break;
      }

      free(atributo);
    }

    if (fim > 0)
      break;

    printf("\n");
  }
}