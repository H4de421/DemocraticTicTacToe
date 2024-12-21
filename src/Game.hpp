#include "Board.hpp"
#include "AI/Automaton.hpp"

#include <memory>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>

class Game
{
private:
    bool playerTurn;
    int winner; // 0 => draw / 1=>player / -1=>IA
    Board *board;
    Automaton * automaton;
public:

    Game(Board *board);

    int getWinner();

    void startGame(void);

    void closeTurn(int playedPos);

    bool isGameOver(int gridPos);

    char getch(void);

    bool inputHandler(char input);

};