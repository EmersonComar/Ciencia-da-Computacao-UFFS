#include <stdio.h>


int validaTime(char time);
void alteraPontuacao(char time, int *pA, int *pB, int *pC, int *pD, int pontos);
char validaCampeao(int *pA, int *pB, int *pC, int *pD);

int main(void){
	int gol1, gol2, pA, pB, pC, pD, partidas;
	char time1, time2;

	pA = pB = pC = pD = 0;
	partidas = 1;
	while (1){
		printf("\n=== Partida %d ===\n", partidas);
		printf("Time: ");
		scanf("%c", &time1);
		
		if(validaTime(time1))
			break;

		printf("Gols: ");
		scanf("%d", &gol1);

		__fpurge(stdin);
		printf("---\n");

		printf("Time: ");
		scanf("%c", &time2);

		if(validaTime(time2))
			break;

		printf("Gols: ");
		scanf("%d", &gol2);
		
		__fpurge(stdin);

		if(gol1 > gol2)
			alteraPontuacao(time1, &pA, &pB, &pC, &pD, 3);
		else if (gol1 < gol2)
			alteraPontuacao(time2, &pA, &pB, &pC, &pD, 3);
		else{
			alteraPontuacao(time1, &pA, &pB, &pC, &pD, 1);
			alteraPontuacao(time2, &pA, &pB, &pC, &pD, 1);
		}
		partidas++;
	}

	char campeao = validaCampeao(&pA, &pB, &pC, &pD);

	printf("\n");

	if(campeao == 'E')
		printf("Não houve campeão\n");
	else
		printf("Campeão: %c\n", campeao);

	printf("A: %d ponto(s)\n", pA);
	printf("B: %d ponto(s)\n", pB);
	printf("C: %d ponto(s)\n", pC);
	printf("D: %d ponto(s)\n", pD);


	return 0;
}

int validaTime(char time){
	if(time == 'A' || time == 'B' || time == 'C' || time == 'D')
		return 0;
	return 1;
}

void alteraPontuacao(char time, int *pA, int *pB, int *pC, int *pD, int pontos){
	switch(time){
		case 'A':
			*pA += pontos;
			break;
		case 'B':
			*pB += pontos;
			break;
		case 'C':
			*pC += pontos;
			break;
		case 'D':
			*pD += pontos;
			break;
	}
}

char validaCampeao(int *pA, int *pB, int *pC, int *pD){
	int maior = *pA;
	char time = 'A';
	int iguais = 0;

	if(*pB > maior){
		maior = *pB;
		time = 'B';
	}
	if(*pC > maior){
		maior = *pC;
		time = 'C';
	}
	if(*pD > maior){
		maior = *pD;
		time = 'D';
	}

	if(maior == *pA)
		iguais++;
	if(maior == *pB)
		iguais++;
	if(maior == *pC)
		iguais++;
	if(maior == *pD)
		iguais++;


	if(iguais > 1)
		return 'E';

	return time;
}
