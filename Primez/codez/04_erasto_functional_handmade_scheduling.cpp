#include "utils.cpp"

int squarez[20][D], ij[20];
void erasto_func_handschedule(bool *res, int a, int n, int thr){
	int proc, i, j, jj, sq=0;
	double summa=0, part;
	sq=floor(sqrt(n));
	
	if (n>4) erasto_func_handschedule(res, 2, sq, thr);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}

	//Sumaric amount of work for each process, so that they'll be approximately equal
	proc=omp_get_max_threads();
	for (i=0;i<=sq;i++){
		if (res[i]==0) summa+=1.0/i;
	}
	part=summa/proc;

	//Primes used by each process
	int beg=0, end=sq;
	double partsum=0;
	for (i=0;i<proc;i++){
		ij[i]=0;
		partsum=0;
		for (j=beg;j<=end;j++){
			if (res[j]==0) {
				squarez[i][ij[i]]=j, partsum+=1.0/j, ij[i]++;
				break;
			}
		}
		beg=j+1;
		if (partsum<part){
			for (j=end;j>=beg;j--){
				if (res[j]==0) {
					squarez[i][ij[i]]=j, partsum+=1.0/j, ij[i]++;
				}
				if (partsum>=part) break;
			}
			end=j-1;
		}
	}
	
	//Pure sieve
#pragma omp parallel for
	for (jj=0;jj<proc;jj++){
		//printf ("%d %d %d\n", n, falka, jj);
		int i=0, j=0, ite, prv=ij[jj], sv=sq+1;

		for (ite=0;ite<prv;ite++){
			i=squarez[jj][ite];
			sv=sq+1;
			j=sv-sv%i+((sv%i==0)?0:i);
			j=max(modal(sv, i), modal(a, i));
			for (j=max(i*i, j); j<=n; j+=i) res[j]=1;
		}
		//printf ("%d %d %d %d %.6lf %d\n", n, omp_get_thread_num(), jj, ij[jj], t2-t1, cloock);
	}
}


int main(int argc, char *argv[]){
	base(argc, argv, &erasto_func_handschedule, "T03_better_par_erasto_sieve.txt");
return 0;}
