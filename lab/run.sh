mpicxx 2v.cpp -o mpi
mpirun -np 4 mpi --mca opal_warn_on_missing_libcuda 0
rm ./mpi