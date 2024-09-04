.PHONY: all clean

all: compila esegui

compila: main.cpp funzioni.cpp
	@${CXX} -o prog $^

esegui: compila	
	@./prog

clean:
	@rm -f prog