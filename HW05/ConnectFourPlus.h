//
// Created by burak.demir on 26.11.2017.
//

#ifndef HW05_CONNECTFOURPLUS_H
#define HW05_CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"
namespace CSE241 {
    class ConnectFourPlus : public ConnectFourAbstract {

    public:
        ConnectFourPlus() {
            turn = 1;
            height = 5;
            width = 5;
            winner = '?';
            createTable();
            resetTable();

        }

        ConnectFourPlus(int w, int h) {

            turn = 1;
            winner = '?';
            width = w;
            height = h;
            maxTurn = width * height;
            createTable();
            resetTable();

        }

        ConnectFourPlus(string filename) {
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

        int countRowEast(Cell cell, bool smallCase = false);

        int countRowWest(Cell cell, bool smallCase = false);

        int countRowSouth(Cell cell, bool smallCase = false);
    };
}

#endif //HW05_CONNECTFOURPLUS_H
