#!/bin/python3

import numpy  as np
import matplotlib.pyplot as plt

def my_print(filename):
    data = np.loadtxt(filename)
    x = data[:, 0]
    y = data[:, 1]
    line = plt.plot(x, y)

    plt.ylim(bottom=0)
    plt.setp(line, linewidth=1)
    return

for i in range(0, 11):
   filename = "file" + str(i) + ".dat"
   my_print(filename)

plt.show()