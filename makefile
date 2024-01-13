CC = g++


<<<<<<< HEAD
all: struct_prodotto struct_vettore
=======
all: es5
>>>>>>> refs/remotes/origin/master

struct_prodotto: struct_prodotto.cpp
	$(CC) -o $@ $<

struct_vettore: struct_vettore.cpp
	$(CC) -o $@ $<

es3: es3_lez7.cpp
	$(CC) -o $@ $<

es4: es4_lez7.cpp
	$(CC) -o $@ $<

es5: es5_lez7.cpp
	$(CC) -o $@ $<