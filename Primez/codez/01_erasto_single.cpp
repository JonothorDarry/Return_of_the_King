#include "utils.cpp"

void erasto_sieve(int *res, int n){
	int i, j;
	res[0]=res[1]=0;

	for (i=2;i*i<=n;i++){
		if (res[i]==0){
			for (j=i*i;j<=n;j+=i) res[j]=1;
		}
	}
}

/*
int primez[C], ite=0;
void linear_sieve(int *res, int n){
	int i, j;
	res[0]=res[1]=0;
	for (i=2;i<=n;i++) res[i]=i;

	for (i=2;i*2<=n;i++){
		if (res[i]==i) primez[ite]=i, ite++;
		for (j=0;j<ite && res[i]>=primez[j] && primez[j]*i<=n; j++)	res[primez[j]*i]=primez[j];	
	}
}*/


int main(int argc, char *argv[]){
	base(argc, argv, &erasto_sieve, "T01_erasto_sieve.txt");
return 0;}
