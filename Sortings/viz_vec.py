import os
import matplotlib.pyplot as plt
from pylab import genfromtxt

directory_path = os.getcwd()

shell_path = os.path.join(directory_path, 'Shell_out_vec.csv')
heap_path = os.path.join(directory_path, 'Heap_out_vec.csv')

shell = genfromtxt(shell_path)
heap = genfromtxt(heap_path)


fig, ax1 = plt.subplots(figsize=(10,6))
#ax1.grid(True)
plt.grid(color = 'grey', linestyle = '', linewidth = 0.3)
plt.xlabel("Array size", fontsize=12)
plt.ylabel("Time, microseconds", fontsize=12)
#fig.suptitle('For reversed array', fontsize = 16)
#fig.suptitle('Clang compiler', fontsize = 16)

plt.plot(shell[:,0], shell[:,1], label = "Shell Sort (blue)", linewidth=1, color = 'blue')
plt.plot(heap[:,0], heap[:,1], label = "Heap Sort (orange)", linewidth=1, color = 'orange')
plt.legend()
plt.savefig("sortings_vec.png")