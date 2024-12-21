#include "../Board.hpp"

#include <stdlib.h> 

#define AI_DEEP 6

class Automaton
{
private:
public:
    Board *board;

    Automaton(Board *board);

    int randomThought(std::vector<int> positions);

    int complexThougth();

    int minMax(Board *board, bool playerTurn, int depth);

};