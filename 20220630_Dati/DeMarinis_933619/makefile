main.x: main.o lib.o
	g++ -o main.x main.o lib.o

main.o: main.cpp lib.h
	g++ -c main.cpp

lib.o: lib.cpp lib.h

compila: main.x

esegui:
	./main.x

clean:
	rm *.o
