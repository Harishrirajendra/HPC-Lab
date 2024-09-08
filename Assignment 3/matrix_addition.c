#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_addition(int **A, int **B, int **C, int size) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int thread_counts[] = {1, 2, 4, 8};
    int num_thread_counts = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        int **A = (int **)malloc(size * sizeof(int *));
        int **B = (int **)malloc(size * sizeof(int *));
        int **C = (int **)malloc(size * sizeof(int *));
        
        for (int i = 0; i < size; i++) {
            A[i] = (int *)malloc(size * sizeof(int));
            B[i] = (int *)malloc(size * sizeof(int));
            C[i] = (int *)malloc(size * sizeof(int));
            for (int j = 0; j < size; j++) {
                A[i][j] = rand() % 100;
                B[i][j] = rand() % 100;
            }
        }

        printf("Matrix size: %d x %d\n", size, size);
        for (int t = 0; t < num_thread_counts; t++) {
            int threads = thread_counts[t];
            omp_set_num_threads(threads);

            double start_time = omp_get_wtime();
            matrix_addition(A, B, C, size);
            double end_time = omp_get_wtime();

            printf("Threads: %d, Time: %f seconds\n", threads, end_time - start_time);
        }

        // Free memory
        for (int i = 0; i < size; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);

        printf("\n");
    }

    return 0;
}