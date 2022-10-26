EXPLANATION

The purpose of this program is to implement QuickSort with Hoare brakdown in parallel.

USAGE
1. mkdir CMake
2. cd CMake
3. cmake ..
4. make
5. cd ..
6. OMP_NUM_THREADS=n ./task8_add N --flags

Where N is size of array to sort. Flags may be:
k - to input array from keyboard
f - to input array from file
IF there is an "f" flag, then after that type name of file where array is, i.e "data.txt"

If no flags, then array will be filled with random integers from 1 to N, and then sorted.