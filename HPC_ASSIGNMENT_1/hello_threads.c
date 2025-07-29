#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);
    omp_set_num_threads(n);

    printf("\nSequential Hello:\n");
    for(int i = 0; i < n; i++)
        printf("Hello, World from thread %d (Sequential)\n", i);

    printf("\nParallel Hello:\n");
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello, World from thread %d (Parallel)\n", tid);
    }

    return 0;
}
