CC = g++


all: struct_prodotto struct_vettore

struct_prodotto: struct_prodotto.cpp
	$(CC) -o $@ $<

struct_vettore: struct_vettore.cpp
	$(CC) -o $@ $<

es3: es3_lez7.cpp
	$(CC) -o $@ $<

es4: es4_lez7.cpp
	$(CC) -o $@ $<