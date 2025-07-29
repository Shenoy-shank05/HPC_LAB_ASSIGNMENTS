#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000000; 

    int *A = (int *)malloc(n * sizeof(int));
    int *B = (int *)malloc(n * sizeof(int));
    int *C = (int *)malloc(n * sizeof(int));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

   
    for (int i = 0; i < n; i++) {
        A[i] = i;
        B[i] = i;
    }

    int threads[] = {1, 2, 4, 6, 8, 10};

    for (int t = 0; t < 6; t++) {
        omp_set_num_threads(threads[t]);

        double start_time = omp_get_wtime();

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            C[i] = A[i] + B[i];
        }

        double end_time = omp_get_wtime();
        printf("Time taken with %d threads: %.6f seconds\n", threads[t], end_time - start_time);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
