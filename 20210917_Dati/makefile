.PHONY: all clean

all: compila esegui

compila: funzioni.cpp main.cpp
	@${CXX} -o prog $^

esegui: compila
	@./prog

clean:
	@rm -f prog