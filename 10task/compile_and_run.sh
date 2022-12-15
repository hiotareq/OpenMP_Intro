g++ -c -fopenmp solvers.cpp main.cpp
g++ -fopenmp solvers.o main.o -o a.out
OMP_NUM_THREADS=4 ./a.out
./plot.py
rm -r a.out main.o solvers.o
rm -r *.dat