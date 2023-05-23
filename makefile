simulator:main.o Functions.o
	g++ main.o Functions.o -o simulator
main.o:main.cpp Functions.h
	g++ -c main.cpp -o main.o
Functions.o:Functions.cpp Functions.h
	g++ -c Functions.cpp -o Functions.o