#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n = 100000000;
    int *A = (int*)malloc(n * sizeof(int));
    int *B = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    qsort(A, n, sizeof(int), asc);
    qsort(B, n, sizeof(int), desc);

    int threads[] = {1, 2, 4, 6, 8, 10};

    for (int t = 0; t < sizeof(threads)/sizeof(threads[0]); t++) {
        omp_set_num_threads(threads[t]);
        long long result = 0;

        double start = omp_get_wtime();

        #pragma omp parallel for reduction(+:result) schedule(static)
        for (int i = 0; i < n; i++) {
            result += (long long)A[i] * B[i];
        }

        double end = omp_get_wtime();

        printf("Threads: %2d | Min Scalar Product = %lld | Time = %.6f s\n",
               threads[t], result, end - start);
    }

    free(A);
    free(B);
    return 0;
}
