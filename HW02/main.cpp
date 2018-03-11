/* 
 * File:   main.cpp
 * Author: burak
 *
 * Created on 18 Eylül 2017 Pazartesi, 15:28
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "connectFour.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    char** table;
    char winner = '?';  // 'X' for player 1, 'O' for player 2 or computer


    decltype(getTableSizeFromKeyboard()) tableSize = getTableSizeFromKeyboard();
    decltype(getGameModeFromKeyboard()) gameMode = getGameModeFromKeyboard();

    table = createTable(tableSize);

    if(gameMode == "P")
        winner = playerVsPlayer(table, tableSize); // returns 'X' or 'O'
    else
        winner = playerVsComputer(table, tableSize); // returns 'X' or 'O'

    printWinner(winner);

    destroyTable(table, tableSize);

    cout << "Good bye!" << endl;

    return 0;
}



int loadGame(string &gameMode, int &tableSize, int &turn, char** &table, string filename){

    ifstream saveFile(filename);
    if(saveFile.is_open()){
        destroyTable(table, tableSize);
        saveFile >> gameMode;
        saveFile >> tableSize;
        saveFile >> turn;
        table = createTable(tableSize);
        for (int i = 0; i < tableSize ; ++i) {
            for (int j = 0; j < tableSize; ++j) {
                saveFile >> table[i][j];
            }
        }
        cout << "Game is loaded\n";
        saveFile.close();
    }
    else{
        cerr << filename <<"is missing or broken! (loadGame)\n";
        return -1;
    }

    return 1;
}


int saveGame(string gameMode, int tableSize, int turn, char** &table, string filename) {

    ofstream file(filename);
    if (file.is_open()) {
        file << gameMode << endl;
        file << tableSize << endl;
        file << turn << endl;
        for (int i = 0; i < tableSize; ++i) {
            for (int j = 0; j < tableSize; ++j) {
                file << table[i][j] << endl;
            }
        }
        cout << "Game is saved\n";
    } else {
        cerr << filename << "is missing or broken! (saveGame)\n";
        return -1;
    }
    return 0;
}


char playerVsPlayer(char** table, int tableSize, int turn/*= 1*/){

    int row, col, direction;
    char whoWin = '?';
    string command;
    string gameMode = "P";

    int maxTurn = tableSize * tableSize;
    printTable(table, tableSize);
    if(turn == 1) //If it is a new game
        cin.ignore();//Ignores '\n', '\t' '

    while(turn <= maxTurn && whoWin == '?'){

        cout << "Pick a target\n";

        getline(cin, command);



        if(command.length() == 1){
            char targetCol = command.at(0);

            if(isMoveLegal(table, targetCol, tableSize)){
                col = targetCol - 'A';


                //Player 1's Turn
                if(turn%2 == 1){
                    row = makeMove(table ,'X', targetCol, tableSize);
                    if(direction = checkRow(table, 'X', row, col, tableSize)){
                        makeSmallCase(table, tableSize, row, col, direction, 'X');
                        whoWin = 'X'; // X for Player 1
                    }
                }
                //Player 2's Turn
                else{
                    row= makeMove(table ,'O', targetCol, tableSize);
                    if(direction = checkRow(table, 'O', row, col, tableSize)){
                        makeSmallCase(table, tableSize, row, col, direction, 'O');
                        whoWin = 'O'; // O for Player 2
                    }
                }
                printTable(table, tableSize);
                turn++;
            }
        }
        else if(command.find("LOAD") == 0) {
            string filename = command.substr(command.find_last_of(" \t") + 1);
            loadGame(gameMode, tableSize, turn, table, filename);
            if(gameMode == "P") {
                whoWin = playerVsPlayer(table, tableSize, turn); // returns 'X' or 'O'

            }else
                whoWin = playerVsComputer(table, tableSize, turn); // returns 'X' or 'O'
            if(whoWin == '?') {
                printWinner(whoWin);
                exit(0);
            }
        }
        else if(command.find("SAVE") == 0) {
            string filename = command.substr(command.find_last_of(" \t") + 1);
            saveGame(gameMode, tableSize, turn + 1, table, filename);
        }
        else if (command.find("PRINT VARS") == 0){
            cout << "TableSize = " << tableSize
                 <<"\nGame Mode"<< gameMode
                 << "\nTurn " << turn
                << "\nMax turn" << maxTurn;
                printTable(table, tableSize);
        }
        else {
            cout << "Wrong command!\n" << "Usage:\n-[A, " <<(char)('A' + tableSize-1) << "]"
                 <<"\n-LOAD file\n-SAVE file\n";
        }
    }
    return whoWin;
}


char playerVsComputer(char** table, int tableSize, int turn/*= 1*/){


    int row, col, direction;
    char whoWin = '?';
    string command;
    int maxTurn = tableSize * tableSize;
    string gameMode = "C";

    printTable(table, tableSize);
    if(turn == 1)  //If it is a new game
        cin.ignore();//Ignores '\n', '\t' '

    while(turn <= maxTurn && whoWin == '?'){

        cout << "Pick a target\n";

        getline(cin, command);



        if(command.length() == 1) {
            char target = command.at(0);

            if (isMoveLegal(table, target, tableSize)) {


                //Player's Turn
                col = target - 'A';
                row = makeMove(table, 'X', target, tableSize);
                if (direction = checkRow(table, 'X', row, col, tableSize)) {
                    whoWin = 'X'; // X for Player
                    makeSmallCase(table, tableSize, row, col, direction, 'X');
                }
                printTable(table, tableSize);


                //Computer's Turn
                if (whoWin != 'X') { // if Player doesn't win

                    target = playByComputer(table, tableSize); //Computer decides which column to make move
                    col = target - 'A';
                    row = makeMove(table, 'O', target, tableSize);
                    if (direction = checkRow(table, 'O', row, col, tableSize)) {
                        makeSmallCase(table, tableSize, row, col, direction, 'O');
                        whoWin = 'C'; // C for computer
                    }
                    printTable(table, tableSize);
                }
                turn += 2;
            }
        }
        else if(command.find("LOAD") == 0) {
            string filename = command.substr(command.find_last_of(" \t") + 1);
            loadGame(gameMode, tableSize, turn, table, filename);
            if(gameMode == "P")
                whoWin = playerVsPlayer(table, tableSize, turn+1); // returns 'X' or 'O'
            else
                whoWin = playerVsComputer(table, tableSize, turn+1); // returns 'X' or 'O'

            if(whoWin == '?') {
                printWinner(whoWin);
                exit(0);
            }
        }
        else if(command.find("SAVE") == 0){
            string filename = command.substr(command.find_last_of(" \t") + 1);
            saveGame(gameMode, tableSize, turn + 1, table, filename);
        } else {
            cout<< "Wrong command!\n" << "Usage:\n[A, " << (char)('A' + tableSize-1) << "]"
                    <<"\nLOAD file\nSAVE file\n";
        }

    }
    return whoWin;
}

char playByComputer(char** table, int size){

    char target = 'A';

    for(int i = 0; i<size; i++)
        if(isMoveLegal(table, target+i, size, false))
            return target + i; //column  that will be played by comp.

}

char** createTable(int row){

    char ** table = (char **)malloc(row * sizeof(char *));
    for (int i=0; i<row; i++)
        table[i] = (char *)malloc(row * sizeof(char));

    resetTable(table, row);

    return table;
}

void destroyTable(char** table, int size){

    for (auto i=0; i < size; i++)
        free(table[i]);
    free(table);

}

void resetTable(char** table, int row){

    for(auto i=0; i < row; i++)
        for(auto j=0; j < row; j++)
            table[i][j] = '.';

}

void printTable(char** table, int row){

    cout << endl << endl;

    for(int i = 0; i < row; i++)
        cout << (char)('A' + i) << ' ';
    cout << endl;

    for(int i=0; i < row; i++){
        for(int j=0; j < row; j++){
            cout << table[i][j] << ' ';
        }
        cout << endl;
    }
}

int makeMove(char** table, const char user, const char target, int row){

    if(table[row-1][target-'A'] != '.')
        return  makeMove(table, user, target, row-1);
    else
        table[row-1][target-'A'] = user;

    return row - 1;
}

bool isMoveLegal(char** table, const char target, int row, bool humanMove /*= true*/){

    bool status = true;

    if(target < 'A' || target > ('A' + row - 1)){
        if (humanMove)
            cerr << "Wrong move! Be sure your target column is "
                "between A and " << (char)('A' + row -1) << endl;
        status = false;
    }
    else if(table[0][target - 'A'] != '.'){

        if (humanMove)
            cerr << "Wrong move! Be sure your target column is not complete full.\n";
        status = false;
    }

    return status;
}

int checkRow(char** table, const char user, int row, int col, const int size, bool smallCase){

    int check = 0;
    if(countRowSouth(table, row, col, user, size, smallCase) == 4){
        check = 1;
    }
    else if((countRowSouthEast(table, row, col, user, size, smallCase) +
             countRowNorthWest(table, row-1, col-1, user, size, smallCase)) >= 4){
        check = 2;
    }
    else if((countRowWest(table, row, col, user, size, smallCase) +
             countRowEast(table, row, col+1, user, size, smallCase)) >= 4){
        check = 3;
    }
    else if((countRowSouthWest(table, row, col, user, size, smallCase) +
             countRowNorthEast(table, row-1, col+1, user, size, smallCase)) >= 4){
        check = 4;
    }

    return check;
}

int countRowSouth(char** table, int row, int col, const char user, const int size, bool smallCase){

    int count = 0;

    while(isCellValid(size, row, col) && table[row][col] == user){
        if(smallCase)
            table[row][col] = user + 32;

        count++;
        row++;
    }

    return count;

}

int countRowEast(char** table, int row, int col, const char user, const int size, bool smallCase){

    int count = 0;

    while(isCellValid(size, row, col) && table[row][col] == user){

        if(smallCase)
            table[row][col] = user + 32;
        count++;
        col++;
    }
    return count;
}

int countRowWest(char** table, int row, int col, const char user, const int size, bool smallCase){

    int count = 0;

    while(isCellValid(size, row, col) && table[row][col] == user){

        if(smallCase)
            table[row][col] = user + 32;
        count++;
        col--;
    }

    return count;
}

int countRowSouthWest(char** table, int row, int col, const char user, const int size, bool smallCase){

    int count = 0;
    while(isCellValid(size, row, col) && table[row][col] == user){
        if(smallCase)
            table[row][col] = user + 32;
        count++;
        row++;
        col--;
    }

    return count;
}

int countRowSouthEast(char** table, int row, int col, const char user, const int size, bool smallCase){

    int count = 0;

    while(isCellValid(size, row, col) && table[row][col] == user){
        if(smallCase)
            table[row][col] = user + 32;
        count++;
        row++;
        col++;
    }

    return count;
}

int countRowNorthEast(char** table, int row, int col, const char user, const int size, bool smallCase){

    int count = 0;

    while(isCellValid(size, row, col) && table[row][col] == user){
        if(smallCase)
            table[row][col] = user + 32;

        count++;
        row--;
        col++;
    }

    return count;
}

int countRowNorthWest(char** table, int row, int col, const char user, const int size, bool smallCase){

    int count = 0;
    while(isCellValid(size, row, col) && table[row][col] == user){
        if(smallCase)
            table[row][col] = user + 32;

        count++;
        row--;
        col--;
    }

    return count;
}

bool isCellValid(int size, int row, int col){

    if(row >= size || row < 0 || col >= size || col < 0)
        return false;
    return true;

}

int getTableSizeFromKeyboard(){

    string input;
    int tableSize = 0;

    do{
        cout << "\nEnter the table size (4, 6, 8, ... 20)\n";
        cin >> input;
        tableSize = convertToInt(input);
    }while(tableSize <= 3 || tableSize >= 25 || tableSize % 2 != 0);

    return tableSize;

}

string getGameModeFromKeyboard(){

    string input;

    do{
        cout << "\nSelect the game mode\n";
        cout << "P - Player vs Player\n";
        cout << "C - Player vs Computer\n";
        cin >> input;

    }while(input != "P" && input != "C");

    return input;

}

void printWinner(char winner){

    if(winner == '?')
        cout << "Tie!"<<endl;
    else if(winner == 'X')
        cout << "Player 1 won!"<<endl;
    else if(winner == 'O')
        cout << "Player 2 won!"<<endl;
    else
        cout << "Computer won!"<<endl;
}

int convertToInt(string input){

    int number = 0;

    for(int i = 0; i < input.length(); i++){
        if(input.at(i) < '0' || input.at(i) > '9')
            return -2;
        else{
            number = number * 10 + input.at(i) - '0';
        }

    }

    return number;
}

void makeSmallCase(char** table, int tableSize, int row, int col, int direction, char user){

    switch(direction){
        case 1: countRowSouth(table, row, col, user, tableSize, true);
            break;
        case 2: countRowSouthEast(table, row, col, user, tableSize, true);
            countRowNorthWest(table, row, col, user, tableSize, true);
            break;

        case 3: countRowWest(table, row, col, user, tableSize, true);
            countRowEast(table, row, col, user, tableSize, true);
            break;
        case 4: countRowSouthWest(table, row, col, user, tableSize, true);
            countRowNorthEast(table, row, col, user, tableSize, true);
            break;
    }

}
