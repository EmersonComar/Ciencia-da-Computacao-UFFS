// finalizar depois

#include <stdio.h>
#include <stdlib.h>

#define QTD 2

struct aluno{
  int matricula;
  char nome[16];
  float notas[3];
};
typedef struct aluno Aluno;

Aluno *criarAlunos(int qtd);
void preencherAlunos(Aluno *alunos, int qtd);
void maiorNotaPrimeiraProva(Aluno *alunos, int qtd);
void maiorMedia(Aluno *alunos, int qtd);
float calculaMedia(Aluno aluno);
void exibirAluno(Aluno aluno);
void liberarAlunos(Aluno *alunos);

int main(void){
  Aluno *alunos;
  
  alunos = criarAlunos(QTD);
  preencherAlunos(alunos, QTD);
  maiorNotaPrimeiraProva(alunos, QTD);
  maiorMedia(alunos, QTD);
  liberarAlunos(alunos);
  
  return 0;
}

Aluno *criarAlunos(int qtd){
  Aluno *alunos = (Aluno *) malloc(qtd * sizeof(Aluno));
  if(alunos == NULL){
    printf("Memória Insuficiente!!\n");
    exit(1);
  }
  
  return alunos;
}

void liberarAlunos(Aluno *alunos){
  free(alunos);
}

void preencherAlunos(Aluno *alunos, int qtd){
  for(int i=0; i<qtd; i++){
    printf("Aluno %d\n", i+1);
    printf("Matrícula: ");
    scanf("%d", &alunos[i].matricula);
    
    __fpurge(stdin);
    
    printf("Nome: ");
    fgets(alunos[i].nome, 16, stdin);
    
    for(int j=0; j<3; j++){
      printf("Prova %d: ", j+1);
      scanf("%f", &alunos[i].notas[j]);
    }
    printf("\n");
  }
}

void maiorNotaPrimeiraProva(Aluno *alunos, int qtd){
  float maior = alunos[0].notas[0];
  Aluno alunoMaior = alunos[0];
  
  for(int i=1; i<qtd; i++){
    if(alunos[i].notas[0] > maior)
      maior = alunos[i].notas[0];
      alunoMaior = alunos[i];
  }
  
  printf("A maior nota da primeira prova pertence ao aluno:\n");
  exibirAluno(alunoMaior);
}

void exibirAluno(Aluno aluno){
  printf("Matrícula: %d\n", aluno.matricula);
  printf("Nome: %s", aluno.nome);
  for(int i=0; i<3; i++)
    printf("Nota[%d]: %.2f\n", i+1, aluno.notas[i]);
}

float calculaMedia(Aluno aluno){
  float media = 0.0f;
  for(int i=0; i<3; i++)
    media += aluno.notas[i];
  
  return media/3;
}

void maiorMedia(Aluno *alunos, int qtd){
  float media = calculaMedia(alunos[0]);
  Aluno mediaMaior = alunos[0];
  
  for(int i=1; i<qtd; i++){
    float alunoAtual = calculaMedia(alunos[i]);
    if(alunoAtual > media)
      media = alunoAtual;
      mediaMaior = alunos[i];
  }
  
  printf("A maior média pertencia ao aluno:\n");
  exibirAluno(mediaMaior);
}
