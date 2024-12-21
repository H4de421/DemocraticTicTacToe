#include "Game.hpp"

/* constructor */
Game::Game(Board *board)
{
    this->board = board;
    this->automaton = new Automaton(board);
    this->playerTurn = true;
}


int Game::getWinner()
{
    return this->winner;
}

/*
function used to launch a game
*/
void Game::startGame(void) 
{
    bool quit = false;
    int lastPlayed;
    
    this->board->printCanevas();
    this->board->printCursor();
    this->winner = 0; // 0 => drow / 1=>player / -1=>IA
    while(this->winner==0 )
    {
        if (playerTurn)
        {
            char input = getch();
            quit = inputHandler(input);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(750));

            int gridId = this->automaton->complexThougth();
            this->board->play(gridId, false, true);
            this->closeTurn(gridId);

            this->board->setCursorPos(this->board->getAvailablePosition()[0]);
            this->board->printCursor();
        }
    }
}

/*
function called after the player or the Automaton played
*/
void Game::closeTurn(int playedPos)
{
    int isWon =  this->board->isGameOver(playedPos, this->playerTurn);
    this->winner = isWon * (this->playerTurn?1:-1);
    this->playerTurn = !this->playerTurn;
    this->board->nextTurn();    
}

/*
function used to catch keyboard input
*/
char Game::getch (void)
{

    fflush(stdout);
    struct termios row;
    tcgetattr(STDIN_FILENO, &row);
    struct termios aa = row;
    aa.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, & aa);

    char ch;
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, & row);
    return ch;
}

/*
function used to process input
*/
bool Game::inputHandler(char input)
{
    switch (input)
    {
    case 'd':
        this->board->cursorRight();
        break;
    case 'a':
    case 'q':
        this->board->cursorLeft();
        break;
    case 'w':
    case 'z':
        this->board->cursorUp();
        break;
    case 's':
        this->board->cursorDown();
        break;
    case 'e':
        if (this->playerTurn)
        {
            this->board->play(this->board->getCursorPos(), true, true);
            this->closeTurn(this->board->getCursorPos());
        }
        break;
    case 'p':
        return true;
    default:
        break;
    }
    return false;
}
