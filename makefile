
all: none far-cel

#compulare files
none: none.cpp
	g++ -o none none.cpp

far-cel: far-cel.cpp
	g++ -o far-cel far-cel.cpp

exnone: none
	./none

exfar-cel: far-cel
	./far-cel
