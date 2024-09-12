.PHONY: all compila esegui clean

MAKEFLAGS += --silent

all: compila esegui

funzioni.o: funzioni.cpp funzioni.h
	${CXX} -c $< -o $@

main.o: main.cpp
	${CXX} -c $< -o $@

compila: main.o funzioni.o
	${CXX} -o prog $^

esegui: compila
	./prog

clean: 
	rm -f prog funzioni.o main.o