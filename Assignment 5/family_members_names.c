#include <stdio.h>
#include <omp.h>

// Sequential version
void family_sequential() {
    for (int i = 0; i < 4; i++) {
        switch(i) {
            case 0: printf("Thread %d: Father\n", i); break;
            case 1: printf("Thread %d: Mother\n", i); break;
            case 2: printf("Thread %d: Sister\n", i); break;
            case 3: printf("Thread %d: Brother\n", i); break;
            default: printf("Thread %d: Extended family member\n", i);
        }
    }
}

// Parallel version
void family_parallel() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        switch(thread_id) {
            case 0: printf("Thread %d: Father\n", thread_id); break;
            case 1: printf("Thread %d: Mother\n", thread_id); break;
            case 2: printf("Thread %d: Sister\n", thread_id); break;
            case 3: printf("Thread %d: Brother\n", thread_id); break;
            default: printf("Thread %d: Extended family member\n", thread_id);
        }
    }
}

int main() {
    double start_time, end_time, sequential_time, parallel_time;
    
    // Sequential execution
    start_time = omp_get_wtime();
    family_sequential();
    end_time = omp_get_wtime();
    sequential_time = end_time - start_time;
    printf("\nSequential execution time: %f seconds\n", sequential_time);
    
    // Parallel execution
    start_time = omp_get_wtime();
    family_parallel();
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;
    printf("\nParallel execution time: %f seconds\n", parallel_time);
    
    // Calculate speedup
    if (parallel_time > 0) {
        double speedup = sequential_time / parallel_time;
        printf("\nSpeedup: %f\n", speedup);
    } else {
        printf("\nParallel execution time is too small to calculate speedup.\n");
    }
    
    return 0;
}
