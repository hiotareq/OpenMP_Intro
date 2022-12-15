import matplotlib.pyplot as plt
import numpy as np

omp_np_number = np.empty(4, dtype=np.double)
omp_times = np.empty(4, dtype=np.double)

for i in range(4):
    omp_np_number[i] = i + 1

omp_times[0] = 0.179835
omp_times[1] = 0.108472
omp_times[2] = 0.0785812
omp_times[3] = 0.0774394

plt.scatter(omp_np_number, omp_times, s = 16)

plt.title("OMP graph")
plt.xlabel("Number of threads")
plt.ylabel("Execution time of parallel region, sec")
plt.xticks([1,2,3,4])
plt.savefig("OMP_exectime.jpg")

omp_acceleration = np.empty(4, dtype=np.double)

# omp_acceleration[0] = 1
# omp_acceleration[1] = omp_times[0]/omp_times[1]
# omp_acceleration[2] = omp_times[0]/omp_times[2]
# omp_acceleration[3] = omp_times[0]/omp_times[3]
# plt.scatter(omp_np_number, omp_acceleration, s = 16)
# plt.title("OMP acceleration")
# plt.savefig("OMP_acceleration.jpg")
