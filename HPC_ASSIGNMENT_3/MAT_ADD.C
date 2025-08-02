#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void add_matrices(int **A, int **B, int **C, int N, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int **allocate_matrix(int N) {
    int **mat = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        mat[i] = (int *)malloc(N * sizeof(int));
    }
    return mat;
}

void fill_matrix(int **mat, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = rand() % 100;
}

void free_matrix(int **mat, int N) {
    for (int i = 0; i < N; i++)
        free(mat[i]);
    free(mat);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 6, 8, 10};

    for (int s = 0; s < sizeof(sizes) / sizeof(sizes[0]); s++) {
        int N = sizes[s];
        printf("\nMatrix Size: %d x %d\n", N, N);

        int **A = allocate_matrix(N);
        int **B = allocate_matrix(N);
        int **C = allocate_matrix(N);

        fill_matrix(A, N);
        fill_matrix(B, N);

        for (int t = 0; t < sizeof(threads) / sizeof(threads[0]); t++) {
            int num_threads = threads[t];
            double start = omp_get_wtime();

            add_matrices(A, B, C, N, num_threads);

            double end = omp_get_wtime();
            printf("Threads: %d | Time: %.6f seconds\n", num_threads, end - start);
        }

        free_matrix(A, N);
        free_matrix(B, N);
        free_matrix(C, N);
    }

    return 0;
}
