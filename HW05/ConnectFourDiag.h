//
// Created by burak.demir on 26.11.2017.
//

#ifndef HW05_CONNECTFOURDIAG_H
#define HW05_CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"
using namespace CSE241;

class ConnectFourDiag : public ConnectFourAbstract {

public:
    ConnectFourDiag() {
        turn = 1;
        height = 5;
        width = 5;
        winner = '?';
        createTable();
        resetTable();

    }

    ConnectFourDiag(int w, int h) {

        turn = 1;
        winner = '?';
        width = w;
        height = h;
        maxTurn = width * height;
        createTable();
        resetTable();

    }

    ConnectFourDiag(string filename) {
        width = 0;
        height = 0;
        maxTurn = 0;
        winner = '?';
        turn = 1;
        getBoardFromFile(filename);
    }

private:
    int checkRow(Cell cell, bool smallCase) override;

    void makeSmallCase(Cell cell, int direction) override;


    int countRowSouthWest(Cell cell, bool smallCase = false);

    int countRowSouthEast(Cell cell, bool smallCase = false);

    int countRowNorthEast(Cell cell, bool smallCase = false);

    int countRowNorthWest(Cell cell, bool smallCase = false);
};


#endif //HW05_CONNECTFOURDIAG_H
