#include <stdio.h>
#include <omp.h>

int main(void) {
    int num_threads;
    double start_time, end_time, sequential_time, parallel_time, speedup;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    
    // Set the number of threads
    omp_set_num_threads(num_threads);
    
    // Sequential execution
    printf("\nSequential output:\n");
    start_time = omp_get_wtime();  // Start timing for sequential execution
    for (int i = 0; i < num_threads; i++) {
        printf("Hello, World from thread %d\n", i);
    }
    end_time = omp_get_wtime();  // End timing for sequential execution
    sequential_time = end_time - start_time;
    printf("Sequential execution time: %f seconds\n", sequential_time);
    
    // Parallel execution
    printf("\nParallel output:\n");
    start_time = omp_get_wtime();  // Start timing for parallel execution
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello, World from thread %d\n", thread_id);
    }
    end_time = omp_get_wtime();  // End timing for parallel execution
    parallel_time = end_time - start_time;
    printf("Parallel execution time: %f seconds\n", parallel_time);
    
    // Calculate speedup
    if (parallel_time > 0) {
        speedup = sequential_time / parallel_time;
        printf("\nSpeedup: %f\n", speedup);
    } else {
        printf("\nParallel execution time is too small to calculate speedup.\n");
    }

    return 0;
}
