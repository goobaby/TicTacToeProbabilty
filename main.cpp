#include <iostream>
#include "TicTacToeNode.hpp"
using namespace std;
void printSmartness(TicTacToeNode* ttt){
    float xWin = ttt->getWinProbability(true,false,false);
    float oWin = ttt->getWinProbability(false,false,false);
    cout << "Odds of Player X winning: " << xWin << endl; 
    cout << "Odds of Player O winning: " << oWin << endl; 
    cout << "Odds of draw: " << 1.0 - xWin - oWin << endl;
    float xXSmartWin = ttt->getWinProbability(true,true,false);
    float oXSmartWin = ttt->getWinProbability(false,true,false);
    cout << "Odds of Player X winning (Smart X): " << xXSmartWin << endl;
    cout << "Odds of Player O winning (Smart X): " << oXSmartWin << endl;
    cout << "Odds of draw with Player X being smart: " << 1.0 - xXSmartWin - oXSmartWin << endl;
    float xOSmartWin = ttt->getWinProbability(true,false,true);
    float oOSmartWin = ttt->getWinProbability(false,false,true);
    cout << "Odds of Player X winning (Smart O): " << xOSmartWin << endl;
    cout << "Odds of Player O winning (Smart O): " << oOSmartWin << endl;
    cout << "Odds of draw with Player O being smart: " << 1.0 - xOSmartWin - oOSmartWin << endl;
    float xOXSmartWin = ttt->getWinProbability(true,true,true);
    float oOXSmartWin = ttt->getWinProbability(false,true,true);
    cout << "Odds of Player X winning (Smart X and Smart O): " << xOXSmartWin << endl;
    cout << "Odds of Player O winning (Smart X and Smart O): " << oOXSmartWin << endl;
    cout << "Odds of draw with with both players being smart: " << 1.0 - xOXSmartWin - oOXSmartWin << endl;
    cout << "-------------------------------------------------------------" << endl;   
    //cout << 1.0 - (firstBaby.getWinProbability(true) + firstBaby.getWinProbability(false)) << endl;
}

int main()
{
    auto rules = bitset<TTT_BITSET_L>();
    unordered_set<int> openStates = {0,1,2,3,4,5,6,7,8};
    unordered_set<int> takenXStates = {};
    unordered_set<int> takenOStates = {};


    cout << "-----------Normal Tic-Tac-Toe (X player goes first)----------" << endl;
    auto firstBaby = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
    knownStates.push_back(&firstBaby);
    firstBaby.computeNext();
    firstBaby.calculateMinimaxProbability(firstBaby.getLeafNodes());

    printSmartness(&firstBaby);

    cout << "-----------Unnormal Tic-Tac-Toe (X player goes first and O player goes twice then its normal)----------" << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl; 
    rules.set(OTWICE_F);
    firstBaby = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
    knownStates = {};
    leafNodes = {};
    knownStates.push_back(&firstBaby);
    firstBaby.computeNext();
    firstBaby.calculateMinimaxProbability(firstBaby.getLeafNodes());
    printSmartness(&firstBaby);
    
    auto gameBoard = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
    gameBoard.game(&firstBaby);

}

void game(){
    auto rules = std::bitset<TTT_BITSET_L>();
    std::unordered_set<int> openStates = {0,1,2,3,4,5,6,7,8};
    std::unordered_set<int> takenXStates = {};
    std::unordered_set<int> takenOStates = {};

    auto firstBaby = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
    knownStates.push_back(&firstBaby);
    firstBaby.computeNext();

    auto gameBoard = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
    gameBoard.game(&firstBaby);
}