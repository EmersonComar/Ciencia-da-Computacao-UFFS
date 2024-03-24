#include <stdio.h>

int main(void){
	int matricula, qtdAlunos;
	float nota, somaAluno, somaTotal;

	qtdAlunos = somaTotal = 0;
	while (1){
		printf("Matrícula: ");
		scanf("%d", &matricula);
		
		qtdAlunos++;
		if (matricula == 0)
			break;

		somaAluno = 0;
		for(int i = 1; i <= 5; i++){
			printf("Nota %d: ", i);
			scanf("%f", &nota);
			somaAluno += nota;
		}

		printf("Aluno: %d Média: %.1f\n", matricula, (somaAluno/5));
		somaTotal += (somaAluno/5);
	}
	if(qtdAlunos > 1)
		qtdAlunos--;

	printf("Média geral da turma: %.1f\n", somaTotal/qtdAlunos);


	return 0;
}
