#include "Automaton.hpp"

Automaton::Automaton(Board *board){
    srand (time(NULL));
    this->board = board;
}

/*
function used to pick a random available position
*/
int Automaton::randomThought(std::vector<int> positions)
{
    return positions[rand() % positions.size() + 1];
}

/*
function used to pick the available position
*/
int Automaton::complexThougth()
{
    int best_id = 0;
    int best_score = -4242;

    std::vector<int> positions = this->board->getAvailablePosition();

    for(int i = 0; i<positions.size(); i++) {
        
        int pos = positions[i];
        Board *copyBoard = new Board(this->board);
        copyBoard->play(pos, false, false);

        int score = 0;
        ;
        if (copyBoard->getAvailablePosition().size() == 0 ||
            copyBoard->isGameOver(pos, false))

        {
            score += copyBoard->isGameOver(pos, false) * 10000;
        }
        else
        {
            score += this->minMax(copyBoard, true, 1);
        }

        if (score>best_score)
        {
            best_id = i;
            best_score = score;
        }
    }

    return positions[best_id];

}

/*
subfunction of [complexThougth]
simple implementation of MinMax algorithm
*/
int Automaton::minMax(Board *board, bool playerTurn, int depth)
{
    int total = 0; 

    std::vector<int> positions = board->getAvailablePosition();

    for(int i = 0; i<positions.size(); i++) {
        int pos = positions[i];
        Board *copyBoard = new Board(board);
        copyBoard->play(pos, playerTurn, false);

        if (copyBoard->getAvailablePosition().size() == 0 ||
            copyBoard->isGameOver(pos, playerTurn))

        {
            if (playerTurn)
            {
                total += depth - copyBoard->isGameOver(pos, true) * 10;
            }
            else
            {
                total += copyBoard->isGameOver(pos, false) * 10 - depth;
            }
        }
        else if (depth <= 6)
        {
            total += this->minMax(copyBoard, !playerTurn, depth+1);
        }
    }

    return total;
}
