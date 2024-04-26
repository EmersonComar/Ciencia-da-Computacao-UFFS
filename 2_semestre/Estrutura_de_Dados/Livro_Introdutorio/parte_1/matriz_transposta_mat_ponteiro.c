// Nesta estratégia para alocar dinamicamente memória para 
// uma determinada matriz, será criado um vetor de ponteiros onde
// cada ponteiro irá representar uma linha da matriz.
//
// A vantagem de utilizar esta estratégia é utilizar a matriz
// de forma natural, como se fosse declarada estaticamente.

float **transposta(int m, int n, float **mat){
	int i, j;
	float **trp;

	trp = (float **) malloc(n*sizeof(float*));

	for(i = 0; i<n; i++)
		trp[i] = (float *) malloc(m*sizeof(float));

	for(i=0; i<m; i++)
		for(j=0; j<n; j++)
			trp[j][i] = mat[i][j];

	return trp;
}
