import os
import matplotlib.pyplot as plt
from pylab import genfromtxt

directory_path = os.getcwd()

quick_path = os.path.join(directory_path, 'quick_out.csv')
merge_path = os.path.join(directory_path, 'merge_out.csv')

quick = genfromtxt(quick_path)
merge = genfromtxt(merge_path)


fig, ax1 = plt.subplots(figsize=(10,6))
#ax1.grid(True)
plt.grid(color = 'grey', linestyle = '--', linewidth = 0.3)
plt.xlabel("Bubble sort walks", fontsize=12)
plt.ylabel("Time, microseconds", fontsize=12)
#fig.suptitle('For reversed array', fontsize = 16)
#fig.suptitle('Clang compiler', fontsize = 16)
#ax1.set_yscale('log')
plt.plot(quick[:,0]-9999, quick[:,1], label = "Quick Sort, pivot - middle (blue)", linewidth=0.1, color = 'blue')
plt.plot(merge[:,0]-9999, merge[:,1], label = "Merge Sort (orange)", linewidth=0.1, color = 'orange')
plt.legend()
plt.savefig("sortings.png")