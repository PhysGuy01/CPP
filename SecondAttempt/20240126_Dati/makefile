.PHONY: all esegui compila clean

MAKEFLAGS += --silent

all: compila esegui

funzioni: funzioni.cpp funzioni.h
	${CXX} -o funzioni.cpp

main: main.cpp
	${CXX} -o $^

compila: main.o funzioni.o
	${CXX} -o prog $^

esegui: compila
	./prog

clean: 
	rm -f main.o funzioni.o prog