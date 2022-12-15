import matplotlib.pyplot as plt
import numpy as np

mpi_np_number = np.empty(16, dtype=np.double)
mpi_times = np.empty(16, dtype=np.double)

for i in range(16):
    mpi_np_number[i] = i + 1

mpi_times[0] = 1.00326
mpi_times[1] = 0.591797
mpi_times[2] = 0.477541
mpi_times[3] = 0.42563
mpi_times[4] = 0.541745
mpi_times[5] = 0.6214
mpi_times[6] = 0.67047
mpi_times[7] = 0.68469
mpi_times[8] = 0.846286
mpi_times[9] = 0.775623
mpi_times[10] = 0.760162
mpi_times[11] = 0.789546
mpi_times[12] = 0.848118
mpi_times[13] = 0.806015
mpi_times[14] = 0.865145
mpi_times[15] = 0.869698

# plt.scatter(mpi_np_number, mpi_times, s = 16)

# plt.title("MPI graph")
# plt.xlabel("np number")
# plt.ylabel("Execution time of parallel region, sec")
# plt.savefig("MPI_exectime.jpg")

mpi_acceleration = np.empty(16, dtype=np.double)

for i in range(16):
    mpi_acceleration[i] = mpi_times[0]/mpi_times[i]

# plt.scatter(mpi_np_number, mpi_acceleration, s = 16)
# plt.title("MPI acceleration")
# plt.savefig("MPI_acceleration.jpg")

mpi_efficiency = np.empty(16, dtype=np.double)

for i in range(16):
    mpi_efficiency[i] = mpi_acceleration[i]/mpi_np_number[i]

plt.scatter(mpi_np_number, mpi_efficiency, s= 16)
plt.title("MPI efficiency")
plt.xlabel("np number")
plt.ylabel("Efficency")
plt.savefig("MPI_efficiency.jpg")