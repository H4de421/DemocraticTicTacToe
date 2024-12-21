#include "Game.hpp"

#include <chrono>
#include <thread>

int main(void)
{
    std::cout << "\e[1;1H\e[2j";
    Board* mainBoard = new Board();
    Game* game = new Game(mainBoard);
    game->startGame();
    mainBoard->finalCleanBoard();
    if (game->getWinner() == 1)
    {
        std::cout << "GG player won" <<std::endl;
    }
    else
    {
        std::cout << "nice try" <<std::endl;
    }
    
    mainBoard->finalCleanBoard();
    return 0;
}