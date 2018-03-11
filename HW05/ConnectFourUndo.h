//
// Created by burak.demir on 26.11.2017.
//

#ifndef HW05_CONNECTFOURUNDO_H
#define HW05_CONNECTFOURUNDO_H

#include "ConnectFourPlus.h"
#include <vector>
using namespace CSE241;

class ConnectFourUndo :public ConnectFourPlus{
public:
    bool play(string command) override;

    ConnectFourUndo();

    ConnectFourUndo(int w, int h);

    bool play(char pos) override;

    char play() override;

    ConnectFourUndo(string filename);

private:
    int loadGame(string filename) override;

    int saveGame(string filename) override;

    vector<char> moves;
    void makeUndo();

};


#endif //HW05_CONNECTFOURUNDO_H
