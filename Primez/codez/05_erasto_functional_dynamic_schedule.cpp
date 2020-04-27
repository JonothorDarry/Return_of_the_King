#include "utils.cpp"

void erasto_fun_dynschedule(bool *res, int a, int n, int thr){
	int i, sq=0;
	res[0]=res[1]=0;
	sq=floor(sqrt(n));
	
	if (n>4) erasto_fun_dynschedule(res, 2, sq, thr);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}

	omp_set_num_threads(thr);
	//Pure sieve
#pragma omp parallel for schedule(dynamic)
	for (i=0;i<=sq;i++){
		if (res[i]==1) continue;
		int sv=sq+1;
		int j=max(modal(sv, i), modal(a, i));
		for (j=max(i*i, j); j<=n; j+=i) res[j]=1;
	}
}


int main(int argc, char *argv[]){	
	base(argc, argv, &erasto_fun_dynschedule, "T04_erasto_dynamic_schedule.txt");
return 0;}
