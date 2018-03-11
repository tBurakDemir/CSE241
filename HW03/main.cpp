#include <iostream>
#include "ConnectFour.h"
#include <vector>

void multigame(vector <ConnectFour> games);
int convertToInt(string input);

using namespace std;

#define MULTIG 5

int ConnectFour::livingCell = 0;

int main() {

    vector <ConnectFour> games(MULTIG);
    ConnectFour sg, sg2("abc.txt");

    //cout << (bool)sg.compare(sg2);

    string multiOrSingle;
    do {
        cout << "Select\n"
            "M - multigame\n"
            "S - singlegame\n";
     cin >> multiOrSingle;
    }while(multiOrSingle != "M" && multiOrSingle != "S");

    if(multiOrSingle == "S")
        sg.playGame();
    else
        multigame(games);

    return 0;
}


void multigame(vector <ConnectFour> games){

    for (int i = 0; i < MULTIG; ++i) {
        cout << "Object " << i+1  << ": "<< endl;
        games[i].getInputs();
    }
    int objNo = MULTIG;
    string command;
    while(games.size() != 0) {

        do{
            cout << "\n\nChoose an object. [1-"<< MULTIG <<"]"<<endl;
            cin >> command;
        }while((objNo = convertToInt(command)) == -2);
        cin.ignore();
        if(objNo > 0 && objNo <= MULTIG){

            if(games[objNo-1].getGameMode() == 'P'){

                games[objNo-1].printTable();
                for (int i = 0; i < 2; ++i) {
                    if(!(games[objNo-1].isGameEnded())){
                        do{
                            cout << "Pick a target\n";
                            getline(cin, command);
                        }while(!(games[objNo-1].play(command)));

                    }
                    else{
                        cerr << objNo <<". Game is ended. Please select another object.\n";
                        break;
                    }
                }
            }
            else{

                if(!(games[objNo-1].isGameEnded())){
                    string command;
                   do {
                       cout << "Pick a target\n";
                       getline(cin, command);
                   }while(!(games[objNo-1].play(command)));
                    games[objNo-1].play();
                    games[objNo-1].printTable();
                } else{
                    cerr << objNo <<". Game is ended. Please select another object.\n";
                    break;
                }
            }
        }
    }
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