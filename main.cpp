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
    //cout << 1.0 - (firstBaby.getWinProbability(true) + firstBaby.getWinProbability(false)) << endl;
}

void game(){
    int games = 0;
    bool isUserX;
    bool isOrderOdd;
    bool shouldRulesChange = true;
    TicTacToeNode* firstBaby;
    string in;
    while (true){
        if(games > 0){
            getline(cin,in);
            cout << "Would you like to play again? (y/n): ";
            getline(cin, in);
            if(in[0] != 'y'){
                return;
            }
            cout << "Do you want to change the rules? (y/n): ";
            getline(cin, in);
            shouldRulesChange = in[0] == 'y';
        }
        if(shouldRulesChange){
            cout << "Would you like to be X? (y/n): ";
            getline(cin, in);
            isUserX = in[0] == 'y';


            cout << "Would you like to play with the modified play order? (y/n): ";
            getline(cin, in);
            isOrderOdd = in[0] == 'y';
        }
        

        auto rules = std::bitset<TTT_BITSET_L>();

        rules.set(OTWICE_F,isOrderOdd);

        std::unordered_set<int> openStates = {0,1,2,3,4,5,6,7,8};
        std::unordered_set<int> takenXStates = {};
        std::unordered_set<int> takenOStates = {};
        if(shouldRulesChange){
            cout << "Calculating options..." << endl;
            *firstBaby->getKnownStates() = {};
            firstBaby = new TicTacToeNode(openStates,takenXStates,takenOStates, rules);
            firstBaby->getKnownStates()->push_back(firstBaby);
            firstBaby->computeNext();
        }
        auto gameBoard = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
        gameBoard.game(firstBaby, isUserX);
        games++;
    }
        
}


int main()
{
    string in;
    cout << "Would you like to play against the AI? This otherwise prints out the W/L probabilities (y/n): ";
    getline(cin, in);
    if(in[0] == 'y'){
        game();
        return 0;
    }
    auto rules = bitset<TTT_BITSET_L>();
    unordered_set<int> openStates = {0,1,2,3,4,5,6,7,8};
    unordered_set<int> takenXStates = {};
    unordered_set<int> takenOStates = {};


    cout << "-----------Normal Tic-Tac-Toe----------" << endl;
    auto firstBaby = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
    firstBaby.getKnownStates()->push_back(&firstBaby);
    firstBaby.computeNext();
    printSmartness(&firstBaby);

    firstBaby.reset();

    cout << "-----------Modified Tic-Tac-Toe--------" << endl;
    rules.set(OTWICE_F);
    firstBaby = TicTacToeNode(openStates,takenXStates,takenOStates, rules);
    knownStates = {};
    knownStates.push_back(&firstBaby);
    firstBaby.computeNext();

    printSmartness(&firstBaby);

}


