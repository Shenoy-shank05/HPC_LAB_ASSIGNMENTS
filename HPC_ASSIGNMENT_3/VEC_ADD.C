#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000
#define SCALAR 5

void fill_vector(int *A, int n) {
    for (int i = 0; i < n; i++)
        A[i] = rand() % 100;
}

void vector_scalar_add_static(int *A, int *B, int n, int chunk, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < n; i++) {
        B[i] = A[i] + SCALAR;
    }
}

void vector_scalar_add_dynamic(int *A, int *B, int n, int chunk, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < n; i++) {
        B[i] = A[i] + SCALAR;
    }
}


void demo_nowait(int *A, int *B, int *C, int n, int num_threads) {
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < n; i++) {
            B[i] = A[i] + SCALAR;
        }

        #pragma omp for
        for (int i = 0; i < n; i++) {
            C[i] = A[i] * SCALAR;
        }
    }
}

int main() {
    int *A = (int *)malloc(SIZE * sizeof(int));
    int *B = (int *)malloc(SIZE * sizeof(int));
    int *C = (int *)malloc(SIZE * sizeof(int)); 

    fill_vector(A, SIZE);

    int chunks[] = {1, 5, 10, 20, 50, 100};
    int threads[] = {1, 2, 4};

    printf("=== Static Scheduling ===\n");
    for (int t = 0; t < sizeof(threads)/sizeof(threads[0]); t++) {
        for (int c = 0; c < sizeof(chunks)/sizeof(chunks[0]); c++) {
            double start = omp_get_wtime();
            vector_scalar_add_static(A, B, SIZE, chunks[c], threads[t]);
            double end = omp_get_wtime();

            printf("Threads: %d | Chunk: %3d | Time: %.6f s\n",
                   threads[t], chunks[c], end - start);
        }
    }

    printf("\n=== Dynamic Scheduling ===\n");
    for (int t = 0; t < sizeof(threads)/sizeof(threads[0]); t++) {
        for (int c = 0; c < sizeof(chunks)/sizeof(chunks[0]); c++) {
            double start = omp_get_wtime();
            vector_scalar_add_dynamic(A, B, SIZE, chunks[c], threads[t]);
            double end = omp_get_wtime();

            printf("Threads: %d | Chunk: %3d | Time: %.6f s\n",
                   threads[t], chunks[c], end - start);
        }
    }

    printf("\n=== Nowait Demo ===\n");
    double start = omp_get_wtime();
    demo_nowait(A, B, C, SIZE, 4);
    double end = omp_get_wtime();
    printf("Nowait demo completed in %.6f s\n", end - start);

    free(A);
    free(B);
    free(C);
    return 0;
}
