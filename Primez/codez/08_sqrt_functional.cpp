#include "utils.cpp"

void primitive_finder(bool *res, int n, int thr){
	int sq=floor(sqrt(n)), vv;
	vv=(sq-2)/thr;
	omp_set_num_threads(thr);
#pragma omp parallel
	{
		int wisdom=omp_get_thread_num(), j, i;
		int v1=2+vv*wisdom, v2=2+vv*(wisdom+1)-1;
		if (wisdom==thr-1) v2=sq;

		for (i=2;i<=n;i++){
			for (j=v1;j*j<=i && j<=v2;j++){
				if (i%j==0) {
					res[i]=1;
					break;
				}
			}
		}
	}
}



int main(int argc, char *argv[]){
	base(argc, argv, &primitive_finder, "T02_primitive_finder.txt");
return 0;}
