import numpy as np
import matplotlib.pyplot as plt

# load data
data = np.loadtxt("masses.dat")

# plot points
plt.hist(data, bins=30, range=(35, 100), label="masse")

# cosmetics
plt.title("Istogramma")
plt.xlabel("masse")
plt.ylabel("Frequenza")
plt.legend()

# save file to disk
plt.savefig("esercizio.png")

# show plot
plt.show()
