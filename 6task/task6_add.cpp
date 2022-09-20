#include <iostream>
#include <omp.h>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;

    // define
    const unsigned long N = std::atoi(argv[1]);

    // define counter of prime numbers
    unsigned counter = 0;

    // vector of our numbers, "1" is prime number, "0" is otherwise
    std::vector<char> numbers(N + 1, 1);

    // 0 and 1 are not prime numbers
    numbers[0] = numbers[1] = 0;

// parallel realization of Eratosthenes sieve
#pragma omp parallel shared(numbers, counter)
    {
#pragma omp single
        {
            for (size_t i = 2; i * i <= N; ++i)
            {
                if (numbers[i] == 1)
#pragma omp task
                {
                    for (size_t j = i * i; j <= N; j += i)
                        numbers[j] = 0;
                }
            }
#pragma omp taskwait
        }

        // count number of prime numbers
#pragma omp for reduction(+ \
                          : counter)
        for (size_t i = 1; i <= N; ++i)
            if (numbers[i] == 1)
                counter++;
    }

    // print number of prime numbers
    printf("There are %u prime numbers from 1 to %u\n", counter, N);

    return 0;
}