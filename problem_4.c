#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int MAX = 10;

int main (int argc, char *argv[])
{
    int i, j, a[MAX];
    j=1;
    #pragma omp parallel for
    for (i=0; i<MAX; i++) {
        j=j+2;
        printf("1:\t%d\t%d - %d\n", omp_get_thread_num(), i, j);
        a[i]=j;
        printf("2:\t%d\t%d - %d\n", omp_get_thread_num(), i, j);
        
    }
    
    for (i=0; i<MAX; i++)
    {
        printf("%d - %d\t", i, a[i]);
    }
    printf("\n");
}