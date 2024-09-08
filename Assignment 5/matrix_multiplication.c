#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void matrix_multiply_serial(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_omp_static(int **A, int **B, int **C, int size) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_omp_dynamic(int **A, int **B, int **C, int size) {
    #pragma omp parallel for schedule(dynamic)
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
    A = malloc(SIZE * sizeof(int *));
    B = malloc(SIZE * sizeof(int *));
    C = malloc(SIZE * sizeof(int *));
    
    for (int i = 0; i < SIZE; i++) {
        A[i] = malloc(SIZE * sizeof(int));
        B[i] = malloc(SIZE * sizeof(int));
        C[i] = malloc(SIZE * sizeof(int));
    }
    
    // Initialize matrices
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Measure serial execution time
    double start = omp_get_wtime();
    matrix_multiply_serial(A, B, C, SIZE);
    double end = omp_get_wtime();
    printf("Serial time: %f seconds\n", end - start);

    // Measure OpenMP static scheduling execution time
    start = omp_get_wtime();
    matrix_multiply_omp_static(A, B, C, SIZE);
    end = omp_get_wtime();
    printf("Static schedule time: %f seconds\n", end - start);

    // Measure OpenMP dynamic scheduling execution time
    start = omp_get_wtime();
    matrix_multiply_omp_dynamic(A, B, C, SIZE);
    end = omp_get_wtime();
    printf("Dynamic schedule time: %f seconds\n", end - start);

    // Free memory
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
