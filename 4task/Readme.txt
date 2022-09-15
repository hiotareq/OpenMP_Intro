Explanation

task4_add:
This program creates matrices A and B of size 1000x1000, counts their product, writes it to the OUT matrix and compares the running times of different methods.
Methods for comparison: 
Single thread:
1. Simple multiplication.
2. Multiplication using fewer accesses to pointers of the resulting matrix.
3. Multiplication using transposed matrix for more cache hits.
    Parallel execution:
1. Simple multiplication.
2. Multiplication using less number of calls to pointers of resulting matrix.
3. Multiplication using transposed matrix for more cache hits (not so efficient for parallel execution).
4. Combined use of items 2. and 3.
In the fastest multiplication it was obtained by experience that the highest speed is achieved when using the directive "schedule(dynamic,1)"

Default size of matrices is 1000

USAGE:
1. mkdir CMake
2. cd CMake
3. cmake ..
4. make
5. cd ..
6. OMP_NUM_THREADS=N ./task4_add