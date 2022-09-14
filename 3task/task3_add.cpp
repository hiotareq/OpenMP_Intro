#include <iostream>
#include <omp.h>
#include <vector>
#include <climits>

int main(int argc, char *argv[])
{
    // define size of our array
    size_t SIZE = 100000;

    // define our array of unsigned long longs because we will multiply very big numbers
    unsigned long long numbers[SIZE];

    // cycle to fullfill our array with natural numbers up to SIZE
    for (unsigned long long i = 0; i < SIZE; ++i)
        numbers[i] = i + 1;

    // precalculate new first element of array because i don't know how to calculate it in parallel
    unsigned long long int new_0 = numbers[0] * numbers[1] / 3;

    // precalculate new last element of array because i don't know how to calculate it in parallel
    unsigned long long int new_last = numbers[SIZE - 2];
    new_last /= 3;
    new_last *= numbers[SIZE - 1];

    // printf first element of modified array
    printf("numbers[0]=%d, master thread %d \n", new_0);

// start of parallel section
#pragma omp parallel shared(numbers)
    {

        // start of parallel for with static schedule because I want every element to be calculated before previous element will be inserted in array. Before inserting I print new element of array
#pragma omp for ordered schedule(static, 1)
        for (int i = 1; i < SIZE - 1; ++i)
        {
            // this is temp variable because I don't want change elements of array too early (before inserting previous element)
            unsigned long long int temp = 0;

            // because we multiply big numbers, and therefore I don't want overfloating, I check if one of numbers is divisible by 3 and make temp as less as posible.
            if (numbers[i - 1] % 3 == 0)
            {
                temp = numbers[i - 1] / 3;
                temp *= numbers[i];
                temp *= numbers[i + 1];
            }
            if (numbers[i] % 3 == 0)
            {
                temp = numbers[i] / 3;
                temp *= numbers[i - 1];
                temp *= numbers[i + 1];
            }
            if (numbers[i + 1] % 3 == 0)
            {
                temp = numbers[i + 1] / 3;
                temp *= numbers[i];
                temp *= numbers[i - 1];
            }

// print new array[i] and threads' number in ascending order
#pragma omp ordered
            printf("numbers[%d]=%lld, thread number %d \n", i, temp, omp_get_thread_num());
            numbers[i] = temp;
        }
    }
    // print last element of new array
    printf("numbers[999999]=%lld, master thread\n", new_last);

    // cnange memorized first and last elements of new array
    numbers[SIZE - 1] = new_last;
    numbers[0] = new_0;
    return 0;
}