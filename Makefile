main: main.cc board.o figures.o
	g++ -std=c++14 main.cc board.o figures.o -o main -lncurses

board.o: board.h board.cc
	g++ -std=c++14 board.cc -c

figures.o: figures.h figures.cc
	g++ -std=c++14 figures.cc -c

figures_test: figures_test.cc figures.o
	g++ -std=c++14 -I /usr/local/gtest/include figures_test.cc figures.o -o figures_test -lgtest -lgtest_main

clean:
	rm *.o main
