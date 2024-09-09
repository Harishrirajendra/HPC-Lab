#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000  // Matrix size (N x N) and vector size (N)

// Sequential matrix-vector multiplication
void matrix_vector_multiply_sequential(int **A, int *x, int *y, int size) {
    for (int i = 0; i < size; i++) {
        y[i] = 0;
        for (int j = 0; j < size; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

// Parallel matrix-vector multiplication using OpenMP
void matrix_vector_multiply_parallel(int **A, int *x, int *y, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        y[i] = 0;
        for (int j = 0; j < size; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main() {
    int **A, *x, *y;
    double start_time, end_time, sequential_time, parallel_time, speedup;

    // Allocate memory
    A = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
    }
    x = (int *)malloc(N * sizeof(int));
    y = (int *)malloc(N * sizeof(int));

    // Initialize matrix A and vector x with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
        x[i] = rand() % 10;
    }

    // Sequential matrix-vector multiplication and time measurement
    start_time = omp_get_wtime();
    matrix_vector_multiply_sequential(A, x, y, N);
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Sequential matrix-vector multiplication completed.\n");
    printf("Time taken (sequential): %f seconds\n", sequential_time);

    // Parallel matrix-vector multiplication and time measurement
    start_time = omp_get_wtime();
    matrix_vector_multiply_parallel(A, x, y, N);
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel matrix-vector multiplication completed.\n");
    printf("Time taken (parallel): %f seconds\n", parallel_time);

    // Calculate speedup
    speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}
