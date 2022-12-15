import matplotlib.pyplot as plt
import numpy as np

mpi_np_number = np.empty(4, dtype=np.double)
mpi_times = np.empty(4, dtype=np.double)

for i in range(4):
    mpi_np_number[i] = i + 1

mpi_times[0] = 0.227102
mpi_times[1] = 0.132375
mpi_times[2] = 0.115383
mpi_times[3] = 0.0865137

plt.scatter(mpi_np_number, mpi_times, s = 16)

plt.title("MPI graph")
plt.xlabel("np number")
plt.ylabel("Execution time of parallel region, sec")
plt.xticks([1,2,3,4])
plt.yticks([0.1, 0.12, 0.14, 0.16, 0.18, 0.2])
plt.savefig("MPI_exectime.jpg")

# mpi_acceleration = np.empty(4, dtype=np.double)

# mpi_acceleration[0] = 1
# mpi_acceleration[1] = mpi_times[0]/mpi_times[1]
# mpi_acceleration[2] = mpi_times[0]/mpi_times[2]
# mpi_acceleration[3] = mpi_times[0]/mpi_times[3]
# plt.scatter(mpi_np_number, mpi_acceleration, s = 16)
# plt.title("MPI acceleration")
# plt.savefig("MPI_acceleration.jpg")