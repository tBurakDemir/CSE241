//
// Created by burak.demir on 26.11.2017.
//

#ifndef HW05_CELL_H
#define HW05_CELL_H

#include <iostream>

namespace CSE241 {
#define BLOCKED_CELL ' '
#define EMPTY_CELL '*'


    class Cell {
        int row;
        int column;
        char belongTo;


    public:

        Cell();

        Cell(char bt);

        Cell(int r, int col, char belong = EMPTY_CELL);

        Cell(int r, int col, int t);

        /*Getters*/
        inline int getRow() const { return row; }

        inline int getCol() const { return column; }

        inline char getUser() const { return belongTo; }
        //inline static int getLivingCell()  { return livingCell;}

        /*Setters*/
        //inline void setRow (int row) {row = row;}
        //inline void setCol (int col) {column = col;}
        //inline void setCol (char col) {column = col - 'A';}
        inline void setUser(char p) { belongTo = p; }

        void setCell(int r, int c, char b);

        Cell &operator++();

        Cell operator++(int a);

        Cell &operator--();

        Cell operator--(int a);


        /*Helper Functions*/
        bool isEmpty();

        char showCell();

        void info();

    };
}
#endif //HW05_CELL_H
