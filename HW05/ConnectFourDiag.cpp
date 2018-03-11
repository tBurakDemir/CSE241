//
// Created by burak.demir on 26.11.2017.
//

#include "ConnectFourDiag.h"
using namespace CSE241;

int ConnectFourDiag::checkRow(Cell cell, bool smallCase) {
    int check = 0;

    if ((countRowSouthEast(cell, smallCase) +
         countRowNorthWest(cell, smallCase)) >= 3) {
        check = 1;
    } else if ((countRowSouthWest(cell, smallCase) +
                countRowNorthEast(cell, smallCase)) >= 3) {
        check = 2;
    }

    return check;
}

void ConnectFourDiag::makeSmallCase(Cell cell, int direction) {
    if (turn % 2 == 1)
        winner = user1;
    else
        winner = user2;

    switch (direction) {
        case 1:
            gameCells[cell.getRow()][cell.getCol()].setUser(cell.getUser() + 32);
            countRowSouthEast(cell, true);
            countRowNorthWest(cell, true);
            break;
        case 2:
            gameCells[cell.getRow()][cell.getCol()].setUser(cell.getUser() + 32);
            countRowSouthWest(cell, true);
            countRowNorthEast(cell, true);
            break;
    }
}


int ConnectFourDiag::countRowSouthWest(Cell cell, bool smallCase) {
    int count = 0;

    int row = cell.getRow() + 1;
    int col = cell.getCol() - 1;

    while (isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()) {
        if (smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        row++;
        col--;
    }

    return count;
}

int ConnectFourDiag::countRowSouthEast(Cell cell, bool smallCase) {
    int count = 0;

    int row = cell.getRow() + 1;
    int col = cell.getCol() + 1;

    while (ConnectFourAbstract::isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()) {
        if (smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        row++;
        col++;
    }

    return count;
}

int ConnectFourDiag::countRowNorthEast(Cell cell, bool smallCase) {

    int count = 0;

    int row = cell.getRow() - 1;
    int col = cell.getCol() + 1;

    while (isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()) {
        if (smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        row--;
        col++;
    }

    return count;
}

int ConnectFourDiag::countRowNorthWest(Cell cell, bool smallCase) {
    int count = 0;

    int row = cell.getRow() - 1;
    int col = cell.getCol() - 1;

    while (isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()) {
        if (smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);

        count++;
        row--;
        col--;
    }

    return count;
}

