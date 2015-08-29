main: main.cc board.cc board.h
	g++ -std=c++11 main.cc board.cc -o main -lncurses

clean:
	rm *.o main
