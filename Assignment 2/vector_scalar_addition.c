#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100000000  // Adjust this for different data sizes

void vector_scalar_add(double* a, double scalar, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        a[i] += scalar;
    }
}

int main() {
    double* vector = (double*)malloc(SIZE * sizeof(double));
    double scalar = 3.14;
    int num_threads;
    
    // Initialize vector
    for (int i = 0; i < SIZE; i++) {
        vector[i] = i * 1.0;
    }
    
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);
    
    double start_time = omp_get_wtime();
    vector_scalar_add(vector, scalar, SIZE);
    double end_time = omp_get_wtime();
    
    printf("Time taken: %f seconds\n", end_time - start_time);
    
    // Verify result (check a few elements)
    for (int i = 0; i < 5; i++) {
        printf("vector[%d] = %f\n", i, vector[i]);
    }
    
    free(vector);
    return 0;
}