import numpy as np
import matplotlib.pyplot as mpl

# Carica i dati dei diametri
data = np.loadtxt("diametri.dat")

# Calcola l'istogramma
mpl.hist(data, bins = 20, range = (data.min() - 0.5, data.max() + 0.5), label = "diametri")

# Cosmetics
mpl.title("Frequenza dei diametri")
mpl.xlabel("Diametri")
mpl.ylabel("Frequenze")
mpl.legend()

# Salva su una immagine .png
mpl.savefig("plot.png")

mpl.show()