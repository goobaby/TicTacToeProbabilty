#include <iostream>
#include "TicTacToeNode.hpp"


int main()
{
    int n, m = 3;

    //Initialize 2D array of chars that we will be passing to constructed Nodes
    char *arr = new char[n * m];

    //Initialize char array to null spaces (-)
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            arr[i][j] = '-';

    //Create first node object before game has begun, X is first
    TicTacToeNode *ticTacToe = new TicTacToeNode(true, arr);

    ticTacToe->printArr();
}