#include <stdio.h>
#include <time.h>
#include <omp.h>

volatile double s2[200];
const long long num_steps = 1000000000, C=200;
double step;

int main(int argc, char* argv[])
{
	clock_t start, stop;
	double pi, sum=0.0, x, real_start, real_stop;
	step = 1./(double)num_steps;
	start = clock();
	real_start=omp_get_wtime();
	
	int i=0, ij=0, num;
	omp_set_num_threads(2);
#pragma omp parallel private(num)
	{
	num=omp_get_thread_num();
	printf ("%d\n", omp_get_num_threads());
	while(ij<C){
#pragma omp barrier
		{}
#pragma omp for private (x)
		for (i=0; i<num_steps; i++){
			x = (i + .5)*step;
			s2[ij+num]=s2[ij+num]+ 4.0/(1.+ x*x);
		}

#pragma omp critical
		{printf ("%d\n", num); sum=sum+s2[ij+num]; s2[ij+num]=0;}
#pragma omp barrier
		{}
#pragma omp single
		{	
			printf ("###########     Iteracja nr %d     ##########\n", ij);
			pi = sum*step;
			stop = clock();
			real_stop=omp_get_wtime();

			printf("Wartosc liczby PI wynosi %15.12f\n",pi);
			printf("Suma czasu przetwarzania wszystkich wątków wynosi %f sekund\n",((double)(stop - start)/1000000.0));
			printf("Czas przetwarzania wynosi %lf sekund\n\n",((double)(real_stop - real_start)));
			real_start=omp_get_wtime();
			start = clock();
			sum=0;
			ij+=1;
		}
	}
	}
	
	//pi= sum/numb_of_steps
	return 0;
}
