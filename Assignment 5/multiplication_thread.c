#include <stdio.h>
#include <omp.h>

// Sequential version of the series calculation
void calculate_series_sequential(int Aryabhatta, int num_threads) {
    for (int thread_id = 0; thread_id < num_threads; thread_id++) {
        int result = thread_id * Aryabhatta;
        printf("Thread %d: Result = %d\n", thread_id, result);
    }
}

// Parallel version of the series calculation
void calculate_series_parallel(int Aryabhatta) {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int result = thread_id * Aryabhatta;
        printf("Thread %d: Result = %d\n", thread_id, result);
    }
}

int main() {
    int Aryabhatta = 10;
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    // Sequential execution
    double start_time = omp_get_wtime();
    calculate_series_sequential(Aryabhatta, num_threads);
    double end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;
    printf("\nSequential execution time: %f seconds\n", sequential_time);
    // Parallel execution
    omp_set_num_threads(num_threads);
    start_time = omp_get_wtime();
    calculate_series_parallel(Aryabhatta);
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    printf("\nParallel execution time: %f seconds\n", parallel_time);
    // Calculate speedup
    if (parallel_time > 0) {
        double speedup = sequential_time / parallel_time;
        printf("\nSpeedup: %f\n", speedup);
    } else {
        printf("\nParallel execution time is too small to calculate speedup.\n");
    }
    return 0;
}
