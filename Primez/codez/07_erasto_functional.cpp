#include "utils.cpp"

void func_par_erasto(int *res, int n){	
	int proc, sq=0;
	res[0]=res[1]=0;
	sq=floor(sqrt(n));
	//omp_set_num_threads(4);
	
	if (n>4) func_par_erasto(res, sq);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}
	proc=omp_get_max_threads();

#pragma omp parallel
	{
		int left=(n/proc)*omp_get_thread_num(), i, j, based_left;
		int right=left+n/proc-1;
		if (omp_get_thread_num()==proc-1) right=n;
		if (left<=sq) left=sq+1;

		for (i=0;i<=sq;i++){
			if (res[i]==0){
				based_left=left-left%i+((left%i==0)?0:i);
				for (j=based_left;j<=right;j+=i){
					res[j]=1;
				}
			}
		}
	}
}


int p[C];
int main(){	
	int l, r, i;
	double t1, t2;
	scanf ("%d %d", &l, &r);
	//linear_sieve(p, r);
	
	t1=omp_get_wtime();
	func_par_erasto(p, r);
	t2=omp_get_wtime();
	printf ("%.6lf\n", t2-t1);
	
	writer(p, l, r, "functional_erasto.txt");

return 0;}
