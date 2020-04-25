#include "utils.cpp"

void better_par_erasto_sieve(bool *res, int n, int thr){
	int i, sq=0;
	res[0]=res[1]=0;
	sq=floor(sqrt(n));
	
	if (n>4) better_par_erasto_sieve(res, sq, thr);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}
	omp_set_num_threads(thr);

	//Pure sieve
#pragma omp parallel for
	for (i=0;i<=sq;i++){
		if (res[i]==1) continue;
		double t1=omp_get_wtime(), t2;
		int falka=omp_get_thread_num();

		int sv=sq+1;
		int j=sv-sv%i+((sv%i==0)?0:i);
		for (j=min(i*i, j); j<=n; j+=i) res[j]=1;
		t2=omp_get_wtime();
	}
}


int main(int argc, char *argv[]){	
	base(argc, argv, &better_par_erasto_sieve, "T04_erasto_dynamic_schedule.txt");
return 0;}
