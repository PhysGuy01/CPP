.PHONY: all esegui compila clean

MAKEFLAGS += --silent

all: compila esegui

funzioni: funzioni.h funzioni.cpp
	${CXX} -o funzioni.cpp

main: main.cpp
	${CXX} -o $^

compila: main.o funzioni.o
	${CXX} -o prog $^

esegui: compila
	./prog

clean:
	rm -f prog main.o funzioni.o