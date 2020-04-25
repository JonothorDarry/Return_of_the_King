#include <stdio.h>
#include <math.h>
#include <omp.h>
#define max(a, b) ((a>b)?(a):(b))
#define min(a, b) ((a>b)?(b):(a))
const int C=1000000001, D=50001;

void writer(bool *p, int l, int r, const char* text){
	int i;
	FILE *k=fopen(text, "w");
	for (i=l;i<=r;i++){
		if (p[i]==0)	fprintf(k, "%d\n", i);
	}
	fclose(k);
	return;
}

void printer(bool *p, int l, int r){
	int s=0, i, res=0;
	for (i=l;i<=r;i++){
		s=0;
		for (;i<=r;i++){
			if (p[i]==0) s++, printf ("%d ", i);
			if (s==10) break;
		}
		res+=s;
		printf ("\n");
	}
	printf("Na zadanym przedziale <%d;%d> znalezionon %d liczb pierwszych\n", l, r, res);
}

bool p[C];
void base(int argc, char *argv[], void fun(bool *p, int a, int thr), const char *text){
	int l=2, r=C, thr=8, printo=0;
	if (argc>2) l=atoi(argv[1]), r=atoi(argv[2]);
	if (argc>3) thr=atoi(argv[3]);	
	if (argc>4) printo=atoi(argv[4]);
	
	double t1, t2;
	//linear_sieve(p, r);
	
	t1=omp_get_wtime();
	fun(p, r, thr);
	t2=omp_get_wtime();
	printf ("%.6lf\n", t2-t1);
	if (printo==1) printer(p, l, r);
	
	//writer(p, l, r, text);
}

