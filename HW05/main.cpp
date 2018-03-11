#include <iostream>
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourUndo.h"

using namespace std;
using namespace CSE241;

int ConnectFourAbstract::livingCell = 0;

void getInputs(string& gameMode, string& pvpOrPvC, int& width, int& height);
int convertToInt(string number);

int main() {

    string gamemode, pvpOrPvC;
    int width, height;

    getInputs(gamemode, pvpOrPvC, width, height);


    ConnectFourAbstract *cfGame;

    if (gamemode == "D") {
        ConnectFourDiag cfDiag(width, height);
        cfGame = &cfDiag;
    }else if (gamemode == "P") {
        ConnectFourPlus cfPlus(width, height);
        cfGame = &cfPlus;
    } else {
        ConnectFourUndo cfUndo(width, height);
        cfGame = &cfUndo;
    }


    cfGame->setGameMode(pvpOrPvC.at(0));
    cfGame->playGame();

    return 0;

}

void getInputs(string& gameMode, string& pvpOrPvC, int& width, int& height){

    do {
        cout << "Select\n"
                "P - Plus Mode\n"
                "D - Diag Mode\n"
                "U - Undo Mode\n";
        cin >> gameMode;
    } while (gameMode != "D" && gameMode != "P" && gameMode != "U");

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

    do {
        cout << "Select\n"
                "P - PvP\n"
                "C - PvC\n";
        cin >> pvpOrPvC;
    } while (pvpOrPvC != "P" && pvpOrPvC != "C");

    
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