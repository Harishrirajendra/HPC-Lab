#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 100000000  // Adjust this for different data sizes

// Sequential version of Pi calculation
double calculate_pi_sequential() {
    double pi = 0.0;
    double step = 1.0 / (double)NUM_STEPS;
    for (int i = 0; i < NUM_STEPS; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }
    pi *= step;
    return pi;
}

// Parallel version of Pi calculation
double calculate_pi_parallel(int num_threads) {
    double pi = 0.0;
    double step = 1.0 / (double)NUM_STEPS;
    
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        double x, sum = 0.0;
        #pragma omp for
        for (int i = 0; i < NUM_STEPS; i++) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
        pi += sum * step;
    }

    return pi;
}

int main() {
    int num_threads;
    double sequential_pi, parallel_pi;
    double sequential_time, parallel_time;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    
    // Sequential execution
    double start_time = omp_get_wtime();
    sequential_pi = calculate_pi_sequential();
    double end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    
    printf("Sequential Pi = %.15f\n", sequential_pi);
    printf("Sequential time taken: %f seconds\n", sequential_time);
    
    // Parallel execution
    start_time = omp_get_wtime();
    parallel_pi = calculate_pi_parallel(num_threads);
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    
    printf("Parallel Pi = %.15f\n", parallel_pi);
    printf("Parallel time taken: %f seconds\n", parallel_time);
    
    // Calculate speedup
    if (parallel_time > 0) {
        double speedup = sequential_time / parallel_time;
        printf("\nSpeedup: %f\n", speedup);
    } else {
        printf("\nParallel execution time is too small to calculate speedup.\n");
    }

    return 0;
}
