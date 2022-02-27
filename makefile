caso1: main.o
	g++ main.o -o caso1.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o