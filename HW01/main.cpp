/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: burak
 *
 * Created on 18 Eylül 2017 Pazartesi, 15:28
 */

#include <cstdlib>
#include <iostream>
#include "connectFour.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    char** table;
    char target; //a letter which will indicate table's column.
    int row, col, tableSize; //table's row, column and size.
    char whoWin = '?';  // 'X' for player 1, 'O' for player 2 or computer 
    string gameMode; // P for PvP, C for PvE
    
   
    tableSize = getTableSizeFromKeyboard();
    gameMode = getGameModeFromKeyboard();

    table = createTable(tableSize);

    if(gameMode == "P")
        whoWin = playerVsPlayer(table, tableSize); // returns 'X' or 'O'
    else
        whoWin = playerVsComputer(table, tableSize); // returns 'X' or 'O'
    
    printWhoWin(whoWin);
    
    destroyTable(table, tableSize);
    
    cout << "Good bye!" << endl;
    
    return 0;
}


char playerVsPlayer(char** table, int tableSize){
    
    int i = 0, row, col, direction;
    char whoWin = '?';
    char target;
    
    int maxTurn = tableSize * tableSize;
    printTable(table, tableSize);
        
    while(i < maxTurn && whoWin == '?'){

        cout << "Pick a target\n";
        cin >> target;
        col = target - 'A';

        if(isMoveLegal(table, target, tableSize)){
            
            //Player 1's Turn
            if(i%2 == 0){
                row = makeMove(table ,'X', target, tableSize);
                if(direction = checkRow(table, 'X', row, col, tableSize, false)){   
                    makeSmallCase(table, tableSize, row, col, direction, 'X');
                    whoWin = 'X'; // X for Player 1
                }
            }//Player 2's Turn
            else{
                row= makeMove(table ,'O', target, tableSize);
                if(direction = checkRow(table, 'O', row, col, tableSize, false)){            
                   makeSmallCase(table, tableSize, row, col, direction, 'O');
                    whoWin = 'O'; // O for Player 2 
                }
            }
            printTable(table, tableSize);
            i++;  
        }
    }
    return whoWin;  
}


char playerVsComputer(char** table, int tableSize){
    
   
    int i = 0, row, col, direction;
    char whoWin = '?';
    char target;
    int maxTurn = tableSize * tableSize/2;
    
    printTable(table, tableSize);
        
    while(i < maxTurn && whoWin == '?'){

        cout << "Pick a target\n";
        cin >> target;
  
        if(isMoveLegal(table, target, tableSize)){
            
            
            //Player's Turn
            col = target - 'A';
            row = makeMove(table ,'X', target, tableSize);
            if(direction = checkRow(table, 'X', row, col, tableSize, false)){
                whoWin = 'X'; // X for Player
                makeSmallCase(table, tableSize, row, col, direction, 'X');
            }
            printTable(table, tableSize);
            
            
            //Computer's Turn
            if(whoWin != 'X'){ // if Player doesn't win
                
                target = playByComputer(table, tableSize); //Computer decides which column to make move
                col = target - 'A';
                row = makeMove(table, 'O', target, tableSize);
                if(direction = checkRow(table, 'O', row, col, tableSize, false)){
                    makeSmallCase(table, tableSize, row, col, direction, 'O');
                    whoWin = 'C'; // C for computer
                }
                printTable(table, tableSize);
            }    
            i++;
        }
        
        
    }
    return whoWin; 
}

char playByComputer(char** table, int size){
    
    char target = 'A';
    
    for(int i = 0; i<size; i++)
        if(isMoveLegal(table, target+i, size))
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
    
    for (int i=0; i < size; i++)
         free(table[i]);
    free(table);
    
}

void resetTable(char** table, int row){
    
    for(int i=0; i < row; i++)
        for(int j=0; j < row; j++)
            table[i][j] = '.';
    
}

void printTable(char** table, int row){
      
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

bool isMoveLegal(char** table, const char target, int row){
    
    bool status = true;
    
    if(target < 'A' || target > ('A' + row - 1)){
        cerr << "Wrong move! Be sure your target column is "
                "between A and " << (char)('A' + row -1) << endl;
        status = false;
    } 
    else if(table[0][target - 'A'] != '.'){
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
        cout << "\nEnter the table size (3 < size < 25)\n";
        cin.clear();
        cin >> input;
        
        tableSize = convertToInt(input);
    }while(tableSize <= 3 || tableSize >= 25);
    
    return tableSize;
    
}

string getGameModeFromKeyboard(){
    
    string input;
    
    do{
        cout << "\nSelect the game mode\n";
        cout << "P - Player vs Player\n";
        cout << "C - Player vs Computer\n";
        cin.clear();
        cin >> input;
       
    }while(input != "P" && input != "C");
    
    return input;
    
}

void printWhoWin(char whoWin){
    
    if(whoWin == '?')
        cout << "Tie!"<<endl;
    else if(whoWin == 'X')
        cout << "Player 1 won!"<<endl;
    else if(whoWin == 'O')
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








