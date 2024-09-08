#include <stdio.h>
#include <omp.h>

long long fibonacci(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    int n = 50;  // Calculate up to the 50th Fibonacci number
    long long result;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    end_time = omp_get_wtime();

    printf("The %dth Fibonacci number is: %lld\n", n, result);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}