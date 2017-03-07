#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 100000;
double step;

int main (int argc, char *argv[])
{
    double begin = omp_get_wtime();
    
    #pragma omp parallel
    {
        int i;
        double x, pi, sum = 0.0;
        
        step = 1.0 / (double) num_steps;
        
        for (i = 0; i < num_steps; i++)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        pi = step * sum;
        
        printf("%d/%d:\t pi = %f\n", omp_get_thread_num(), omp_get_num_threads(),pi);
    }
    
    printf("Running time: %f\n", omp_get_wtime() - begin);
}