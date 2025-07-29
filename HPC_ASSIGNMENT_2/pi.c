#include <stdio.h>
#include <omp.h>

int main() {
    int num_steps=100000000;
    double step = 1.0 / (double)num_steps;
    double sum ;
    double pi;
    

  

    int threads[] = {1, 2, 4, 6, 8, 10};

    for (int t = 0; t < 6; t++) {
        sum = 0.0;
        omp_set_num_threads(threads[t]);
        double start_time = omp_get_wtime();

        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < num_steps; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

        pi = step * sum;

        double end_time = omp_get_wtime();
        printf("Pi with %d threads = %.15f | Time = %f seconds\n", threads[t], pi, end_time - start_time);
    }

    return 0;
}
