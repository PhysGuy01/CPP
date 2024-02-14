import numpy as np
import matplotlib.pyplot as mpl

# carica i dati su una lista data
data = np.loadtxt("datamasse.dat")

# traccia grafico
mpl.hist(data, bins = 30, range=(35, 100), label = "masse")

# cosmetics
mpl.title("Frequenza delle masse")
mpl.xlabel("Masse")
mpl.ylabel("Frequenza")
mpl.legend()

# disegna su un file
mpl.savefig("plot.png")

# disegna
mpl.show()