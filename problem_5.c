/*
    Consider the following OpenMP program segment.
    
    int a=1, b=2, c=3, d=4;
        …
    #pagama omp parallel private(b), firstprivate(c) lastprivate(d)
    {
        …
    }
*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int a = 1, b = 2, c = 3, d = 4, i;
    omp_set_num_threads(4);
    
    // (a)  a is shared in the parallel region
    // (b)  The initial value of a for each thread will be the value in main
    //      thread.
    #pragma omp parallel
    {
        printf("%d - 1\ta = %d\n", omp_get_thread_num(), a);
        a += 2;
        printf("%d - 2\ta = %d\n", omp_get_thread_num(), a);
    }
    printf("a = %d\n----------\n", a);
    /*
        1 - 1   a = 1
        1 - 2   a = 3
        0 - 1   a = 1
        0 - 2   a = 5
        2 - 1   a = 1
        2 - 2   a = 7
        3 - 1   a = 1
        3 - 2   a = 9
        a = 9
    */
    
    // (a)  b is local in the parallel region
    // (b)  Private will define a new variable as private member for every
    //      thread. Each thread has its own copy of b.
    //      Because the private variable b is not initialized, the initial value
    //      of b in each thread is unknow.
    //      (Global variable will be initialized automatically, and local
    //      variable will not be initialized automatically.)
    //
    //      Reference about initialize rule:
    //      http://billhoo.blog.51cto.com/2337751/733279
    #pragma omp parallel private(b)
    {
        printf("%d - 1\tb = %d\n", omp_get_thread_num(), b);
        b += 3;
        printf("%d - 2\tb = %d\n", omp_get_thread_num(), b);
    }
    printf("b = %d\n----------\n", b);
    /*
        2 - 1   b = 32767
        0 - 1   b = 0
        0 - 2   b = 3
        3 - 1   b = 32767
        3 - 2   b = 32770
        2 - 2   b = 32770
        1 - 1   b = 32767
        1 - 2   b = 32770
        b = 2
    */
    
    // (a)  c is local in the parallel region
    // (b)  Firstprivate will define and initialize a variable copy for the
    //      serial part of the code.
    //      The initial value of c for each thread will be the value of c in
    //      main thread.
    #pragma omp parallel for firstprivate(c)
    for (i = 0; i < 5; i++)
    {
        printf("%d - 1\ti = %d\tc = %d\n", omp_get_thread_num(), i, c);
        c += 3;
        printf("%d - 2\ti = %d\tc = %d\n", omp_get_thread_num(), i, c);
    }
    printf("c = %d\n----------\n", c);
    /*
        3 - 1   i = 4   c = 3
        3 - 2   i = 4   c = 6
        0 - 1   i = 0   c = 3
        0 - 2   i = 0   c = 6
        0 - 1   i = 1   c = 6
        0 - 2   i = 1   c = 9
        1 - 1   i = 2   c = 3
        1 - 2   i = 2   c = 6
        2 - 1   i = 3   c = 3
        2 - 2   i = 3   c = 6
        c = 3
    */
    
    // (a)  d is local in the parallel region
    // (b)  Lastprivate will copy the value of d in the last thread which
    //      executes the ending loop index to the master thread.
    //      The initial value of d is unknow because the variable d for each
    //      thread is not initialized.
    //      (Global variable will be initialized automatically, and local
    //      variable will not be initialized automatically.)
    #pragma omp parallel for lastprivate(d)
    for (i = 0; i < 5; i++)
    {
        printf("%d - 1\ti = %d\td = %d\n", omp_get_thread_num(), i, d);
        d = i * 3;
        printf("%d - 2\ti = %d\td = %d\n", omp_get_thread_num(), i, d);
    }
    printf("d = %d\n----------\n", d);
    /*
        0 - 1   i = 0   d = 32767
        0 - 2   i = 0   d = 0
        0 - 1   i = 1   d = 0
        0 - 2   i = 1   d = 3
        2 - 1   i = 3   d = -1
        2 - 2   i = 3   d = 9
        3 - 1   i = 4   d = -1
        3 - 2   i = 4   d = 12
        1 - 1   i = 2   d = -1
        1 - 2   i = 2   d = 6
        d = 12
    */
    return 0;
}