#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])
{
    // glob_sum is sum we want to count, it_num is number of for-loop iterations on single thread
    unsigned long long glob_sum = 0, it_num;

    // check if number of args is correct
    if (argc == 1 || argc > 2)
    {
        printf("Error: wrong number of arguments\n");
        return -1;
    }

    // Get the number to count to
    unsigned long long N = std::atoi(argv[1]);

    // here starts parallel region with its own number of iterations on every thread
#pragma omp parallel private(it_num)
    {
        it_num = 0;

        // adding partial sums to glob_sum and in the end of this section all partial sums will be added  together by reduction(+:glob_sum)
        // dynamic scheduling is the most optimal here in my opinion, according to https://stackoverflow.com/questions/42970700/openmp-dynamic-vs-guided-scheduling
#pragma omp for schedule(dynamic, 1) reduction(+ \
                                               : glob_sum)
        for (int i = 1; i <= N; ++i)
        {
            it_num++;
            glob_sum += i;
        }

        // this barrier is to have clear output in future
#pragma omp barrier

        // every thread prints own number of iterations it went throuth while counting summ
#pragma omp critical
        {
            printf("Threads' %d number of iterations is %d\n", omp_get_thread_num(), it_num);
        }

// barrier for clear output
#pragma omp barrier

// print answer that is global_sum
#pragma omp master
        {
            printf("Sum of %d first numbers is %d\n", N, glob_sum);
        }
    }
    return 0;
}