#ifndef _TICTACTOENODE
#define _TICTACTOENODE

#include<string>
#include<iostream>
#include<vector>
#include<unordered_set>
#include<map>

static std::map<TicTacToeNode,TicTacToeNode*> knownStates;

class TicTacToeNode {
public:
    TicTacToeNode(std::unordered_set<int> *openStates, std::unordered_set<int> *takenOStates, std::unordered_set<int> *takenXStates) 
    {
        open = openStates;
        takenX = takenXStates;
        takenO = takenOStates;
    }
    void printSetContents(std::unordered_set<int> const &temp);
    void computeNext();
    bool operator< (const TicTacToeNode& lhs, const TicTacToeNode& rhs) const
   {
       //THIS IS ONLY FOR C++'S MAP. IT IS CURSED AND SO IS THE LANGUAGE
       return !(lhs.open == rhs.open && lhs.takenX == rhs.takenX && lhs.takenO == lhs.takenO);
   }
   
private:
    std::unordered_set<int> open;
    std::unordered_set<int> takenX;
    std::unordered_set<int> takenO;
    std::vector<TicTacToeNode*> parents;
    std::vector<TicTacToeNode*> children;
    float probabilityVal;

};

#endif