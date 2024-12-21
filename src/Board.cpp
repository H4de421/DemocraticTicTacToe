#include "Board.hpp"
#include <stdlib.h>

/* constructors */
Board::Board(){
    
    this->cursorPos = 0;
    this->lastPlayed = 0;
    this->grid = {0,0,0,0,0,0,0,0,0,0};
}
Board::Board(Board *board)
{
    this->cursorPos = board->cursorPos;
    this->lastPlayed = board->lastPlayed;
    this->grid = board->grid;
}

/* == setter/getter == */
int Board::getCursorPos() {
    return this->cursorPos;
}
void Board::setCursorPos(int newValue) {
    this->cursorPos = newValue;
}

/*
print the board EMPTY
*/
void Board::printCanevas() {
    /*
        canvas information :
            Board start at (6,9)
            tile 1 start at (7,10);


    */
    char canevas[] = "\r\
                                                ╭═══════╮\n\
                   ┌────────────────────────────║       ║────────────────────────────┐\n\
  \e[0;33m╔═════════════════\e[0m╲___________________________║ ▄   ▄ ║___________________________╱\e[0;33m════════════════╗\n\
  \e[0;33m║                     \e[0m╲_______________________╰─╮ ▴ ╭─╯_______________________╱                    \e[0;33m║\n\
  \e[0;33m║                               \e[0m╲______ ╲_______╰─═─╯_____╱ ______╱                                \e[0;33m║\n\
  \e[0;33m║      ╔═══════╦═══════╦═══════╗      ║                                                            ║\n\
  \e[0;33m║      ║       ║       ║       ║      ║                                                            ║\n\
  \e[0;33m║      ║       ║       ║       ║      ║                                                            ║\n\
  \e[0;33m║      ╠═══════╬═══════╬═══════╣      ║                                                            ║\n\
  \e[0;33m║      ║       ║       ║       ║      ║                                                            ║\n\
  \e[0;33m║      ║       ║       ║       ║      ║                                                            ║\n\
  \e[0;33m║      ╠═══════╬═══════╬═══════╣      ║                                                            ║\n\
  \e[0;33m║      ║       ║       ║       ║      ║                                                            ║\n\
  \e[0;33m║      ║       ║       ║       ║      ║                                                            ║\n\
  \e[0;33m║      ╚═══════╩═══════╩═══════╝      ║                                                            ║\n\
  \e[0;33m║                                     ║                                                            ║\n\
  \e[0;33m║                                     ║                                                            ║\n\
  \e[0;33m╚═════════════════════════════════╦═══╩════════════════════════════╦═══════════════════════════════╝\e[0;0m\n\
  \e[0;33m                                  ║      \e[0mshow stratagèmes : P\e[0;33m      ║\e[0;0m\n\
  \e[0;33m                                  ╚════════════════════════════════╝\e[0;0m\e[23A\n";
    std::cout << canevas;
}

/*
return all "free" position in an int vector
*/
std::vector<int> Board::getAvailablePosition(){
    std::vector<int> res = {};
    for (int pos = 0; pos <9 ; pos++)
    {
        if (this->grid[pos] == 0)
        {
            res.push_back(pos);
        }
    }
    return res;
}

/*
print an tile depending of his lifetime and color 
*/
void Board::printTile(int gridPos)
{
    if (gridPos < 0 || 
        gridPos > 8)
    {
        return ;
    }
    int shiftx =  11 + (gridPos%3) * 8;
    int shifty =  5 + (gridPos/3) * 3;
    std::cout << "\e[" << shiftx << "C\e[" << shifty << "B";
    fflush(stdout);

    bool isPlayer = this->grid[gridPos] > 0;
    int absoluteValue =this->grid[gridPos] * (isPlayer?1:-1);

    std::string color = (isPlayer?"\e[0;34m":"\e[0;31m");
    std::string sigil = "     ";
    if (absoluteValue != 0)
    {
        sigil = (absoluteValue==1?"░░░░░":"█████");
    }
    std::cout << color << sigil <<"\e[1B\e[5D" << sigil << "\e[0m";
    std::cout << "\r\e[" << (shifty + 1) << "A" ;
    fflush(stdout);
}

/*
put a pin at the [gridPos] postion in the grid
    return false if [gridPos] is not free
    return true otherwsie
*/
bool Board::play(int gridPos, bool isPlayer, bool diplay){
    if (gridPos < 0 || 
        gridPos > 8 ||
        this->grid[gridPos] != 0)
    {
        return false;
    }
    this->grid[gridPos] =  PIN_LIFETIME * (isPlayer?1:-1);
    if (diplay)
    {
        printTile(gridPos);
    }
    this->lastPlayed = gridPos;
    return true;
}

/*
nextTurn: update all pin in the board, decreaseing their lifetime by 1
*/
void Board::nextTurn(){
    for (size_t i = 0; i < 9; i++)
    {
        bool isPlayer = this->grid[i] > 0;
        if (this->grid[i] != 0)
        {
            this->grid[i] -= 1 * (isPlayer?1:-1);
            if (this->grid[i] == (isPlayer?1:-1))
            {
                printTile(i);
            }
            if (this->grid[i] == 0)
            {
                printTile(i);
            }
        }
    }
}

/*
reset cursor to 0:0 (upepr right of the screen)
*/
void Board::finalCleanBoard() {
    std::cout << "\e[22B" <<"\e[1;1H\e[2j";
}

/*
print cursor depending of his current pos
*/
void Board::printCursor()
{
    int shiftx =  12 + (this->cursorPos%3) * 8;
    int shifty =  5 + (this->cursorPos/3) * 3;
    std::cout << "\e[" << shiftx << "C\e[" << shifty << "B";
    fflush(stdout);
    std::cout << "╭─╮" <<"\e[1B\e[3D" << "╰─╯" << "\e[0m";
    std::cout << "\r\e[" << (shifty + 1) << "A" ;
}

/*
moveCursor to the next right available spot 
*/
void Board::cursorRight()
{
    bool changed = false;
    if (this->cursorPos%3 < 2)
    {
        int rightShift = 2 - (this->cursorPos % 3);
        int virtualPos = this->cursorPos;
        while(rightShift > 0)
        {
            virtualPos += 1;
            if (this->grid[virtualPos] == 0)
            {
                changed = true;
                break;
            }
            rightShift--;
        }
        if (changed)
        {
            printTile(this->cursorPos);
            this->cursorPos = virtualPos;   
            printCursor();
        }
    }

}

/*
moveCursor to the next left available spot 
*/
void Board::cursorLeft()
{
    
    bool changed = false;
    if (this->cursorPos%3 > 0)
    {
        int leftShift = (this->cursorPos % 3);
        int virtualPos = this->cursorPos;
        while(leftShift > 0)
        {
            virtualPos -= 1;
            if (this->grid[virtualPos]==0)
            {
                changed = true;
                break;
            }
            
            leftShift--;
        }
        if (changed)
        {
            printTile(this->cursorPos);
            this->cursorPos = virtualPos;   
            printCursor();
        }
    }
}

/*
moveCursor to the next up available spot 
*/
void Board::cursorUp()
{
    bool changed = false;
    if (this->cursorPos/3 > 0)
    {
        int UpShift = (this->cursorPos / 3);
        int virtualPos = this->cursorPos;
        while(UpShift > 0)
        {
            
            virtualPos -= 3;
            if (this->grid[virtualPos]==0)
            {
                changed = true;
                break;
            }
            UpShift--;
        }
        if (changed)
        {
            printTile(this->cursorPos);
            this->cursorPos = virtualPos;   
            printCursor();
        }
    }
}

/*
moveCursor to the next down available spot 
*/
void Board::cursorDown()
{
    
    bool changed = false;
    if (this->cursorPos/3 < 2)
    {
        int DonShift = 2 - (this->cursorPos/3);
        int virtualPos = this->cursorPos;
        while(DonShift > 0)
        {
            virtualPos += 3;
            if (this->grid[virtualPos]==0)
            {
                changed = true;
                break;
            }
            DonShift--;
        }
        if (changed)
        {
            printTile(this->cursorPos);
            this->cursorPos = virtualPos;   
            printCursor();
        }
    }
}

/*
return an int refering to the team of the pin
1 for player, -1 for Automaton, 0 if empty
*/
int Board::getTeamOf(int gridPos)
{
    int res = (this->grid[gridPos]==0 ? 0 : 1);
    return res * (this->grid[gridPos] > 0 ? 1 : -1);
}

/*
return true if the player chose won
*/
bool Board::isGameOver(int gridPos, bool isPlayer)
{
    int col = gridPos%3;
    int row = gridPos/3;
    //std::cout << "col = " << col << " and row = " << row;
    int possibleScore[4] = {0,0,0,0}; 

    // column
    possibleScore[0] = this->getTeamOf(col) +
                        this->getTeamOf(col+3) +
                        this->getTeamOf(col+6);
    // row
    possibleScore[1] = this->getTeamOf((row)*3) +
                        this->getTeamOf((row)*3+1) +
                        this->getTeamOf((row)*3+2);
    // diag1
    possibleScore[2] = this->getTeamOf(0) + 
                        this->getTeamOf(4) + 
                        this->getTeamOf(8);
    // diag2
    possibleScore[3] = this->getTeamOf(2) + 
                        this->getTeamOf(4) + 
                        this->getTeamOf(6);

    for(int i = 0; i<4 ; i++) {
        int score = possibleScore[i];
        //std::cout << " " << score << " |";
        int absScore = score * (score>0? 1 : -1);
        if (absScore == 3)
        {
            //std::cout << "     id = "<< i <<"           score  = " << score << std::endl;
            return isPlayer && score > 0 || !isPlayer && score < 0;
        }
    }
    return false;
}

/*
-> for debug purpose
print an simple version of the grid, 
used to see inner value of the grid
*/
void Board::DEBUG_printgrid()
{
    for(int i = 0 ; i< 9; i++)
    {
        std::cout << this->grid[i] << (i%3!=2?" | ":"\e[9D\e[1B");
    }
}