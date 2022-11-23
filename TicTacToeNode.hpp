#ifndef _TICTACTOENODE
#define _TICTACTOENODE

#include<string>
#include<iostream>
#include<vector>

class TicTacToeNode {
public:
    TicTacToeNode(bool turn, char *arr[][3]) 
    {
        currentState = arr;
        currentTurn = turn;
        // _listOfNodes = new std::vector<TicTacToeNode *>;
    
        void printArr()
        {
            for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++)
                    std::cout << arr[i][j];
        }
    }

private:
    // std::vector<TicTacToeNode *> *_listOfNodes;
    float winProb;
    bool currentTurn;
    char **currentState;
};

#endif