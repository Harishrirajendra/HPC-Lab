#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 100000000  // Adjust this for different data sizes

int main() {
    int num_threads;
    double pi = 0.0;
    double step = 1.0 / (double)NUM_STEPS;
    
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);
    
    double start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        double x, sum = 0.0;
        int i;
        #pragma omp for
        for (i = 0; i < NUM_STEPS; i++) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
        pi += sum * step;
    }
    
    double end_time = omp_get_wtime();
    
    printf("Calculated Pi = %.15f\n", pi);
    printf("Time taken: %f seconds\n", end_time - start_time);
    
    return 0;
}