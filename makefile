CC = g++


all: es2 es3 es4

es2: es2_lez7.cpp
	$(CC) -o $@ $<

es3: es3_lez7.cpp
	$(CC) -o $@ $<

es4: es4_lez7.cpp
	$(CC) -o $@ $<