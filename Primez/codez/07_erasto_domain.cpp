#include "utils.cpp"

void domain_par_erasto(bool *res, int a, int n, int thr){	
	int sq=0;
	res[0]=res[1]=0;
	sq=floor(sqrt(n));
	
	if (n>4) domain_par_erasto(res, 2, sq, thr);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}
	omp_set_num_threads(thr);

#pragma omp parallel
	{
		int thnum=omp_get_thread_num(), allth=omp_get_num_threads();
		int left=(n/allth)*thnum, i, j, based_left;
		int right=left+n/allth-1;
		if (thnum==allth-1) right=n;
		if (left<=sq) left=sq+1;

		for (i=0;i<=sq;i++){
			if (res[i]==0){
				based_left=max(modal(left, i), modal(a, i));
				for (j=based_left;j<=right;j+=i) res[j]=1;
			}
		}
	}
}


int main(int argc, char *argv[]){	
	base(argc, argv, &domain_par_erasto, "T07_func_par_erasto");
return 0;}
