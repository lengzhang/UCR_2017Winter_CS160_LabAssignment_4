/*
    Create a parallel version of the pi program using a loop construct. Your
    goal is to minimize the number changes made to the serial program. Please
    use the OpenMP runtime library routine omp_get_wtime() to measure the
    execution time of the computational section in the program.
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 100000;

int main (int argc, char *argv[])
{
    double pi, full_sum;
    double step = 1.0 / (double) num_steps;
    double start_time, run_time;
    
    int i;
    for (i = 1; i <= 8; i++)
    {
        start_time = omp_get_wtime();
        omp_set_num_threads(i);
        full_sum = 0.0;
        
        int j;
        double sum[i];
        for (j = 0; j < i; j++) {
            sum[j] = 0.0;
        }
        
        #pragma omp parallel for
        for (j = 0; j < num_steps; j++)
        {
            double x = (j + 0.5) / (double) num_steps;
            sum[omp_get_thread_num()] += 4.0 / (1.0 + x * x);
        }
        
        for (j = 0; j < i; j++)
        {
            full_sum += sum[j];
        }
        
        pi = full_sum * step;
        run_time = omp_get_wtime() - start_time;
        printf("pi is %f in %f seconds with %d with threads\n", pi, run_time, i);
    }
    return 0;
}