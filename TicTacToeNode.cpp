#include "TicTacToeNode.hpp"
#include <unordered_set>
#include <stdlib.h>  //used for game
using namespace std;

//Use to print contents of vectors for debuggging purposes
void TicTacToeNode::printSetContents(unordered_set<int> const &temp)
{
    copy(temp.begin(), temp.end(), ostream_iterator<int>(cout, " "));
    cout<<"\n";
}

/*

*/
bool TicTacToeNode::isXTurn() {
    if(rules.test(OTWICE_F)){
        if(takenX.size() == 0){
            return true;
        }
        else if(takenX.size() == 1 && takenO.size() < 2){
            return false;
        }
        return takenO.size() != takenX.size();
    }
    return takenO.size() == takenX.size();
    
}

void TicTacToeNode::computeNext()
{
    bool XTurn = isXTurn();
    for (int next_move: open) { //Python equivalent: for next_move in open:
        //Copy of sets made here
        unordered_set<int> new_open = open;
        unordered_set<int> new_takenX = takenX;
        unordered_set<int> new_takenO = takenO;

        new_open.erase(next_move);

        if (XTurn){
            new_takenX.insert(next_move);
        }else{
            new_takenO.insert(next_move);
        }

        //Testing
        //cout<<"This is new_open:" << endl;
        //printSetContents(new_open);
        //cout<<"This is new_takenX:" << endl;
        //printSetContents(new_takenX);
        //cout<<"This is new_takenO:" << endl;
        //printSetContents(new_takenO);

        //Reference passed to sets so we don't copy an additional time
        TicTacToeNode * new_node = new TicTacToeNode(new_open,new_takenO,new_takenX,rules);

        
        auto previouslyFound = findInKnown(new_node);

        if(previouslyFound == nullptr){ //If it's nullptr, this is our first time getting herer
            addToKnown(new_node);
            leafNodes.insert(new_node);
            new_node->parents.push_back(this);
            children.push_back(new_node);

            //Our recursion step!
            if(new_open.size() > 0 && !new_node->doesPlayerWin(XTurn)){ //CHECKS TO SEE IF THERE'S A WINNER/CATTIE
                new_node->computeNext();
            }
        }else{
            children.push_back(previouslyFound); //Get the pointer from our previously found states
            
            previouslyFound->parents.push_back(this);
            previouslyFound->count += 1;
            delete new_node;
        }
    }
}

bool operator== (const TicTacToeNode& lhs, const TicTacToeNode& rhs) {
    return (lhs.open == rhs.open) && (lhs.takenX == rhs.takenX) && (lhs.takenO == rhs.takenO) && 
           (rhs.open == lhs.open) && (rhs.takenX == lhs.takenX) && (rhs.takenO == lhs.takenO);
}


TicTacToeNode* TicTacToeNode::findInKnown(TicTacToeNode* ttt) {
    for (int i = 0; i < knownStates.size(); i++){
        if (*ttt == *knownStates.at(i)) {
            return knownStates.at(i);
        }
    }
    return nullptr;
}

void TicTacToeNode::addToKnown(TicTacToeNode* ttt){
    knownStates.push_back(ttt);
}

void TicTacToeNode::printNumKnown(){
    cout << knownStates.size() << endl;
}

bool isSubset(unordered_set<int> a, unordered_set<int> b){
    for(int element: a){
        if(b.find(element) == b.end()){ //is the element not a member of b?
            return false;
        }
    }
    return true;
}

//Determine if current player's taken move sets are winning
bool TicTacToeNode::doesPlayerWin(bool isPlayerX){
    unordered_set<int>* playerToCheck;
    if(isPlayerX){
        playerToCheck = &takenX;
    }else{
        playerToCheck = &takenO;
    }
    return 
        //Horiztonal 
        isSubset(unordered_set<int>{0,1,2},*playerToCheck) ||
        isSubset(unordered_set<int>{3,4,5},*playerToCheck) ||
        isSubset(unordered_set<int>{6,7,8},*playerToCheck) ||

        //Vertical
        isSubset(unordered_set<int>{0,3,6},*playerToCheck) ||
        isSubset(unordered_set<int>{1,4,7},*playerToCheck) ||
        isSubset(unordered_set<int>{2,5,8},*playerToCheck) ||
        
        //Diagonal
        isSubset(unordered_set<int>{0,4,8},*playerToCheck) ||
        isSubset(unordered_set<int>{2,4,6},*playerToCheck)
    ;
}

//Don't work yet for cyclic stuff
void TicTacToeNode::calculateMinimaxProbability(std::unordered_set<TicTacToeNode*> layer){
    //cout << layer.size() << endl;
    std::unordered_set<TicTacToeNode*> nextLayer = {};
    for(TicTacToeNode* node : layer){
        if(node->children.size() == 0){
            node->minimaxProbability = (float)(node->doesPlayerWin(true) - node->doesPlayerWin(false));
        }else{
            float summ = 0.0;
            for(auto kids : node->children){
                summ += kids->minimaxProbability;
            }
            node->minimaxProbability = summ / node->children.size();
        }
        for(auto parent : node->parents){
            
            if(nextLayer.find(parent) == nextLayer.end()){
                nextLayer.insert(parent);
            }
        }
    }
    if(!nextLayer.empty()){
        calculateMinimaxProbability(nextLayer);
    }
}

//Fake, old, bad, cringe (only works for average values)
float TicTacToeNode::getWinProbability(bool isPlayerX, bool XSmart, bool OSmart){
    if(children.size() == 0){
        return (float)(doesPlayerWin(isPlayerX));
    }
    if ((isXTurn() && !XSmart) || (!isXTurn() && !OSmart)){
        float sum = 0.0;
        for(auto child : children) {
            sum += child->getWinProbability(isPlayerX,XSmart,OSmart);
        }
        return sum / children.size();
    }
    else{
        //If we're playing to minimize the win probability
        float multiplier = 1.0;
        if(!isXTurn())
            multiplier = -1.0;
        float max = -3.0;
        TicTacToeNode * t;
        for(auto child : children) {
            //could be wrong
            float prob = multiplier*child->minimaxProbability;
            if (prob > max) {
                max = prob;
                t = child;
            }
        }
        return t->getWinProbability(isPlayerX,XSmart,OSmart);
    }
}

void TicTacToeNode::nicePrint(){
    for(int i = 0; i < 9; i++){
        if(takenX.count(i) == 1){
            cout << "X";
        } else if (takenO.count(i) == 1){
            cout << "O";
        }else{
            cout << i;
        }
        if(i % 3 != 2){
            cout << "|";
        }else{
            cout << endl;
        }
    }
}


/*
float TicTacToeNode::getOptimalProbability(){
    if(children.size() == 0){
        return (float)(doesPlayerWin(true) - doesPlayerWin(false));
    }
    float sum = 0.0;
    float max = -2.0;
    TicTacToeNode *bestKid;
    for(auto child : children) {
        float prob = child->getWinProbability(true);
        if (prob > max) {
            max = prob;
            bestKid = child;
        }
    }

    return sum / children.size();
}
*/

void TicTacToeNode::game(TicTacToeNode * masterBoard){

    int playerChoice = 0;
    while(true){
        open = {0,1,2,3,4,5,6,7,8};
        takenX = {};
        takenO = {};
        while(!open.empty() && !doesPlayerWin(true) && !doesPlayerWin(false)){
            nicePrint();
            cout << endl;
            if(isXTurn()){
                cin >> playerChoice;
                open.erase(playerChoice);
                takenX.insert(playerChoice);
                if(open.empty()){
                    break;
                }
            }else{
                auto curBoard = masterBoard->findInKnown(this);
                float min = 2.0;
                vector<TicTacToeNode*> bestKids;
                if(curBoard == nullptr){
                    cout << "why" << endl;
                }
                for(auto child : curBoard->children) {
                    float prob = child->getWinProbability(true,true,true);
                    if (prob < min) {
                        min = prob;
                        bestKids = {child};
                    } else if (prob == min){
                        bestKids.push_back(child);
                    }
                }
                auto bestKid = bestKids[rand() % bestKids.size()];
                int moveChoice = 0;
                for(int i = 0; i < 9; i++){
                    if(takenO.count(i) == 0 && bestKid->takenO.count(i) == 1){
                        moveChoice = i;
                        cout << "found move at " << moveChoice << endl;
                        break;
                    }
                }
                open.erase(moveChoice);
                takenO.insert(moveChoice);
                cout << "loop end" << endl;
            }


            //cout << "Thinking..." << endl;
        }
        if(doesPlayerWin(true)){
            cout << "Player X wins! (how???)" << endl << endl;
        }else if(doesPlayerWin(false)){
            cout << "Player O wins!" << endl << endl;
        }else{
            cout << "Tie." << endl << endl;
        }
    }
}
std::unordered_set<TicTacToeNode*> TicTacToeNode::getLeafNodes(){
    return leafNodes;
}