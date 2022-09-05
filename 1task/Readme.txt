Explanation

task1_main:
The main task is for the streams to get the numbers out.

task1_add:
An additional task - the threads output their numbers and then output them in reverse order. The order in which threads output their numbers the first time is remembered in my program with std::deque;

USAGE:
1. mkdir CMake
2. cd CMake
3. cmake ..
4. OMP_NUM_THREADS=N ./task1_main
5. OMP_NUM_THREADS=N ./task1_add