
.PHONY: all compila esegui clean

all: compila esegui

compila: funzioni.cpp main.cpp
	@${CXX} -o $^

esegui: compila
	@./prog

clean:
	@rm -f prog