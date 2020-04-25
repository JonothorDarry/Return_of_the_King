#include "utils.cpp"

void func_par_erasto(bool *res, int n, int thr){	
	int sq=0;
	res[0]=res[1]=0;
	sq=floor(sqrt(n));
	
	if (n>4) func_par_erasto(res, sq, thr);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}
	omp_set_num_threads(thr);

#pragma omp parallel
	{
		int left=(n/thr)*omp_get_thread_num(), i, j, based_left;
		int right=left+n/thr-1;
		if (omp_get_thread_num()==thr-1) right=n;
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


int main(int argc, char *argv[]){	
	base(argc, argv, &func_par_erasto, "T07_func_par_erasto");
return 0;}
