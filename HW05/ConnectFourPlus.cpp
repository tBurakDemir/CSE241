//
// Created by burak.demir on 26.11.2017.
//

#include "ConnectFourPlus.h"
using namespace CSE241;

int ConnectFourPlus::checkRow(Cell cell, bool smallCase) {

    int check = 0;

    if(countRowSouth(cell, smallCase) == 4){
        check = 1;
    }
    else if((countRowWest(cell, smallCase) +
             countRowEast(cell, smallCase)) >= 3){
        check = 2;
    }

    return check;
}

void ConnectFourPlus::makeSmallCase(Cell cell, int direction) {

    if(getTurn() %2 == 1)
        setWinner(user1);
    else
        setWinner(user2);

    switch(direction){
        case 1: countRowSouth(cell, true);
            break;
        case 2: gameCells[cell.getRow()][cell.getCol()].setUser(cell.getUser() + 32);
            countRowWest(cell, true);
            countRowEast(cell, true);
            break;
    }

}

int ConnectFourPlus::countRowEast(Cell cell, bool smallCase) {
    int count = 0;

    int row = cell.getRow();
    int col = cell.getCol()+1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){

        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        col++;
    }

    return count;
}

int ConnectFourPlus::countRowWest(Cell cell, bool smallCase) {
    int count = 0;

    int row = cell.getRow();
    int col = cell.getCol()-1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){

        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        col--;
    }

    return count;
}

int ConnectFourPlus::countRowSouth(Cell cell, bool smallCase) {
    int count = 0;

    int row = cell.getRow();
    int col = cell.getCol();

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){
        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);

        count++;
        row++;
    }

    return count;
}
