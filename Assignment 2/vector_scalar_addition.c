#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100000000  // Adjust this for different data sizes

// Sequential version of vector scalar addition
void vector_scalar_add_sequential(double* a, double scalar, int size) {
    for (int i = 0; i < size; i++) {
        a[i] += scalar;
    }
}

// Parallel version of vector scalar addition
void vector_scalar_add_parallel(double* a, double scalar, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        a[i] += scalar;
    }
}

int main() {
    double* vector_sequential = (double*)malloc(SIZE * sizeof(double));
    double* vector_parallel = (double*)malloc(SIZE * sizeof(double));
    double scalar = 3.14;
    int num_threads;
    
    // Initialize both vectors
    for (int i = 0; i < SIZE; i++) {
        vector_sequential[i] = i * 1.0;
        vector_parallel[i] = i * 1.0;
    }
    
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);
    
    // Sequential execution
    double start_time = omp_get_wtime();
    vector_scalar_add_sequential(vector_sequential, scalar, SIZE);
    double end_time = omp_get_wtime();
    double sequential_time = end_time - start_time;
    printf("Sequential execution time: %f seconds\n", sequential_time);
    
    // Parallel execution
    start_time = omp_get_wtime();
    vector_scalar_add_parallel(vector_parallel, scalar, SIZE);
    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;
    printf("Parallel execution time: %f seconds\n", parallel_time);
    
    // Calculate speedup
    if (parallel_time > 0) {
        double speedup = sequential_time / parallel_time;
        printf("\nSpeedup: %f\n", speedup);
    } else {
        printf("\nParallel execution time is too small to calculate speedup.\n");
    }
    
    // Verify result (check a few elements for both sequential and parallel)
    for (int i = 0; i < 5; i++) {
        printf("Sequential vector[%d] = %f, Parallel vector[%d] = %f\n", 
               i, vector_sequential[i], i, vector_parallel[i]);
    }
    
    free(vector_sequential);
    free(vector_parallel);
    return 0;
}
