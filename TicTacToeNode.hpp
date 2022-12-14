#ifndef _TICTACTOENODE
#define _TICTACTOENODE

#include<string>
#include<iostream>
#include<vector>
#include<unordered_set>
#include<map>
#include<iterator>
#include <bitset>

#define TTT_BITSET_L 4

const int OTWICE_F = 0;
const int CYCLE_F = 1;



class TicTacToeNode {
public:
    TicTacToeNode(std::unordered_set<int> openStates, std::unordered_set<int> takenOStates, std::unordered_set<int> takenXStates, std::bitset<TTT_BITSET_L> Rrules) 
    {
        open = openStates;
        takenX = takenXStates;
        takenO = takenOStates;
        count = 1;
        //std::cout << rules << std::endl;
        rules = Rrules;
    }
    void printSetContents(std::unordered_set<int> const &temp);
    void computeNext();
    bool isXTurn();
    void printNumKnown();
    bool doesPlayerWin(bool isPlayerX);
    float getWinProbability(bool isPlayerX, bool XSmart, bool OSmart);
    void nicePrint();
    void game(TicTacToeNode* masterBoard, bool isUserX);
    std::vector<TicTacToeNode*>* getKnownStates();
    void reset();
    friend bool operator== (const TicTacToeNode& lhs, const TicTacToeNode& rhs);
   
private:
    std::unordered_set<int> open;
    std::unordered_set<int> takenX;
    std::unordered_set<int> takenO;
    std::vector<TicTacToeNode*> parents;
    std::vector<TicTacToeNode*> children;
    TicTacToeNode* findInKnown(TicTacToeNode* ttt);
    void addToKnown(TicTacToeNode* ttt);
    int count;
    std::bitset<TTT_BITSET_L> rules;
};

static std::vector<TicTacToeNode*> knownStates = {};
static std::unordered_set<TicTacToeNode*> leafNodes = {};
#endif