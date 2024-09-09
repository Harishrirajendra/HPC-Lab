#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000  // Matrix size (N x N)

// Sequential matrix multiplication
void matrix_multiply_sequential(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Parallel matrix multiplication using OpenMP
void matrix_multiply_parallel(int **A, int **B, int **C, int size) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int **A, **B, **C;
    double start_time, end_time, sequential_time, parallel_time, speedup;

    // Allocate memory for matrices
    A = (int **)malloc(N * sizeof(int *));
    B = (int **)malloc(N * sizeof(int *));
    C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    // Initialize matrices A and B with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Sequential matrix multiplication and time measurement
    start_time = omp_get_wtime();
    matrix_multiply_sequential(A, B, C, N);
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("Sequential matrix multiplication completed.\n");
    printf("Time taken (sequential): %f seconds\n", sequential_time);

    // Parallel matrix multiplication and time measurement
    start_time = omp_get_wtime();
    matrix_multiply_parallel(A, B, C, N);
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("Parallel matrix multiplication completed.\n");
    printf("Time taken (parallel): %f seconds\n", parallel_time);

    // Calculate speedup
    speedup = sequential_time / parallel_time;
    printf("Speedup: %f\n", speedup);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
