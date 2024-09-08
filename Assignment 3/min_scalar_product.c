#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define SIZE 100000

void generate_random_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;  // Random numbers between 0 and 99
    }
}

int min_scalar_product(int arr1[], int arr2[], int size) {
    int min_product = INT_MAX;
    
    #pragma omp parallel for reduction(min:min_product)
    for (int i = 0; i < size; i++) {
        int product = arr1[i] * arr2[i];
        if (product < min_product) {
            min_product = product;
        }
    }
    
    return min_product;
}

int main() {
    int arr1[SIZE], arr2[SIZE];
    double start_time, end_time;
    
    generate_random_array(arr1, SIZE);
    generate_random_array(arr2, SIZE);
    
    start_time = omp_get_wtime();
    int result = min_scalar_product(arr1, arr2, SIZE);
    end_time = omp_get_wtime();
    
    printf("Minimum scalar product: %d\n", result);
    printf("Time taken: %f seconds\n", end_time - start_time);
    
    return 0;
}