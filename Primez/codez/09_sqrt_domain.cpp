#include "utils.cpp"

void primitive_finder(bool *res, int n, int thr){
	int i;
	omp_set_num_threads(thr);
#pragma omp parallel for
	for (i=2;i<=n;i++){
		for (int j=2;j*j<=i;j++){
			if (i%j==0) {
				res[i]=1;
				break;
			}
		}
	}
}



int main(int argc, char *argv[]){
	base(argc, argv, &primitive_finder, "T02_primitive_finder.txt");
return 0;}
