ticTacToe.x: main.o TicTacToeNode.o
	g++ -std=c++17 main.o TicTacToeNode.o -o ticTacToe.x

main.o: main.cpp TicTacToeNode.hpp
	g++ -std=c++17 -c main.cpp -o main.o

TicTacToeNode.o: TicTacToeNode.hpp TicTacToeNode.cpp
	g++ -std=c++17 -c TicTacToeNode.cpp -o TicTacToeNode.o