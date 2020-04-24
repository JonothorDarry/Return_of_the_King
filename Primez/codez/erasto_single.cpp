#include "utils.cpp"

void erasto_sieve(int *res, int n){
	int i, j;
	res[0]=res[1]=0;

	for (i=2;i*i<=n;i++){
		if (res[i]==0){
			for (j=i*i;j<=n;j+=i) res[j]=1;
		}
	}
}

/*
int primez[C], ite=0;
void linear_sieve(int *res, int n){
	int i, j;
	res[0]=res[1]=0;
	for (i=2;i<=n;i++) res[i]=i;

	for (i=2;i*2<=n;i++){
		if (res[i]==i) primez[ite]=i, ite++;
		for (j=0;j<ite && res[i]>=primez[j] && primez[j]*i<=n; j++)	res[primez[j]*i]=primez[j];	
	}
}*/


int p[C];
int main(){
	int l, r, i;
	double t1, t2;
	scanf ("%d %d", &l, &r);
	//linear_sieve(p, r);
	t1=omp_get_wtime();
	erasto_sieve(p, r);
	t2=omp_get_wtime();
	printf ("%.6lf\n", t2-t1);
	writer(p, l, r, "basic_erasto_sieve.txt");
	
return 0;}
