#include <stdio.h>
#include <omp.h>

int main() {
    int total_sum = 0;
    // Parallel region with shared total_sum
    #pragma omp parallel
    {
        int thread_sum = 0;  // Each thread computes a partial sum
        #pragma omp for
        for (int i = 0; i < 100; i++) {
            thread_sum += i;  // Each thread sums part of the range
        }
        // Using critical section to safely update total_sum
        #pragma omp critical
        {
            total_sum += thread_sum;
        }
        // Alternatively, we could use atomic to update total_sum
        // #pragma omp atomic
        // total_sum += thread_sum;
    }
    printf("Total sum: %d\n", total_sum);
    return 0;
}
