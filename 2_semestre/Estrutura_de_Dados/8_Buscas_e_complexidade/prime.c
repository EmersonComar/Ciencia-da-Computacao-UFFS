#include <stdio.h>
#include <math.h>
#include <time.h>

//87.178.291.199
//1.073.676.287
//2971215073
//17180131327
int isPrime1 (long int n) // O(n)
{
   long int i;
   for (i=2;i<n;i++)
      if ((n%i)==0)
      {
		 printf("*****%ld\n",i);
         return 0;
      }
   return 1;
}

int isPrime2 (long int n) // O(n/2)
{
   int long i;
   for (i=2;i<(n/2);i++)
      if ((n%i)==0)
      {
		 printf("*****%ld\n",i);
         return 0;
      }
   return 1;
}

int isPrime3 (long int n) // O(raiz de n)
{
   long int i;
   for (i=2;i<=sqrt(n);i++)
      if ((n%i)==0)
      {
		 printf("*****%ld\n",i);
         return 0;
      }
   return 1;
}

int main()
{
	clock_t begin, end;
	double time_spent;
	long int n[3]={1073676287,1073676289,17180131327}; //2971215073}; //68718952447};
    int i;
    for (i=0;i<3;i++)
    {
		// O(n)
		printf("===> %ld\n",n[i]);
		begin= clock();
		if (isPrime1(n[i]))
		   printf("   Primo!\n");
		else
		   printf("   Não Primo!\n");
	    end=clock();
	    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	    printf(" Prime O(n): %.4lf s\n",time_spent);
		// O(n/2)
		begin= clock();
		if (isPrime2(n[i]))
		   printf("   Primo!\n");
		else
		   printf("   Não Primo!\n");
	    end=clock();
	    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	    printf(" Prime O(n/2): %.4lf s\n",time_spent);
		// O(sqrt(n))
		begin= clock();
		if (isPrime3(n[i]))
		   printf("   Primo!\n");
		else
		   printf("   Não Primo!\n");
	    end=clock();
	    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	    printf(" Prime O(sqrt(n)): %.4lf s\n",time_spent);
    }
    return 0;
}
