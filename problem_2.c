#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 99999;

int main (int argc, char *argv[])
{
    double begin_time = omp_get_wtime();
    
    //omp_set_num_threads(2);
    int i;
    double sum[omp_get_max_threads()];
    for (i=0; i < omp_get_max_threads(); i++) {
        sum[i] = 0.0;
    }
    
    #pragma omp parallel for
    for (i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) / (double) num_steps;
        sum[omp_get_thread_num()] += 4.0 / (1.0 + x * x);
    }
    double total = 0.0;
    for (i=0; i < omp_get_max_threads(); i++) {
        total += sum[i];
    }
    double pi = total / (double) num_steps;
    printf("pi = %f\n", pi);
    
    printf("Running time: %f\n", omp_get_wtime() - begin_time);
}