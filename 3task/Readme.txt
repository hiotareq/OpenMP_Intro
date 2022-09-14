Explanation 

task3_add:
The task of this program is to create an array of the first 100,000 natural numbers and to replace each element of that array with the product of three consecutive elements and a triplet. 
I implemented this algorithm using the directive "omp for ordered schedule(static,1)". The block size is equal to one, because the idea of the algorithm is that each thread waits for the previous thread to execute (replace the previous element) and only then inserts its own element.
To output the elements and to insert them sequentially, I used the directive "omp ordered'.

USAGE:
1. mkdir CMake
2. cd CMake
3. cmake ..
4. make
5. cd ..
6. OMP_NUM_THREADS=N ./task3_add