Explanation

task2_main:
The main task - the threads must calculate the sum of the first Q natural numbers, Q is given by a variable within the program. Load sharing between threads is done automatically using the "#pragma omp for" directive.
By default, Q = 1000;

task2_add:
An additional task is to allow the user to set the Q number himself by passing it as an argument when starting the program. The load is also distributed among the threads using the "#schedule" directive. I chose to do the load balancing with dynamic,1 after reading the answer to this question: https://stackoverflow.com/questions/42970700/openmp-dynamic-vs-guided-scheduling
I also used the "reduction" directive, which automatically scales the partial sums after the summation is executed on all threads.

USAGE:
1. mkdir CMake
2. cd CMake
3. cmake ..
4. make
5. cd ..
6. OMP_NUM_THREADS=N ./task2_main
7. OMP_NUM_THREADS=N ./task2_add Q
Q is the number we want to count summ to

P.S. If you want to see that dynamic scheduling is actually working by giving equal load to threads, use the "7." with big Q or little N.