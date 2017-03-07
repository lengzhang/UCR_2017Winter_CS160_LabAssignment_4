#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static long num_steps = 971;

int main (int argc, char *argv[])
{
    //omp_set_num_threads(2);
    
    double sum = 0.0;
    double step = 1.0 / (double) num_steps;
    int num_threads = omp_get_max_threads();
    
    double begin_time = omp_get_wtime();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int begin = id * num_steps / num_threads;
        int end = (id + 1) * num_steps / num_threads;
        
        if (id == num_threads - 1)
        {
            end = num_steps;
        }
        double x, y = 0.0;
        
        for (begin; begin < end; begin++)
        {
            x = (begin + 0.5) * step;
            y += 4.0 / (1.0 + x * x);
        }
        sum += y;
    }
    
    double pi = step * sum;
    printf("pi = %f\n", pi);
    
    printf("Running time: %f\n", omp_get_wtime() - begin_time);
}