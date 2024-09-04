import numpy as np
import matplotlib.pyplot as mpl

# Carica i dati delle ascisse su ascisse
ascisse = np.loadtxt("ascisse.dat")

# Crea un istogramma dai dati
mpl.hist(ascisse, range = (ascisse.min() - 10, ascisse.max() + 10), bins = 10, label = "Ascisse dei batteri")


# Cosmetics
mpl.title("Frequenza delle ascisse dei batteri")
mpl.xlabel("Posizione dei batteri sulle ascisse")
mpl.ylabel("Frequenza")
mpl.legend()

# Salva su una png
mpl.savefig("plot.png")

# Disegna
mpl.show()