#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000  // Matrix size (N x N) and vector size (N)

void matrix_vector_multiply(int **A, int *x, int *y, int size) {
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
    double start_time, end_time;

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

    // Perform matrix-vector multiplication and measure time
    start_time = omp_get_wtime();
    matrix_vector_multiply(A, x, y, N);
    end_time = omp_get_wtime();

    printf("Matrix-vector multiplication completed.\n");
    printf("Time taken: %f seconds\n", end_time - start_time);

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}