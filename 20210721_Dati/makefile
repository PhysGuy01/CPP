.PHONY: all compila esegui clean

all: compila esegui

compila: main.cpp funzioni.cpp
	@${CXX} -o prog $^

esegui: compila
	@./prog

clean:
	@rm -f prog