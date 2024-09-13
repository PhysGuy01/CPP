.PHONY: all esegui compila clean

MAKEFLAGS += --silent

all: compila esegui

funzioni.o: funzioni.cpp funzioni.h
	${CXX} -c $< -o $@

main.o: main.cpp
	${CXX} -c $< -o $@

compila: main.o funzioni.o
	${CXX} -o prog $^

esegui: 
	./prog

clean: 
	rm -f main.o funzioni.o prog