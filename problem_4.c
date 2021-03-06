/*
    Does the following OpenMP code segment parallelize the for-loop correctly or not? Why?

    int i, j, a[MAX];
    j=1;
    #pragma omp parallel for
    for (i=0; i<MAX; i++) {
        j=j+2;
        a[i]=comp(j);
    }
*/

/*
    Answer:
        No because this code segment will cause race problem. Before thread A
        reaches to a[i]=comp(j), another thread reaches to j=j+2. Therefore,
        when thread A reaches to a[i]=comp(j), the value of j is not the value
        thread want.
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int MAX = 10;

int main (int argc, char *argv[])
{
    //  test
    int i, j, a[MAX];
    j=1;
    #pragma omp parallel for
    for (i=0; i<MAX; i++) {
        j=j+2;
        printf("%d - 1\t%d - %d\n", omp_get_thread_num(), i, j);
        a[i]=j;
        printf("%d - 2\t%d - %d\n", omp_get_thread_num(), i, j);
        
    }
    
    for (i=0; i<MAX; i++)
    {
        printf("%d - %d\t", i, a[i]);
    }
    printf("\n");
}