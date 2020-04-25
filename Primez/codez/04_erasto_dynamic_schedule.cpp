#include "utils.cpp"

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
		int falka=omp_get_thread_num();

		int j=0;
		for (j=i*i; j<=n; j+=i) res[j]=1;
		t2=omp_get_wtime();
	}
}


int main(int argc, char *argv[]){	
	base(argc, argv, &better_par_erasto_sieve, "T04_erasto_dynamic_schedule.txt");
return 0;}
