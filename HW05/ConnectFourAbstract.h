//
// Created by burak.demir on 26.11.2017.
//

#ifndef HW05_CONNECTFOURABSTRACT_H
#define HW05_CONNECTFOURABSTRACT_H

#include "Cell.h"
#include <string>
#include <fstream>
#include <iostream>


#define MIN_COL 4
#define MAX_COL 25
#define BLOCKED_CELL ' '
#define EMPTY_CELL '*'
#define FIRST_TURN 1

using namespace std;
namespace CSE241 {
    class ConnectFourAbstract {

    public:

        int getLivingCell() { return livingCell; }
        virtual char getGameMode() const;
        virtual void setGameMode(char mode);

       //----------HW05--------
        virtual void getInputs();
        virtual void playGame();
        virtual char play();
        virtual bool play(char pos);
        virtual bool play(string command);
        virtual void printTable();
        //---------HW05-----------

        virtual bool isGameEnded();

        virtual int newGameFromFile(string filename);

        virtual void printWinner();

        virtual bool operator==(ConnectFourAbstract &other) const;

        void setWinner(char winner);

        int getTurn() const;

        int getMaxTurn() const;

        int getHeight() const;

        int getWidth() const;

        char getWinner() const;

        int getCells() const;

    protected:

        Cell **gameCells;
        int turn;
        char winner;
        char gameMode;
        int maxTurn;
        int height;
        int width;
        static int livingCell;
        int cells = 0;

        const char user1 = 'X';
        const char user2 = 'O'; // also for computer

        virtual void createTable();
        virtual void destroyTable();
        virtual void resetTable();

        bool isPosValid(int row, int pos);
        virtual int getBoardFromFile(string filename);

    private:

        //----------HW05----------
        virtual int loadGame(string filename);
        virtual int saveGame(string filename);

        virtual int checkRow(Cell cell, bool smallCase = false) = 0;
        virtual void makeSmallCase(Cell cell, int direction) = 0;

        virtual char playByComputer();
        virtual char playerVsPlayer();
        virtual char playerVsComputer();

        virtual bool isMoveLegal(const char target, bool humanMove = true);
        virtual int makeMove(const char user, const int target, int row);


        virtual void getTableSizeFromKeyboard();
        virtual void getGameModeFromKeyboard();
        virtual int convertToInt(string input);

    };

}
#endif //HW05_CONNECTFOURABSTRACT_H
