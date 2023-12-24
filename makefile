CC = g++


all: es5

es2: es2_lez7.cpp
	$(CC) -o $@ $<

es3: es3_lez7.cpp
	$(CC) -o $@ $<

es4: es4_lez7.cpp
	$(CC) -o $@ $<

es5: es5_lez7.cpp
	$(CC) -o $@ $<