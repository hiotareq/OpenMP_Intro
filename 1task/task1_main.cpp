#include <iostream>
#include <omp.h>
#include <deque>

int main()
{
#pragma omp parallel
    {
// this critical section is for beatiful print of numbers of threads,
//  so there won't any lines like "\n\n"
#pragma omp critical
        {
            std::cout << "Hello, World! I'm thread number " << omp_get_thread_num() << "\n";
        }
    }
    return 0;
}