//
// Created by burak.demir on 26.11.2017.
//

#include "ConnectFourAbstract.h"
namespace CSE241 {

    char ConnectFourAbstract::getGameMode() const { return gameMode; }

    void ConnectFourAbstract::getInputs() {

        getTableSizeFromKeyboard();
        getGameModeFromKeyboard();

        createTable();
        resetTable();

    }

    void ConnectFourAbstract::setGameMode(char mode) {
        gameMode = mode;
    }

    void ConnectFourAbstract::playGame() {


        if (gameMode == 'P')
            playerVsPlayer();
        else
            playerVsComputer();

        printWinner();

        cout << "Good bye!" << endl;
    }

    char ConnectFourAbstract::play() {

        char pos = playByComputer(); //Computer decides which column to make move
        int col = pos - 'A';
        int row = makeMove(user2, col, height);
        Cell newCell(row, col, user2);
        if (int direction = checkRow(newCell)) {
            makeSmallCase(newCell, direction);
            winner = 'C'; // C for computer
        }
        turn++;
        livingCell++;

        printTable();
        return pos;
    }

    bool ConnectFourAbstract::play(char pos) {
        if (isMoveLegal(pos)) {

            int col = pos - 'A';
            int row;
            if (turn % 2 == 1)
                row = makeMove(user1, col, height);
            else
                row = makeMove(user2, col, height);

            Cell newCell(row, col, turn);
            if (int direction = checkRow(newCell)) {
                makeSmallCase(newCell, direction);
                return false;
            }

            turn++;
            livingCell++;

            return true;
        }
        return false;
    }

    bool ConnectFourAbstract::play(string command) {
        bool nextTurn = false;
        cout << command << endl;
        if (command.length() == 1) {
            char pos = command.at(0);
            nextTurn = play(pos);

        } else if (command.find("LOAD") == 0) {
            string filename = command.substr(command.find_last_of(" \t") + 1);
            loadGame(filename);

        } else if (command.find("SAVE") == 0) {
            string filename = command.substr(command.find_last_of(" \t") + 1);
            saveGame(filename);
        } else if (command.find("PRINT VARS") == 0) {
            cout << "TableSize = " << height << " " << width
                 << "\nGame Mode " << gameMode
                 << "\nTurn " << turn
                 << "\nMax turn " << maxTurn
                 << "\nLiving Cell " << livingCell << endl;

        } else {
            cout << "Wrong command!\n" << "Usage:\n-[A, " << (char) ('A' + width - 1) << "]"
                 << "\n-LOAD file\n-SAVE file\n";
        }

        printTable();
        if (winner != '?')
            printWinner();

        return nextTurn;
    }

    void ConnectFourAbstract::printTable() {

        cout << endl;

        for (int i = 0; i < width; i++)
            cout << (char) ('A' + i) << ' ';
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << gameCells[i][j].getUser() << ' ';
            }
            cout << endl;
        }

        cout << "Living Cell: " << livingCell << endl;
    }

    bool ConnectFourAbstract::isGameEnded() {
        if (turn >= maxTurn || winner != '?')
            return true;
        return false;
    }

    int ConnectFourAbstract::newGameFromFile(string filename) {
        height = 0;
        width = 0;
        return getBoardFromFile(filename);
    }

    void ConnectFourAbstract::printWinner() {
        if (winner == '?')
            cout << "Tie!" << endl;
        else if (winner == user1)
            cout << "Player 1 won!" << endl;
        else if (winner == user2 && gameMode == 'P')
            cout << "Player 2 won!" << endl;
        else
            cout << "Computer won!" << endl;

    }

    bool ConnectFourAbstract::operator==(ConnectFourAbstract &other) const {

        if (this->width != other.width || this->height != other.height)
            return false;
        if (this->turn != other.turn)
            return false;
        for (int i = 0; i < this->height; i++)
            for (int j = 0; j < this->width; j++)
                if (gameCells[i][j].getUser() != other.gameCells[i][j].getUser())
                    return false;

        return true;
    }

    int ConnectFourAbstract::loadGame(string filename) {
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

            cout << "Game is loaded\n";
            savedFile.close();
        } else {

            cerr << filename << "is missing or broken! (loadGame)\n";
            return -1;
        }

        return 1;
    }

    int ConnectFourAbstract::saveGame(string filename) {
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

            cout << "Game is saved\n";

        } else {

            cerr << filename << "is missing or broken! (saveGame)\n";
            return -1;
        }
        return 0;
    }

    char ConnectFourAbstract::playByComputer() {
        char target = 'A';

        for (int i = 0; i < width; i++)
            if (isMoveLegal(target + i, false))
                return target + i; //column  that will be played by comp.
    }

    char ConnectFourAbstract::playerVsPlayer() {

        if (turn == FIRST_TURN)  //If it is a new game
            cin.ignore();//Ignores '\n', '\t' '

        while (turn <= maxTurn && winner == '?') {
            string command;
            cout << "Pick a target\n";
            getline(cin, command);
            if (command.length() != 0)
                play(command);
            else {
                cout << "EOF! Exitting (-2)\n";
                exit(-2);
            }

        }
    }

    char ConnectFourAbstract::playerVsComputer() {

        string command;
        printTable();
        if (turn == FIRST_TURN)  //If it is a new game
            cin.ignore();//Ignores '\n', '\t' '

        while (turn <= maxTurn && winner == '?') {

            cout << "Pick a target\n";
            getline(cin, command);

            if (play(command))
                play();
        }
        return winner;
    }

    bool ConnectFourAbstract::isPosValid(int row, int pos) {
        if (row >= height || row < 0
            || pos >= width || pos < 0)
            return false;

        return true;
    }

    bool ConnectFourAbstract::isMoveLegal(const char target, bool humanMove) {
        bool status = true;

        //cout << "called func isMovelegal\n";

        if (target < 'A' || target > ('A' + width - 1)) {
            if (humanMove)
                cerr << "Wrong move! Be sure your target column is "
                        "between A and " << (char) ('A' + width - 1) << endl;
            status = false;
        } else {
            int i = 0;
            while (gameCells[i][target - 'A'].getUser() == BLOCKED_CELL)
                i++;

            if (gameCells[i][target - 'A'].getUser() != EMPTY_CELL) {
                if (humanMove)
                    cerr << "Wrong move! Be sure your target column is not complete full.\n";
                status = false;
            }
        }
        return status;
    }

    int ConnectFourAbstract::makeMove(const char user, const int col, int row) {
        if (gameCells[row - 1][col].getUser() != '*')
            return makeMove(user, col, row - 1);
        else
            gameCells[row - 1][col].setUser(user);

        return row - 1;
    }

    void ConnectFourAbstract::getTableSizeFromKeyboard() {
        string input;

        do {
            cout << "\nEnter the table width [4, 25]\n";
            cin >> input;
            width = convertToInt(input);
        } while (width < 4 || width > 25);

        do {
            cout << "\nEnter the table height [4, 25]\n";
            cin >> input;
            height = convertToInt(input);
        } while (height < 4 || height > 25);

        maxTurn = height * width;

    }

    void ConnectFourAbstract::getGameModeFromKeyboard() {
        string input;

        do {
            cout << "\nSelect the game mode\n";
            cout << "P - Player vs Player\n";
            cout << "C - Player vs Computer\n";
            cin.ignore();
            cin >> input;

        } while (input != "P" && input != "C");

        gameMode = input[0];

    }

    int ConnectFourAbstract::getBoardFromFile(string filename) {

        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            char ch;
            string line;
            while (inputFile >> line) {
                height++;
                if (line.length() > width)
                    width = line.length();
            }

            inputFile.clear();
            inputFile.seekg(0, inputFile.beg);

            createTable();

            int currHeight = 0, currWidth = 0;
            while (!inputFile.eof()) {

                inputFile.get(ch);
                if (ch == '\n') {
                    currHeight++;
                    currWidth = 0;
                } else {
                    gameCells[currHeight][currWidth].setUser(ch);
                    currWidth++;
                    if (ch == EMPTY_CELL)
                        maxTurn++;
                }
            }
            inputFile.close();
        } else {

            cerr << filename << " is missing or broken! (getBoardFromFile)\n";
            exit(-1);
        }

        return 1;
    }

    void ConnectFourAbstract::createTable() {

        if (width < MIN_COL || width > MAX_COL) {

            cout << "Invalid width. Be sure width is between "
                 << MIN_COL << "-" << MAX_COL << ". Exitting (-1)\n";
            exit(-1);
        }

        gameCells = new Cell *[height];

        for (int i = 0; i < height; ++i) {
            gameCells[i] = new Cell[width];
        }

    }

    void ConnectFourAbstract::destroyTable() {
        for (int i = 0; i < height; ++i) {
            delete[] gameCells[i];
        }

        delete[] gameCells;

    }

    void ConnectFourAbstract::resetTable() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                gameCells[i][j].setUser(EMPTY_CELL);
            }
        }

    }

    int ConnectFourAbstract::convertToInt(string input) {
        int number = 0;

        for (int i = 0; i < input.length(); i++) {
            if (input.at(i) < '0' || input.at(i) > '9')
                return -2;
            else {
                number = number * 10 + input.at(i) - '0';
            }

        }
    }

    int ConnectFourAbstract::getTurn() const {
        return turn;
    }

    int ConnectFourAbstract::getMaxTurn() const {
        return maxTurn;
    }

    int ConnectFourAbstract::getHeight() const {
        return height;
    }

    int ConnectFourAbstract::getWidth() const {
        return width;
    }

    char ConnectFourAbstract::getWinner() const {
        return winner;
    }

    int ConnectFourAbstract::getCells() const {
        return cells;
    }


    void ConnectFourAbstract::setWinner(char winner) {
        ConnectFourAbstract::winner = winner;
    }


}











