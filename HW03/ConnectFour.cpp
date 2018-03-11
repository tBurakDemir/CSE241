//
// Created by burak on 17.10.2017.
//

#include <iostream>
#include "ConnectFour.h"
using namespace std;


int ConnectFour::loadGame(string filename){

    ifstream saveFile(filename);
    if(saveFile.is_open()){

        //destroyTable(table, tableSize);
        saveFile >> gameMode;
        saveFile >> width;
        saveFile >> height;
        saveFile >> turn;
        //saveFile >> lCell;


        gameCells.resize(height);
        for (int i = 0; i < height ; ++i) {
            gameCells[i].resize(width);
        }

        char user;
        for (int i = 0; i < height ; ++i) {
            for (int j = 0; j < width; ++j) {
                saveFile >> user;
                gameCells[i][j].setCell(i, j, user);
            }
        }
        maxTurn = width * height;


        cout << "Game is loaded\n";
        saveFile.close();
    }
    else{

        cerr << filename <<"is missing or broken! (loadGame)\n";
        return -1;
    }

    return 1;
}


int ConnectFour::saveGame(string filename) {

    ofstream file(filename);

    if (file.is_open()) {

        file << gameMode << endl;
        file << width << endl;
        file << height << endl;
        file << turn << endl;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                file << gameCells[i][j].getUser() << endl;
            }
        }

        cout << "Game is saved\n";

    } else {

        cerr << filename << "is missing or broken! (saveGame)\n";
        return -1;
    }
    return 0;
}


char ConnectFour::playerVsPlayer(){

    char whoWin = '?';
    string command;

    while(turn <= maxTurn && winner == '?'){

        cout << "Pick a target\n";
        getline(cin, command);

        play(command);
    }

    return whoWin;
}


char ConnectFour::playerVsComputer(){

    string command;
    maxTurn = height * width;
    string gameMode = "C";

    printTable();
    if(turn == 1)  //If it is a new game
        cin.ignore();//Ignores '\n', '\t' '

    while(turn <= maxTurn && winner == '?'){

        cout << "Pick a target\n";

        getline(cin, command);

        if(command.length() == 1) {
            char pos = command.at(0);
            if (isMoveLegal(pos)) {

                bool tr = play(pos);
                printTable();
                //Computer's Turn
                if (winner != 'X' && tr) { // if Player doesn't win
                    play();
                    printTable();
                }

            }
        }
        else if(command.find("LOAD") == 0) {
            string filename = command.substr(command.find_last_of(" \t") + 1);
            loadGame(filename);
            if(gameMode == "P")
                winner = playerVsPlayer(); // returns 'X' or 'O'
            else
                winner = playerVsComputer(); // returns 'X' or 'O'

            if(winner == '?') {
                printWinner();
                exit(0);
            }
        }
        else if(command.find("SAVE") == 0){
            string filename = command.substr(command.find_last_of(" \t") + 1);
            saveGame(filename);
        } else {
            cout<< "Wrong command!\n" << "Usage:\n[A, " << (char)('A' + width-1) << "]"
                <<"\nLOAD file\nSAVE file\n";
        }

    }
    return winner;
}

char ConnectFour::playByComputer(){

    char target = 'A';

    for(int i = 0; i<width; i++)
        if(isMoveLegal(target+i, false))
            return target + i; //column  that will be played by comp.

}

void ConnectFour::printTable(){

    cout << endl << endl;

    for(int i = 0; i < width; i++)
        cout << (char)('A' + i) << ' ';
    cout << endl;

    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++){
            cout << gameCells[i][j].getUser() << ' ';
        }
        cout << endl;
    }

    cout << "Living Cell: " << livingCell << endl;
}

int ConnectFour::makeMove(const char user, const int col, int row){

    if(gameCells[row-1][col].getUser() != '.')
        return  makeMove(user, col, row-1);
    else
        gameCells[row-1][col].setUser(user);

    return row - 1;
}

bool ConnectFour::isMoveLegal(const char target, bool humanMove /*= true*/){

    bool status = true;



    if(target < 'A' || target > ('A' + width - 1)){
        if (humanMove)
            cerr << "Wrong move! Be sure your target column is "
                    "between A and " << (char)('A' + width -1) << endl;
        status = false;
    }
    else if(gameCells[0][target - 'A'].getUser() != '.'){

        if (humanMove)
            cerr << "Wrong move! Be sure your target column is not complete full.\n";
        status = false;
    }


    return status;
}

int ConnectFour::checkRow(Cell cell, bool smallCase /*= false*/){

    int check = 0;

    if(countRowSouth(cell, smallCase) == 4){
        check = 1;
    }
    else if((countRowSouthEast(cell, smallCase) +
             countRowNorthWest(cell, smallCase)) >= 3){
        check = 2;
    }
    else if((countRowWest(cell, smallCase) +
             countRowEast(cell, smallCase)) >= 3){
        check = 3;
    }
    else if((countRowSouthWest(cell, smallCase) +
             countRowNorthEast(cell, smallCase)) >= 3){
        check = 4;
    }

    return check;
}

int ConnectFour::countRowSouth(const Cell cell, bool smallCase){

    int count = 0;

    int row = cell.getRow();
    int col = cell.getCol();

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){
        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);

        count++;
        row++;
    }

    return count;

}

int ConnectFour::countRowEast(const Cell cell, bool smallCase){

    int count = 0;

    int row = cell.getRow();
    int col = cell.getCol()+1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){

        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        col++;
    }

    return count;
}

int ConnectFour::countRowWest(const Cell cell, bool smallCase){

    int count = 0;

    int row = cell.getRow();
    int col = cell.getCol()-1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){

        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        col--;
    }

    return count;
}

int ConnectFour::countRowSouthWest(const Cell cell, bool smallCase){

    int count = 0;

    int row = cell.getRow()+1;
    int col = cell.getCol()-1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){
        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        row++;
        col--;
    }

    return count;
}

int ConnectFour::countRowSouthEast(const Cell cell, bool smallCase){

    int count = 0;

    int row = cell.getRow()+1;
    int col = cell.getCol()+1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){
        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        row++;
        col++;
    }

    return count;
}

int ConnectFour::countRowNorthEast(const Cell cell, bool smallCase){

    int count = 0;

    int row = cell.getRow()-1;
    int col = cell.getCol()+1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){
        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);
        count++;
        row--;
        col++;
    }

    return count;
}

int ConnectFour::countRowNorthWest(const Cell cell, bool smallCase){

    int count = 0;

    int row = cell.getRow()-1;
    int col = cell.getCol()-1;

    while(isPosValid(row, col) && gameCells[row][col].getUser() == cell.getUser()){
        if(smallCase)
            gameCells[row][col].setUser(cell.getUser() + 32);

        count++;
        row--;
        col--;
    }

    return count;
}

bool ConnectFour::isPosValid(int row, int pos) {

    if(row >= height || row < 0
        || pos >= width || pos < 0)
         return false;

    return true;

}

void ConnectFour::getTableSizeFromKeyboard(){

    string input;

    do{
        cout << "\nEnter the table width [4, 25]\n";
        cin >> input;
        width = convertToInt(input);
    }while(width < 4 || width > 25);

    do{
        cout << "\nEnter the table height [4, 25]\n";
        cin >> input;
        height = convertToInt(input);
    }while(height < 4 || height > 25);

    maxTurn = height * width;

}

void ConnectFour::getGameModeFromKeyboard(){

    string input;

    do{
        cout << "\nSelect the game mode\n";
        cout << "P - Player vs Player\n";
        cout << "C - Player vs Computer\n";
        cin.ignore();
        cin >> input;

    }while(input != "P" && input != "C");

    gameMode = input[0];

}

void ConnectFour::printWinner(){

    if(winner == '?')
        cout << "Tie!"<<endl;
    else if(winner == user1)
        cout << "Player 1 won!"<<endl;
    else if(winner == user2 && gameMode == 'P')
        cout << "Player 2 won!"<<endl;
    else
        cout << "Computer won!"<<endl;
}

int ConnectFour::convertToInt(string input){

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

void ConnectFour::makeSmallCase(Cell cell, int direction){

    if(turn %2 == 1)
        winner = user1;
    else
        winner = user2;

    switch(direction){
        case 1: countRowSouth(cell, true);
            break;
        case 2:
            gameCells[cell.getRow()][cell.getCol()].setUser(cell.getUser() + 32);
            countRowSouthEast(cell, true);
            countRowNorthWest(cell, true);
            break;

        case 3:
            gameCells[cell.getRow()][cell.getCol()].setUser(cell.getUser() + 32);
            countRowWest(cell, true);
            countRowEast(cell, true);
            break;
        case 4:
            gameCells[cell.getRow()][cell.getCol()].setUser(cell.getUser() + 32);
            countRowSouthWest(cell, true);
            countRowNorthEast(cell, true);
            break;
    }

}

void ConnectFour::play(){

    char pos = playByComputer(); //Computer decides which column to make move
    int col = pos - 'A';
    int row = makeMove(user2, col, height);
    printTable();

    Cell newCell(row, col, user2);
    if (int direction = checkRow(newCell)) {
        makeSmallCase(newCell, direction);
        winner = 'C'; // C for computer
    }
    turn++;

    if(isGameEnded())
        printWinner();


}
bool ConnectFour::play(char pos){

    if(isMoveLegal(pos))
    {
        int col = pos - 'A';
        int row;
        if(turn % 2 == 1)
            row = makeMove(user1, col, height);
        else
            row = makeMove(user2, col, height);

        Cell newCell(row, col, turn);
        if (int direction = checkRow(newCell)) {
            // X for Player
            makeSmallCase(newCell, direction);
        }
        printTable();
        turn++;

        if(isGameEnded())
            printWinner();

        return true;
    }
    return false;
}

void ConnectFour::playGame() {

    getInputs();

    if(gameMode == 'P')
        playerVsPlayer();
    else
        playerVsComputer();

    printWinner();

    cout << "Good bye!" << endl;

}

void ConnectFour::getInputs() {

    if(turn == 1){
        getTableSizeFromKeyboard();
        getGameModeFromKeyboard();

        gameCells.resize(height);
        for (int i = 0; i < height ; ++i) {
            gameCells[i].resize(width);
        }
        resetTable();
    }
}

void ConnectFour::resetTable(){

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            gameCells[i][j].setUser('.');
        }
    }
}

/*karşılaştırmayı sahip oldukları hücrelere göre yaptım.*/

bool ConnectFour::compare(ConnectFour &other) {

    if(this->turn < other.turn)
        return false;
    return true;
}

bool ConnectFour::isGameEnded() {


    if(turn >= maxTurn || winner != '?')
        return true;
    return false;
}

bool ConnectFour::play(string command) {

    if(command.length() == 1)
    {
        char pos = command.at(0);
        return play(pos);

    }
    else if(command.find("LOAD") == 0)
    {
        string filename = command.substr(command.find_last_of(" \t") + 1);
        loadGame(filename);
        printTable();


    }
    else if(command.find("SAVE") == 0)
    {
        string filename = command.substr(command.find_last_of(" \t") + 1);
        saveGame(filename);
    }
    else if (command.find("PRINT VARS") == 0)
    {
        cout << "TableSize = " << height << " " << width
             <<"\nGame Mode "<< gameMode
             << "\nTurn " << turn
             << "\nMax turn " << maxTurn
             << "\nLiving Cell " << livingCell <<endl;
        printTable();
    }
    else {
        cout << "Wrong command!\n" << "Usage:\n-[A, " <<(char)('A' + width-1) << "]"
             <<"\n-LOAD file\n-SAVE file\n";

    }

    return false;

}



