#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

const long long num_steps = 1000000000;
double step, s2[100];

int main(int argc, char* argv[])
{
	printf ("Nazwa programu: %s\n", __FILE__);
	if (argc>0){
		omp_set_num_threads(atoi(argv[1]));
		printf("Zadana liczba wątków: %s\n", argv[1]);
	}
	clock_t start, stop;
	double pi, sum=0.0, x, real_start, real_stop;
	step = 1./(double)num_steps;
	start = clock();
	real_start=omp_get_wtime();
	
	int i=0, num;
#pragma omp parallel private(num)
	{
		num=omp_get_thread_num();
#pragma omp for private (x)
		for (i=0; i<num_steps; i++){
			x = (i + .5)*step;
			s2[num]=s2[num]+ 4.0/(1.+ x*x);
		}

#pragma omp critical
		{sum=sum+s2[num];}
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
