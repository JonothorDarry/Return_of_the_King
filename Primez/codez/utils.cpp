#include <stdio.h>
#include <math.h>
#include <omp.h>
#define max(a, b) ((a>b)?(a):(b))
const int C=1500000001, D=50001;

void writer(int *p, int l, int r, const char* text){
	int i;
	FILE *k=fopen(text, "w");
	for (i=l;i<=r;i++){
		if (p[i]==0)	fprintf(k, "%d\n", i);
	}
	fclose(k);
	return;
}

int p[C];
void base(int argc, char *argv[], void fun(int *p, int a), const char *text){
	int l, r;
	double t1, t2;
	scanf ("%d %d", &l, &r);
	//linear_sieve(p, r);
	
	t1=omp_get_wtime();
	fun(p, r);
	t2=omp_get_wtime();
	printf ("%.6lf\n", t2-t1);
	
	writer(p, l, r, text);
}

