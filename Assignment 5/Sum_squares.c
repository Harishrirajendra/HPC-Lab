#include <stdio.h>
#include <omp.h>

// Sequential version
int sum_of_squares_sequential(int num_threads) {
    int sum = 0;
    for (int thread_id = 0; thread_id < num_threads; thread_id++) {
        int square = thread_id * thread_id;
        printf("Thread %d: Square = %d\n", thread_id, square);
        sum += square;
    }
    return sum;
}

// Parallel version
int sum_of_squares_parallel(int num_threads) {
    int sum = 0;
    #pragma omp parallel reduction(+:sum)
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;
        printf("Thread %d: Square = %d\n", thread_id, square);
        sum += square;
    }
    return sum;
}

int main() {
    int num_threads;
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Sequential execution
    double start_time = omp_get_wtime();
    int sum_seq = sum_of_squares_sequential(num_threads);
    double end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;
    printf("Sequential sum of squares: %d\n", sum_seq);
    printf("Sequential execution time: %f seconds\n\n", sequential_time);

    // Parallel execution
    start_time = omp_get_wtime();
    int sum_par = sum_of_squares_parallel(num_threads);
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    printf("Parallel sum of squares: %d\n", sum_par);
    printf("Parallel execution time: %f seconds\n\n", parallel_time);

    // Calculate speedup
    if (parallel_time > 0) {
        double speedup = sequential_time / parallel_time;
        printf("Speedup: %f\n", speedup);
    } else {
        printf("Parallel execution time is too small to calculate speedup.\n");
    }

    return 0;
}
