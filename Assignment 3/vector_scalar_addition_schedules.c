#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200

void vector_scalar_add(double *a, double scalar, int size, int chunk_size, int schedule_type) {
    if (schedule_type == 0) {  // STATIC
        #pragma omp parallel for schedule(static, chunk_size)
        for (int i = 0; i < size; i++) {
            a[i] += scalar;
        }
    } else if (schedule_type == 1) {  // DYNAMIC
        #pragma omp parallel for schedule(dynamic, chunk_size)
        for (int i = 0; i < size; i++) {
            a[i] += scalar;
        }
    }
}

int main() {
    double *vector = (double *)malloc(SIZE * sizeof(double));
    double scalar = 3.14;
    int chunk_sizes[] = {1, 5, 10, 20, 50};
    int num_chunk_sizes = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);

    // Initialize vector
    for (int i = 0; i < SIZE; i++) {
        vector[i] = i * 1.0;
    }

    printf("STATIC Schedule:\n");
    for (int i = 0; i < num_chunk_sizes; i++) {
        double start_time = omp_get_wtime();
        vector_scalar_add(vector, scalar, SIZE, chunk_sizes[i], 0);
        double end_time = omp_get_wtime();
        printf("Chunk size: %d, Time: %f seconds\n", chunk_sizes[i], end_time - start_time);
    }

    printf("\nDYNAMIC Schedule:\n");
    for (int i = 0; i < num_chunk_sizes; i++) {
        double start_time = omp_get_wtime();
        vector_scalar_add(vector, scalar, SIZE, chunk_sizes[i], 1);
        double end_time = omp_get_wtime();
        printf("Chunk size: %d, Time: %f seconds\n", chunk_sizes[i], end_time - start_time);
    }

    // Demonstrate nowait clause
    printf("\nDemonstrating nowait clause:\n");
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE / 2; i++) {
            vector[i] += scalar;
        }

        #pragma omp for
        for (int i = SIZE / 2; i < SIZE; i++) {
            vector[i] += scalar;
        }
    }

    free(vector);
    return 0;
}