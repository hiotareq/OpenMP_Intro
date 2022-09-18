#include <iostream>
#include <omp.h>
#include <iomanip>
#include <chrono>

int main(int argc, char *argv[])
{
    // check for valid args number
    if (argc != 2)
        return -1;

    // define the number of partition segments
    unsigned long long N = std::atoi(argv[1]);

    // initialize answer and stepsize
    long double answer = 0, step = 1 / (long double)(N);

    // take the time at the beginning of calculation
    auto start = std::chrono::high_resolution_clock::now();

    // parallel section for with dynamic scheduling with block size 1, so there is not much waiting for procecess, reduction is to summarize resulting answer
#pragma omp parallel for schedule(dynamic, 1) reduction(+ \
                                                        : answer) shared(N, step)
    for (unsigned long long i = 0; i < N; ++i)
    {
        long double x = (i + 0.5) * step;
        answer += step * 4 / (1 + x * x);
    }

    // time at the end of calculation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << duration.count() << " milliseconds" << std::endl;
    std::cout << std::setprecision(16);
    std::cout << answer << std::endl;
    return 0;
}