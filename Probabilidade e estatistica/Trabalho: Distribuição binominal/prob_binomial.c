#include <stdio.h>
#include <math.h>

long double fatorial_aprox(int valor);
long double combinacao(int n, int x);
long double prob_bin_individual(int n, int x, long double p, long double q);
long double prob_bin_acumulada(int n, int x, long double p, long double q);

int main(void){
    int n, x;
    long double p, q;

    printf("Fórmula Binomial: P(x) = Cn,x . (p)^x . (q)^(n - x)\n");
    
    printf("Digite o valor de n: ");
    scanf("%d", &n);

    printf("Digite o valor de x: ");
    scanf("%d", &x);

    printf("Digite o valor absoluto de p: ");
    scanf("%Lf", &p);

    q = 1.0 - p;

    printf("\n");
    printf("\t[+] Probabilidade Binomial Individual: %.4Lf\n", prob_bin_individual(n, x, p, q));
    printf("\t[+] Probabilidade Binomial Acumulada: %.4Lf\n", prob_bin_acumulada(n, x, p, q));

    return 0;
}

long double fatorial_aprox(int valor){
    if(valor == 0 || valor == 1)
        return 1;
    return sqrt(2 * M_PI * valor) * pow((valor / M_E), valor);
}

long double combinacao(int n, int x){
    if(x > n / 2)
        x = n - x;
    
    long double resultado = 1;
    for(int i = 0; i < x; i++){
        resultado *= (n - i);
        resultado /= (i + 1);
    }

    return resultado;
}

long double prob_bin_individual(int n, int x, long double p, long double q){
    return combinacao(n, x) * pow(p, x) * pow(q, (n - x));
}

long double prob_bin_acumulada(int n, int x, long double p, long double q){
	long double resultado = 0.0;
	for(int i=0; i<=x; i++)
		resultado += prob_bin_individual(n, i, p, q);

	return resultado;
}
