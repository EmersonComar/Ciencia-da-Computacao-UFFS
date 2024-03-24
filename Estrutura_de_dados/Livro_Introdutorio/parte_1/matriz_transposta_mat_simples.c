// Essa função irá retornar o endereço de memória 
// do primeiro elemento da matriz transposta.
// 
// Como o espaço de memória para as matrizes são reservadas
// de forma linear, é necessário adotar algumas estratégias
// para declarar dinamicamente memória para matrizes
// multidimencionais.
//
// Neste exemplo, a estratégia que será criada será tratar
// a matriz como se fosse um vetor. Considerando mat[i][j],
// para acessar uma determinada posição podemos utilizar:
// mat[k], onde k = i*n + j, considerando n o número de
// colunas.

float *transposta (int m, int n, float *mat){
	int i, j;
	float *trp;

	trp = (float *) malloc(n*m*sizeof(float));

	for(i=0; i<m. i++)
		for(j=0; j<n; j++)
			trp[j*m*i] = mat[i*n+j];

	return trp;

}
