all: main

main: main.o
	g++ -std=c++11 main.o -o main

main.o: main.cpp AnalizadorLexico.h
	g++ -std=c++11 -c -Wall main.cpp

clean:
	rm -rf *o main
