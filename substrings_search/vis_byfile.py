import os
import matplotlib.pyplot as plt
from pylab import genfromtxt

directory_path = os.getcwd()

rk_path = os.path.join(directory_path, 'rabin_karp_filelen_10.txt')
bm_path = os.path.join(directory_path, 'boyer_moore_filelen_10.txt')

rk = genfromtxt(rk_path)
bm = genfromtxt(bm_path)


fig, ax1 = plt.subplots(figsize=(10,6))

plt.grid(color = 'grey', linestyle = '--', linewidth = 0.3)
plt.xlabel("File length", fontsize=12)
plt.ylabel("Time, miliseconds", fontsize=12)

fig.suptitle('For chinese text', fontsize = 16)


plt.plot(rk[:,0], rk[:,1], label = "Rabin Karp (blue)", linewidth=1, color = 'blue')
plt.plot(bm[:,0], bm[:,1], label = "Boyer Moore (orange)", linewidth=1, color = 'orange')
plt.legend()
plt.savefig("substring_search.png")
