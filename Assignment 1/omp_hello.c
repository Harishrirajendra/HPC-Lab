#include <stdio.h>
#include <omp.h>

int main(void) {
    int num_threads;
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    
    // Set the number of threads
    omp_set_num_threads(num_threads);
    
    // Sequential execution
    printf("\nSequential output:\n");
    for (int i = 0; i < num_threads; i++) {
        printf("Hello, World from thread %d\n", i);
    }
    
    // Parallel execution
    printf("\nParallel output:\n");
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello, World from thread %d\n", thread_id);
    }
    
    return 0;
}