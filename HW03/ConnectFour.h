//
// Created by burak on 17.10.2017.
//

#ifndef HW03_CONNECTFOUR_H
#define HW03_CONNECTFOUR_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class ConnectFour {


public:


    ConnectFour(){
        turn = 1;
        height = 1;
        width = 1;
        winner = '?';

    }
    ConnectFour(int w, int h){
        gameCells.resize(height);
        turn = 1;
        winner = '?';
        width = w;
        height = h;
        maxTurn = width * height;
        for(auto &i:gameCells)
            i.resize(width);
    }

    ConnectFour(string filename){
        loadGame(filename);
    }


    static int getLivingCell() { return livingCell;}
    char getGameMode () const { return gameMode;}
    void getInputs();
    void playGame();
    void play();
    bool play(char pos);
    bool play(string command);
    void printTable();
    bool compare(ConnectFour &other);
    bool isGameEnded();


private:

    class Cell{
        int row;
        int column;
        char belongTo;


    public:

        Cell(){
            row = 0;
            column = 0;
        }

        Cell(char bt){
            belongTo = bt;
            Cell();
        }

        Cell(int r , int col, char belong = '.'){
            row = r;
            column = col;
            belongTo = belong;
            if(belong == '.')
                livingCell++;
        }

        Cell(int r, int col, int t){
            row = r;
            column = col;
            if(t % 2 == 1)
                belongTo = 'X';
            else
                belongTo = 'O';

        }

        /*Getters*/
        inline int getRow () const {return row;}
        inline int getCol () const {return column;}
        inline char getUser () const { return belongTo;}
        //inline static int getLivingCell()  { return livingCell;}

        /*Setters*/
        //inline void setRow (int row) {row = row;}
        //inline void setCol (int col) {column = col;}
        //inline void setCol (char col) {column = col - 'A';}
        inline void setUser (char p) {
            if(belongTo == '.') {
                livingCell++;
            }
            belongTo = p;
        }
        void setCell (int r, int c, char b) {
            row = r;
            column = c;
            belongTo = b;
        }

        /*Helper Functions*/
        bool isEmpty () {return belongTo == '.';}
        char showCell () { return belongTo;}

        void info() {cout << "row: " << row << endl;
            cout << "col: " << column << endl;
            cout << "Cell belong to " << belongTo;}
    };

    vector< vector<Cell> > gameCells;
    char gameMode;
    int turn;
    int maxTurn;
    int height;
    int width;
    char winner;
    const char user1 = 'X';
    const char user2 = 'O'; // also for computer
    static int livingCell;
    int cells = 0;

    int loadGame(string filename);
    int saveGame(string filename);

    char playByComputer();
    char playerVsPlayer();
    char playerVsComputer();

    bool isPosValid(int row, int pos);
        bool isMoveLegal(const char target, bool humanMove = true);
        int makeMove(const char user, const int target, int row);


    int checkRow(Cell cell, bool smallCase=false);
        int countRowEast(Cell cell, bool smallCase = false);
        int countRowWest(Cell cell, bool smallCase = false);
        int countRowSouth(Cell cell, bool smallCase = false);
        int countRowSouthWest(Cell cell, bool smallCase = false);
        int countRowSouthEast(Cell cell, bool smallCase = false);
        int countRowNorthEast(Cell cell, bool smallCase = false);
        int countRowNorthWest(Cell cell, bool smallCase = false);
        void makeSmallCase(Cell cell, int direction);


    void getTableSizeFromKeyboard();
    void getGameModeFromKeyboard();


    void printWinner();
    void resetTable();
    int convertToInt(string input);




};

#endif //HW03_CONNECTFOUR_H
