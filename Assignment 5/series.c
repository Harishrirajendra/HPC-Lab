#include <stdio.h>
#include <omp.h>

void print_series_2() {
    for (int i = 1; i <= 10; i++) {
        printf("Thread 1: %d\n", 2 * i);
    }
}

void print_series_4() {
    for (int i = 1; i <= 10; i++) {
        printf("Thread 2: %d\n", 4 * i);
    }
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        print_series_2();

        #pragma omp section
        print_series_4();
    }
    return 0;
}
