#include <stdio.h>
#include <math.h>
#include <omp.h>
#define max(a, b) ((a>b)?(a):(b))
const int C=1500000001, D=100001;

void writer(int *p, int l, int r, const char* text){
	int i;
	FILE *k=fopen(text, "w");
	for (i=l;i<=r;i++){
		if (p[i]==0)	fprintf(k, "%d\n", i);
	}
	fclose(k);
	return;
}
