//
// Created by burak.demir on 26.11.2017.


#include "ConnectFourUndo.h"

void ConnectFourUndo::makeUndo() {

    if(turn == FIRST_TURN) {
        cout << "There is no move to make undo\n";
        return;
    }
    char targetCol = moves.at(turn-2) - 'A';
    for (int i = 0; i < height; ++i) {
        if(gameCells[i][targetCol].getUser() != EMPTY_CELL &&
                gameCells[i][targetCol].getUser() != BLOCKED_CELL) {
            gameCells[i][targetCol].setUser(EMPTY_CELL);
            break;
        }
    }
    moves.pop_back();
    turn--;
    livingCell--;

    if(turn%2 == 0 && gameMode == 'C') { //if computer's turn
        printTable();
        play();
    }
}


bool ConnectFourUndo::play(string command) {

    bool nextTurn = false;

    if (command.length() == 1) {
        char pos = command.at(0);
        nextTurn = play(pos);

    } else if (command.find("LOAD") == 0) {
        string filename = command.substr(command.find_last_of(" \t") + 1);
        loadGame(filename);

    } else if (command.find("SAVE") == 0) {
        string filename = command.substr(command.find_last_of(" \t") + 1);
        saveGame(filename);
    } else if (command.find("UNDO") == 0) {
        makeUndo();
    }
    else if (command.find("PRINT VARS") == 0) {
        cout << "TableSize = " << height << " " << width
             << "\nGame Mode " << gameMode
             << "\nTurn " << turn
             << "\nMax turn " << maxTurn
             << "\nLiving Cell " << livingCell
             << "\nMoves Vector Size " << moves.size() << endl;

    } else {
        cout << "Wrong command!\n" << "Usage:\n-[A, " << (char) ('A' + width - 1) << "]"
             << "\n-LOAD file\n-SAVE file\n";
    }

    printTable();
    if (winner != '?')
        printWinner();

    return nextTurn;
}

ConnectFourUndo::ConnectFourUndo() : ConnectFourPlus() {

}

ConnectFourUndo::ConnectFourUndo(int w, int h) : ConnectFourPlus(w, h) {

}

ConnectFourUndo::ConnectFourUndo(string filename) : ConnectFourPlus(filename) {

}

int ConnectFourUndo::loadGame(string filename) {

    ifstream savedFile(filename);

    if (savedFile.is_open()) {

        destroyTable();

        savedFile >> gameMode;
        savedFile >> width;
        savedFile >> height;
        savedFile >> turn;
        savedFile >> maxTurn;
        savedFile >> livingCell;

        createTable();

        string user;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                getline(savedFile, user);
                gameCells[i][j].setCell(i, j, user[0]);
            }
        }
        moves.clear();
        char m;
        for (int i = 0; i < turn -1; ++i)  {
            savedFile >> m;
            moves.push_back(m);
        }

        cout << "Game is loaded\n";
        savedFile.close();
    } else {

        cerr << filename << "is missing or broken! (loadGame)\n";
        return -1;
    }

    return 1;

}

int ConnectFourUndo::saveGame(string filename) {

    ofstream file(filename);

    if (file.is_open()) {

        file << gameMode << endl;
        file << width << endl;
        file << height << endl;
        file << turn << endl;
        file << maxTurn << endl;
        file << livingCell;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file << gameCells[i][j].getUser();
                file << endl;
            }
        }

        for (int i = 0; i < turn-1; ++i) {
            file << moves.at(i);
        }

        cout << "Game is saved\n";

    } else {

        cerr << filename << "is missing or broken! (saveGame)\n";
        return -1;
    }
    return 0;

}

bool ConnectFourUndo::play(char pos) {
    if(ConnectFourAbstract::play(pos)){
        moves.push_back(pos);
        return true;
    }

    return false;

}

char ConnectFourUndo::play() {
    char move = ConnectFourAbstract::play();
    moves.push_back(move);
}

