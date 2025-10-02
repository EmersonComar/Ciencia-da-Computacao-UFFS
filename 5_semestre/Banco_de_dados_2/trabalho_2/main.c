#include "exibir.h"

int main(int argc, char *argv[])
{
  char *tabela_logica = NULL;
  char *tabela_fisica = NULL;
  char *metadados_atributos = NULL;
  Tab_fisico fisica;
  Estrutura_metadados *metadados;
  int qtd_att = 0;
  int debug = 0;

  tratando_parametros(argc, argv, &tabela_fisica, &tabela_logica, &metadados_atributos, &debug);
  if (tabela_fisica == NULL || tabela_logica == NULL || metadados_atributos == NULL)
  {
    exibir_ajuda(argv[0]);
  }

  FILE *arquivo_fisico = fopen(tabela_fisica, "rb");
  if (arquivo_fisico == NULL)
  {
    printf("Erro ao abrir arquivo %s\n", tabela_fisica);
    return 1;
  }

  if (debug)
  {
    printf("Arquivo %s encontrado\n", tabela_fisica);
    printf("Procurando tabela lógica %s..\n", tabela_logica);
  }

  if (!procurar_tab_logica(arquivo_fisico, tabela_logica, &fisica, debug))
  {
    printf("Tabela lógica %s não encontrada em %s\n", tabela_logica, tabela_fisica);
    fclose(arquivo_fisico);
    return 1;
  }

  if (debug)
  {
    printf("Tabela lógica %s encontrada com sucesso\n", tabela_logica);
    printf("Abrindo metadados dos atributos..\n");
  }

  FILE *arquivo_metadados = fopen(metadados_atributos, "rb");
  if (arquivo_metadados == NULL)
  {
    printf("Erro ao abrir arquivo %s\n", metadados_atributos);
    fclose(arquivo_fisico);
    return 1;
  }

  capturando_metadados(arquivo_metadados, &metadados, &qtd_att, debug);

  if (debug)
  {
    printf("Metadados lidos\n");
    printf("Abrindo arquivo de dados físico %s ..\n", fisica.nome_fisico);
  }

  FILE *dados_fisicos = fopen(fisica.nome_fisico, "rb");
  if (dados_fisicos == NULL)
  {
    printf("Erro ao abrir arquivo físico %s\n", fisica.nome_fisico);
    fclose(arquivo_fisico);
    fclose(arquivo_metadados);
    free(metadados);
    return 1;
  }

  if (debug)
  {
    printf("Arquivo %s encontrado\n", fisica.nome_fisico);
    printf("Imprimindo dados..\n\n");
  }

  exibindo_dados(dados_fisicos, metadados, qtd_att);

  fclose(arquivo_fisico);
  fclose(arquivo_metadados);
  fclose(dados_fisicos);
  free(metadados);
  return 0;
}