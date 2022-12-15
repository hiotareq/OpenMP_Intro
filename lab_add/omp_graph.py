import matplotlib.pyplot as plt
import numpy as np

omp_np_number = np.empty(28, dtype=np.double)
omp_times = np.empty(28, dtype=np.double)

for i in range(28):
    omp_np_number[i] = i + 1

omp_times[0] = 0.1242
omp_times[1] = 0.0649023
omp_times[2] = 0.0436185
omp_times[3] = 0.0344022
omp_times[4] = 0.054352
omp_times[5] = 0.0388438
omp_times[6] = 0.037506
omp_times[7] = 0.0280838
omp_times[8] = 0.0242088
omp_times[9] = 0.0207369
omp_times[10] = 0.0173061
omp_times[11] = 0.0272383
omp_times[12] = 0.0243707
omp_times[13] = 0.0208898
omp_times[14] = 0.0185204
omp_times[15] = 0.0116659
omp_times[16] = 0.0076482
omp_times[17] = 0.00749645
omp_times[18] = 0.00640535
omp_times[19] = 0.0153824
omp_times[20] = 0.00758607
omp_times[21] = 0.00556687
omp_times[22] = 0.00552517
omp_times[23] = 0.0051406
omp_times[24] = 0.00665866
omp_times[25] = 0.00501119
omp_times[26] = 0.00975483
omp_times[27] = 0.00441673

# plt.scatter(omp_np_number, omp_times, s = 16)

# plt.title("OMP graph")
# plt.xlabel("Number of threads")
# plt.ylabel("Execution time of parallel region, sec")
# plt.xticks(np.arange(1,28, step = 1))
# plt.savefig("OMP_exectime.jpg")

omp_acceleration = np.empty(28, dtype=np.double)
for i in range(28):
    omp_acceleration[i] = omp_times[0]/ omp_times[i]

plt.scatter(omp_np_number, omp_acceleration, s = 16)
plt.title("OMP acceleration")
plt.savefig("OMP_acceleration.jpg")
