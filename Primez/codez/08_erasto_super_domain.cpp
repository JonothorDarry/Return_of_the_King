#include "utils.cpp"

int neoprimez[D], ineo=0, dp[10][D];
void func_par_erasto(bool *res, int n, int thr){
	int sq=0, outer=32000, ite=0;
	res[0]=res[1]=0;
	sq=floor(sqrt(n));
	
	if (n>4) func_par_erasto(res, sq, thr);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}
	omp_set_num_threads(thr);

	ineo=0;
	for (int vi=0;vi<=sq;vi++){
		if (res[vi]==0) {
			for (ite=0;ite<10;ite++) dp[ite][vi]=0;
			neoprimez[ineo]=vi, ineo++;
		}
	}

#pragma omp parallel
	{
		int thnum=omp_get_thread_num(), allth=omp_get_num_threads();
		int left=(n/allth)*thnum, i, ji, j, finished=0, curfun=left;
		int right=left+n/allth-1;
		if (thnum==allth-1) right=n;
		if (left<=sq) left=sq+1;
		
		while (finished<ineo){
			curfun=curfun+outer;
			for (ji=0;ji<ineo;ji++){
				i=neoprimez[ji];
				if (dp[thnum][i]==0) dp[thnum][i]=left-left%i+((left%i==0)?0:i);
				for (j=dp[thnum][i];j<=right;j+=i){
					p[j]=1;	
					if (j>=curfun) break;
				}
				if (j>right) finished++;
				dp[thnum][i]=j;
			}
		}
	}
}


int main(int argc, char *argv[]){	
	base(argc, argv, &func_par_erasto, "T07_func_par_erasto");
return 0;}
