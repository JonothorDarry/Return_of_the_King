#include <stdio.h>
#include <time.h>
#include <omp.h>

const long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])
{
	clock_t start, stop;
	double pi, sum=0.0, s2=0.0, x;
	step = 1./(double)num_steps;
	start = clock();
	
	int i=0;
#pragma omp parallel for private(s2, x) reduction(+:sum)
	for (i=0; i<num_steps; i++){
		x = (i + .5)*step;
		sum=sum+ 4.0/(1.+ x*x);
	}
	
	
	//pi= sum/numb_of_steps
	pi = sum*step;
	stop = clock();
	printf ("%lu %lu %lu\n", start, stop, stop-start);

	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	printf("Czas przetwarzania wynosi %f sekund\n",((double)(stop - start)/1000000.0));
	return 0;
}
