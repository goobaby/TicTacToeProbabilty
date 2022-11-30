#include "TicTacToeNode.hpp"

//Use to print contents of vectors for debuggging purposes
void TicTacToeNode::printSetContents(std::unordered_set<int> const &temp)
{
    std::copy(temp.begin(), temp.end(), std::ostreambuf_iterator<int>(std::cout, " "));
}

void TicTacToeNode::computeNext()
{
    bool XTurn = takenO.size() == takenX.size();
    for (int& next_move: open) { //Python equivalent: for next_move in open:
        //Copy of sets made here
        std::unordered_set<int> new_open = open;
        std::unordered_set<int> new_takenX = takenX;
        std::unordered_set<int> new_takenO = takenO;
        new_open.erase(next_move);

        if (XTurn){
            new_takenX.insert(next_move);
        }else{
            new_takenO.insert(next_move);
        }
        //Reference passed to sets so we don't copy an additional time
        TicTacToeNode * new_node = new TicTacToeNode(&new_open,&new_takenX,&new_takenO);

        
        auto previouslyFound = knownStates.find(new_node);

        if(previouslyFound == knownStates.end()){//If it's a new state
            knownStates.insert(new_node, new_node);
            new_node->parents.push_back(this);
            children.push_back(new_node);

            //Our recursion step!
            new_node->computeNext();
        }else{
            children.push_back(previouslyFound->second); //Get the pointer from our previously found states
            previouslyFound->second->parents.push_back(this);
        }
    }
}