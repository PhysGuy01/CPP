import numpy as np
import matplotlib.pyplot as mpl

# Carica i dati delle lunghezze
data = np.loadtxt("lenghts.dat")

# Traccia istogramma
mpl.hist(data, bins = 50, range = (0, 20), label = "lunghezze")

# Cosmetici
mpl.title("Distribuzione delle lunghezze di un arco di gluoni")
mpl.xlabel("Lunghezze")
mpl.ylabel("Frequenza")
mpl.legend()

# Salva un'immagine del grafico
mpl.savefig("plot.png")

mpl.show()