.PHONY: all compila esegui clean

all: compila esegui

funzioni: funzioni.h funzioni.cpp
	@${CXX} -c funzioni.cpp

main: main.cpp
	@${CXX} -c $^

compila: funzioni.o main.o
	@${CXX} -o prog $^

esegui: compila
	@./prog

clean:
	@rm -f prog main.o funzioni.o