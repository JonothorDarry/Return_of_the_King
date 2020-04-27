#include "utils.cpp"

void erasto_sieve(bool *res, int a, int n, int thr){
	int i, j;
	res[0]=res[1]=0;
	if (a!=2) erasto_sieve(res, 2, floor(sqrt(n)), thr);

	for (i=2;i*i<=n;i++){
		if (res[i]==0){
			for (j=i*i;j<=n;j+=i) res[j]=1;
		}
	}
}

int main(int argc, char *argv[]){
	base(argc, argv, &erasto_sieve, "T01_erasto_sieve.txt");
return 0;}
