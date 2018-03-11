/*
 * File:   connectFour.h
 * Author: burak
 *
 * Created on 20 Eylül 2017 Çarşamba, 01:32
 */

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <string.h>
#include <fstream>

using namespace std;



char** createTable(int row);
void printTable(char ** table, int row);
int makeMove(char** table, const char user, const char target, int row);
bool isMoveLegal(char** table, const char target, int row, bool humanMove = true);
int checkRow(char** table, const char user, int row, int col, const int size, bool smallCase=false);
bool isCellValid(int size, int row, int col);
void resetTable(char** table, int row);
void destroyTable(char** table, int size);
void showWinnerCells(char** table, int size);

char playByComputer(char** table, int size);
char playerVsPlayer(char** table, int size, int turn = 1);
char playerVsComputer(char** table, int size, int turn = 1);

int loadGame(string &gameMode, int &tableSize, int &turn, char** &table, string filename);
int saveGame(string gameMode, int tableSize, int turn, char** &table, string filename);



int countRowEast(char** table, int row, int col, const char user, const int size, bool smallCase = false);
int countRowWest(char** table, int row, int col, const char user, const int size, bool smallCase = false);
int countRowSouth(char** table, int row, int col, const char user, const int size, bool smallCase = false);
int countRowSouthWest(char** table, int row, int col, const char user, const int size, bool smallCase = false);
int countRowSouthEast(char** table, int row, int col, const char user, const int size, bool smallCase = false);
int countRowNorthEast(char** table, int row, int col, const char user, const int size, bool smallCase = false);
int countRowNorthWest(char** table, int row, int col, const char user, const int size, bool smallCase = false);


int getTableSizeFromKeyboard();
string getGameModeFromKeyboard();
void printWinner(char winner);
int convertToInt(string input);

void makeSmallCase(char** table, int tableSize, int row, int col, int direction, char player);





#endif /* CONNECTFOUR_H */

