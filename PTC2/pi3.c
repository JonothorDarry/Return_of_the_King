#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

const long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])
{
	printf ("Nazwa programu: %s\n", __FILE__);
	if (argc>0){
		omp_set_num_threads(atoi(argv[1]));
		printf("Zadana liczba wątków: %s\n", argv[1]);
	}

	clock_t start, stop;
	double pi, sum=0.0, real_stop, real_start;
	step = 1./(double)num_steps;
	start = clock();
	real_start=omp_get_wtime();
	
	int i=0;
#pragma omp parallel for
	for (i=0; i<num_steps; i++)
	{
		double x = (i + .5)*step;
#pragma omp atomic
		sum = sum + 4.0/(1.+ x*x);
	}
	
	//pi= sum/numb_of_steps
	pi = sum*step;
	stop = clock();
	real_stop=omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n",pi);
	printf("Suma czasu przetwarzania wszystkich wątków wynosi %f sekund\n",((double)(stop - start)/1000000.0));
	printf("Rzeczywisty czas przetwarzania wynosi %lf sekund\n\n",((double)(real_stop - real_start)));
	return 0;
}
