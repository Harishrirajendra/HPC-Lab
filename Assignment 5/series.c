#include <stdio.h>
#include <omp.h>

// Function to print multiples of 2
void print_series_2() {
    for (int i = 1; i <= 10; i++) {
        printf("Thread 1: %d\n", 2 * i);
    }
}

// Function to print multiples of 4
void print_series_4() {
    for (int i = 1; i <= 10; i++) {
        printf("Thread 2: %d\n", 4 * i);
    }
}

int main() {
    double start_time, end_time, sequential_time, parallel_time, speedup;

    // Sequential execution
    start_time = omp_get_wtime();  // Start timer for sequential execution
    print_series_2();
    print_series_4();
    end_time = omp_get_wtime();    // End timer for sequential execution

    sequential_time = end_time - start_time;  // Calculate sequential execution time
    printf("\nSequential execution time: %f seconds\n\n", sequential_time);

    // Parallel execution using OpenMP
    start_time = omp_get_wtime();  // Start timer for parallel execution
    #pragma omp parallel sections
    {
        #pragma omp section
        print_series_2();

        #pragma omp section
        print_series_4();
    }
    end_time = omp_get_wtime();    // End timer for parallel execution

    parallel_time = end_time - start_time;  // Calculate parallel execution time
    printf("\nParallel execution time: %f seconds\n\n", parallel_time);

    // Calculate speedup
    speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    return 0;
}
