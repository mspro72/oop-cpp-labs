#include "field.h"
using namespace std;

Field::Field(bool isRedFirst) {
    clear(isRedFirst);
}

void Field::clear(bool isRedFirst) {
    isRedTurn = isRedFirst;
    winner = EMPTY;
    for (int i = 0; i < FIELD_WIDTH; i++) {
        for (int j = 0; j < FIELD_HEIGHT; j++) {
            cells[i][j] = EMPTY;
        }
    }
}

bool Field::makeTurn(int column) {
    if (column < 1 || column > FIELD_WIDTH || isOver()) {
        return false;
    }

    int i = column - 1;
    for (int j = 0; j < FIELD_HEIGHT; j++) {
        if (cells[i][j] == EMPTY) {
            cells[i][j] = isRedTurn ? RED : YELLOW;
            checkWinner(i, j);
            isRedTurn = !isRedTurn;
            return true;
        }
    }
    return false; // Колонка полна
}

void Field::checkWinner(int i, int j) {
    Cell start = cells[i][j];
    int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

    for (int d = 0; d < 4; d++) {
        int length = 1;
        for (int side = -1; side <= 1; side += 2) {
            for (int step = 1; step < WIN_LENGTH; step++) {
                int iline = i + directions[d][0] * step * side;
                int jline = j + directions[d][1] * step * side;

                if (iline < 0 || iline >= FIELD_WIDTH || jline < 0 || jline >= FIELD_HEIGHT)
                    break;
                if (cells[iline][jline] != start)
                    break;
                length++;
            }
        }
        if (length >= WIN_LENGTH) {
            winner = start;
            return;
        }
    }
}

bool Field::isWon(bool red) const {
    return winner == (red ? RED : YELLOW);
}

bool Field::isOver() const {
    if (winner != EMPTY) return true;
    for (int i = 0; i < FIELD_WIDTH; i++) {
        if (cells[i][FIELD_HEIGHT - 1] == EMPTY) return false;
    }
    return true;
}

Cell Field::getCell(int i, int j) const {
    return cells[i][j];
}

bool Field::isRedTurnNow() const {
    return isRedTurn;
}

void Field::print() const {
    cout << "\n 1 2 3 4 5 6 7\n";
    for (int j = FIELD_HEIGHT - 1; j >= 0; j--) {
        cout << "|";
        for (int i = 0; i < FIELD_WIDTH; i++) {
            if (cells[i][j] == RED) cout << "R|";
            else if (cells[i][j] == YELLOW) cout << "Y|";
            else cout << "_|";
        }
        cout << "\n";
    }
}

void Field::printResult() const {
    print();
    if (winner == RED) cout << "Red Win!\n";
    else if (winner == YELLOW) cout << "Yellow Win!\n";
    else cout << "Draw!\n";
}