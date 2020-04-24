#include "utils.cpp"

int sqlist[D], squarez[20][D], ij[20];
void better_par_erasto_sieve(int *res, int n){
	int i, sq=0;
	res[0]=res[1]=0;
	sq=floor(sqrt(n));
	//omp_set_num_threads(4);
	
	if (n>4) better_par_erasto_sieve(res, sq);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}

	//Pure sieve
#pragma omp parallel for schedule(dynamic)
	for (i=0;i<sq;i++){
		if (res[i]==1) continue;
		double t1=omp_get_wtime(), t2;
		int falka=omp_get_thread_num(), cloock=0;
		printf ("%d %d\n", n, falka);

		int j=0;
		for (j=i*i; j<=n; j+=i) res[j]=1, cloock++;
		t2=omp_get_wtime();
		printf ("%d %d %d %.6lf %d\n", n, omp_get_thread_num(), ij[i], t2-t1, cloock);
	}
}


int p[C];
int main(){
	int l, r, i;
	double t1, t2;
	scanf ("%d %d", &l, &r);
	//linear_sieve(p, r);
	
	t1=omp_get_wtime();
	better_par_erasto_sieve(p, r);
	t2=omp_get_wtime();
	printf ("%.6lf\n", t2-t1);
	
	writer(p, l, r, "better_par_erasto_sieve.txt");
	
return 0;}
