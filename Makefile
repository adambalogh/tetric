main: main.cc board.cc board.h
	g++ -std=c++11 main.cc board.cc -o main -lncurses

figures.o: figures.h figures.cc
	g++ -std=c++11 figures.cc -c

clean:
	rm *.o main
