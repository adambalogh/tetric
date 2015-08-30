main: main.cc board.o figures.o
	g++ -std=c++11 main.cc board.o figures.o -o main -lncurses

board.o: board.h board.cc
	g++ -std=c++11 board.cc -c

figures.o: figures.h figures.cc
	g++ -std=c++11 figures.cc -c

clean:
	rm *.o main
