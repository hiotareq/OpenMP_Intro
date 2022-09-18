Explanation

The task of this program is to calculate the number of Pi in parallel mode with the greatest accuracy and with the least amount of time.
I have solved this problem by using the "omp for" directive with a dynamic schedule type and block size equal to one, because this choice gives the shortest downtime for each thread and in this problem there is no need to get into caches to improve performance (no arrays, so no caches).
The best accuracy I could get was 15 decimal numbers after point with the number of partition segments (the argument to start the program) equal to 1000000000000000000.

USAGE
1. mkdir CMake
2. cd CMake
3. cmake ..
4. make
5. cd ..
6. OMP_NUM_THREADS=n ./task5_add N

Where N is the number of partition segments