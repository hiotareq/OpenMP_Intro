#include <iostream>
#include <omp.h>
#include <deque>

int main()
{
    std::deque<int> processes_deque1;
#pragma omp parallel shared(processes_deque1)
    {

// printing to track forward proceeding of threads
#pragma omp master
        {
            std::cout << "Forward printing threads' num:"
                      << "\n";
        }

// this barrier is for beautiful output to the command line. for example, some processes could execute their print before master print
#pragma omp barrier

//this critical section is for clear output
#pragma omp critical
        {
            std::cout << "Hello, World! I'm thread number " << omp_get_thread_num() << "\n";
        }
        processes_deque1.push_back(omp_get_thread_num());

// the purpose of this barrier is to wait until all processes print there numbers and to clearly declare backward pritning
#pragma omp barrier

// master process declares backward printing
#pragma omp master
        {
            std::cout << "\n";
            std::cout << "Backward printing threads' num:"
                      << "\n";
        }

// purpose of this barrier is that processes have to wait until declaration of backward printing will be printed
#pragma omp barrier
        while (omp_get_thread_num() != processes_deque1.back())
        {
        }

        std::cout << "Hello, World! I'm Thread number " << processes_deque1.back() << "\n";
        processes_deque1.pop_back();
    }
    return 0;
}