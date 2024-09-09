#include <stdio.h>
#include <omp.h>

// Sequential sum of first n natural numbers
int sum_sequential(int n) {
    int total_sum = 0;
    for (int i = 1; i <= n; i++) {
        total_sum += i;
    }
    return total_sum;
}

// Parallel sum of first n natural numbers
int sum_parallel(int n) {
    int total_sum = 0;
    
    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 1; i <= n; i++) {
        total_sum += i;
    }

    return total_sum;
}

int main() {
    int n = 20;   
    // Sequential execution
    double start_time = omp_get_wtime();
    int sum_seq = sum_sequential(n);
    double end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;
    printf("Sequential sum: %d\n", sum_seq);
    printf("Sequential execution time: %f seconds\n", sequential_time);
    // Parallel execution
    start_time = omp_get_wtime();
    int sum_par = sum_parallel(n);
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    printf("Parallel sum: %d\n", sum_par);
    printf("Parallel execution time: %f seconds\n", parallel_time);
    // Calculate speedup
    if (parallel_time > 0) {
        double speedup = sequential_time / parallel_time;
        printf("Speedup: %f\n", speedup);
    } else {
        printf("Parallel execution time is too small to calculate speedup.\n");
    }
    return 0;
}
