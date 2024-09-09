#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define SIZE 1000000  // Large array size

int main() {
    // Dynamically allocate array to avoid stack overflow for large SIZE
    int *arr = (int *)malloc(SIZE * sizeof(int));
    long long int sum = 0;  // Initialize sum as 0

    // Initialize array with values from 1 to SIZE
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    // Sequential execution to find the sum
    double start_time = omp_get_wtime();
    for (int i = 0; i < SIZE; i++) {
        sum += arr[i];
    }
    double end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;

    printf("Sequential Sum: %lld\n", sum);
    printf("Sequential Time: %f seconds\n", sequential_time);
    fflush(stdout);  // Ensure the output is flushed immediately

    // Reset sum for parallel execution
    sum = 0;

    // Parallel sum using OpenMP reduction
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += arr[i];
    }
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;

    printf("Parallel Sum: %lld\n", sum);
    printf("Parallel Time: %f seconds\n", parallel_time);
    fflush(stdout);  // Ensure the output is flushed immediately

    // Calculate speedup
    double speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    // Free dynamically allocated memory
    free(arr);

    return 0;
}
