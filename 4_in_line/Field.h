#pragma once
#include <iostream>

const int FIELD_WIDTH = 7;
const int FIELD_HEIGHT = 6;
const int WIN_LENGTH = 4;

enum Cell {
    EMPTY = 0,
    RED = 1,
    YELLOW = 2
};

class Field {
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    bool isRedTurn;
    Cell winner;
    void checkWinner(int i, int j);

public:
    Field(bool isRedFirst);
    void clear(bool isRedFirst);
    bool makeTurn(int column);
    bool isWon(bool red) const;
    bool isOver() const;
    Cell getCell(int i, int j) const;
    bool isRedTurnNow() const;
    void print() const;
    void printResult() const;
};