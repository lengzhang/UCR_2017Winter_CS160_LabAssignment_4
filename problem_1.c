/*
    Create a parallel version of the pi program using a parallel construct.
    Please use the OpenMP runtime library routine omp_get_wtime() to measure the
    execution time of the computational section in the program.
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 100000;

int main (int argc, char *argv[])
{
    //omp_set_num_threads(2);
    
    double pi, full_sum;
    double step = 1.0 / (double) num_steps;
    double start_time, run_time;
    
    int i;
    for (i = 1; i <= 8; i++)
    {
        start_time = omp_get_wtime();
        omp_set_num_threads(i);
        full_sum = 0.0;
        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            int num_threads = omp_get_num_threads();
            double x, sum = 0.0;
            
            int j;
            for (j = id; j < num_steps; j += num_threads)
            {
                x = (j + 0.5) * step;
                sum = sum + 4.0 / (1.0 + x * x);
            }
            full_sum += sum;
        }
        pi = step * full_sum;
        run_time = omp_get_wtime() - start_time;
        printf("pi is %f in %f seconds with %d threads\n", pi, run_time, i);
    }
    return 0;
}