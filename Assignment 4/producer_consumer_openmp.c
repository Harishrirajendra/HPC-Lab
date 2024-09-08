#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 50

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;

omp_lock_t mutex, full, empty;

void producer(int id) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100;  // Produce a random item
        
        omp_set_lock(&empty);
        omp_set_lock(&mutex);
        
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        
        printf("Producer %d produced item %d\n", id, item);
        
        omp_unset_lock(&mutex);
        omp_unset_lock(&full);
        
        // Simulate some work
        #pragma omp taskyield
    }
}

void consumer(int id) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        omp_set_lock(&full);
        omp_set_lock(&mutex);
        
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        
        printf("Consumer %d consumed item %d\n", id, item);
        
        omp_unset_lock(&mutex);
        omp_unset_lock(&empty);
        
        // Simulate some work
        #pragma omp taskyield
    }
}

int main() {
    omp_init_lock(&mutex);
    omp_init_lock(&full);
    omp_init_lock(&empty);
    
    #pragma omp parallel sections num_threads(4)
    {
        #pragma omp section
        producer(1);
        
        #pragma omp section
        producer(2);
        
        #pragma omp section
        consumer(1);
        
        #pragma omp section
        consumer(2);
    }
    
    omp_destroy_lock(&mutex);
    omp_destroy_lock(&full);
    omp_destroy_lock(&empty);
    
    return 0;
}