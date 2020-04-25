#include "utils.cpp"

int squarez[20][D], ij[20];
void better_par_erasto_sieve(bool *res, int n, int thr){
	int proc, i, j, jj, sq=0;
	double summa=0, part;
	sq=floor(sqrt(n));
	//omp_set_num_threads(4);
	
	if (n>4) better_par_erasto_sieve(res, sq, thr);
	else{
		if (n>=4) res[0]=res[1]=res[4]=1;
		else res[0]=res[1]=1;
		return;
	}
	omp_set_num_threads(thr);

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

		//printf ("At %d: Process %d executes: %.6lf, as a part: %.6lf\n", n, i, partsum, partsum/summa);
		//for (j=0;j<ij[i];j++) printf ("%d\n", squarez[i][j]);
	}
	
	//Pure sieve
#pragma omp parallel for
	for (jj=0;jj<proc;jj++){
		double t1=omp_get_wtime(), t2;
		int falka=omp_get_thread_num();
		//printf ("%d %d %d\n", n, falka, jj);

		int i=0, j=0, ite, prv=ij[jj];

		for (ite=0;ite<prv;ite++){
			i=squarez[jj][ite];
			for (j=i*i; j<=n; j+=i) res[j]=1;
		}
		t2=omp_get_wtime();
		//printf ("%d %d %d %d %.6lf %d\n", n, omp_get_thread_num(), jj, ij[jj], t2-t1, cloock);
	}
}


int main(int argc, char *argv[]){
	base(argc, argv, &better_par_erasto_sieve, "T03_better_par_erasto_sieve.txt");
return 0;}
