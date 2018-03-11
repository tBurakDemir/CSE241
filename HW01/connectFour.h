/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   connectFour.h
 * Author: burak
 *
 * Created on 20 Eylül 2017 Çarşamba, 01:32
 */

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <string.h>
using namespace std;




char** createTable(int row);
void printTable(char ** table, int row);
int makeMove(char** table, const char user, const char target, int row);
bool isMoveLegal(char** table, const char target, int row);
int checkRow(char** table, const char user, int row, int col, const int size, bool smallCase);
bool isCellValid(int size, int row, int col);
void resetTable(char** table, int row);
void destroyTable(char** table, int size);
void showWinnerCells(char** table, int size);

char playByComputer(char** table, int size);
char playerVsPlayer(char** table, int size);
char playerVsComputer(char** table, int size);



int countRowEast(char** table, int row, int col, const char user, const int size, bool smallCase);
int countRowWest(char** table, int row, int col, const char user, const int size, bool smallCase);
int countRowSouth(char** table, int row, int col, const char user, const int size, bool smallCase);
int countRowSouthWest(char** table, int row, int col, const char user, const int size, bool smallCase);
int countRowSouthEast(char** table, int row, int col, const char user, const int size, bool smallCase);
int countRowNorthEast(char** table, int row, int col, const char user, const int size, bool smallCase);
int countRowNorthWest(char** table, int row, int col, const char user, const int size, bool smallCase);


int getTableSizeFromKeyboard();
string getGameModeFromKeyboard();
void printWhoWin(char whoWin);
int convertToInt(string input);

void makeSmallCase(char** table, int tableSize, int row, int col, int direction, char player);





#endif /* CONNECTFOUR_H */

