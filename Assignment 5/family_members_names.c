#include <stdio.h>
#include <omp.h>

int main() {
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
    return 0;
}