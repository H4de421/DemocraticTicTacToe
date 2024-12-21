#pragma once

#include <vector>
#include <iostream>

#define PIN_LIFETIME 6

class Board
{
private:
    int cursorPos;
    int lastPlayed;
    std::vector<int> grid;
public:
    /*
    constructors
    */
    Board();
    Board(Board *board);

    /* == setter/getter == */
    int getCursorPos();
    void setCursorPos(int newValue);

    /*
    print the canvas
    */
    void printCanevas();

    /*
    print an tile depending of his lifetime and color 
    */
    void printTile(int gridPos);

    /*
    Erase current cursor + find the net available position (current eclue)
    */
    void clearCursor();

    /*
    getAvailablePosition: return all "free" position in an int vector
    */
    std::vector<int> getAvailablePosition();

    /*
    play: put a pin at the [gridPos] postion in the grid
           return false if [gridPos] is not free
           return true otherwsie
    */
    bool play(int gridPos, bool isPlayer, bool diplay);

    /*
    nextTurn: update all pin in the board, decreaseing their lifetime by 1
    */
    void nextTurn();

    void finalCleanBoard();

    void cursorRight();
    void cursorLeft();
    void cursorUp();
    void cursorDown();
    void printCursor();

    int getTeamOf(int gridPos);
    
    bool isGameOver(int gridPos, bool playerTurn);

    
    void DEBUG_printgrid();
};
