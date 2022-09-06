#include <iostream>
#include <omp.h>

int main()
{
    // N is the number to countto, partial sum is sum on sigle thread, answer is sum of all partial summs
    int N = 1000, partial_sum = 0, answer = 0;

    // here begins a parallel region with its own partial sums on each thread
#pragma omp parallel private(partial_sum) shared(answer)
    {
        // counting partial sums on every thread
#pragma omp for
        for (int i = 1; i <= N; ++i)
        {
            partial_sum += i;
        }

        // here every thread ads own partial sum to global sum/answer
#pragma omp critical
        {
            std::cout << "Thread number " << omp_get_thread_num()
                      << " partial sum = " << partial_sum << "\n";
            answer += partial_sum;
        }
    }
    std::cout << "Big summ is " << answer << "\n";
    return 0;
}