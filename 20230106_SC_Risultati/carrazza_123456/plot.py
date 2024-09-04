import numpy as np
import matplotlib.pyplot as plt

# load data
data = np.loadtxt("massainv.dat")

# plot points
eps = 1e-5
plt.hist(data, bins=30, range=(50.0111-eps, 199.779+eps), label="masse")

# cosmetics
plt.title("Istogramma")
plt.xlabel("masse invarianti")
plt.ylabel("Frequenza")
plt.legend()

# save file to disk
plt.savefig("esercizio.png")

# show plot
plt.show()
