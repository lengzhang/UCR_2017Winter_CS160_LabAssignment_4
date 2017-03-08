#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int i, j, k;
    #pragma omp parallel for private(j) num_threads(3)
    for (i = 0; i < 5; i++)
    {
        int id_i = omp_get_thread_num();
        #pragma omp parallel for num_threads(3)
        for (j = 0; j < 5; j++)
        {
            int id_j = omp_get_thread_num();
            printf("i: %d\tj: %d\t%d - %d\n", id_i, id_j, i, j);
        }
    }
}