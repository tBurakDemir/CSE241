//
// Created by burak.demir on 26.11.2017.
//

#include "Cell.h"
using namespace CSE241;

Cell::Cell() {
    row = 0;
    column = 0;
}

Cell::Cell(char bt) {
    belongTo = bt;
    Cell();
}

Cell::Cell(int r, int col, char belong) {
    row = r;
    column = col;
    belongTo = belong;
}

Cell::Cell(int r, int col, int t) {
    row = r;
    column = col;
    if(t % 2 == 1)
        belongTo = 'X';
    else
        belongTo = 'O';

}

void Cell::setCell(int r, int c, char b) {
    row = r;
    column = c;
    belongTo = b;
}

Cell &Cell::operator++() {//prefix

    if(this->belongTo == 'X')
        this->belongTo = 'O';
    else if(this->belongTo == 'O')
        this->belongTo = EMPTY_CELL;
    else if(this->belongTo == EMPTY_CELL)
        this->belongTo == 'X';
}

Cell Cell::operator++(int a) {
    Cell temp(this->row, this->column, this->belongTo);
    ++*this;
    return temp;
}

Cell &Cell::operator--() {//prefix

    if(this->belongTo == 'X')
        this->belongTo = EMPTY_CELL;
    else if(this->belongTo == 'O')
        this->belongTo = 'X';
    else if(this->belongTo == EMPTY_CELL)
        this->belongTo == 'O';
}

Cell Cell::operator--(int a) {
    Cell temp(this->row, this->column, this->belongTo);
    --(*this);
    return temp;
}

bool Cell::isEmpty() {return belongTo == '.';}

char Cell::showCell() { return belongTo;}

void Cell::info() {
    std::cout << "row: " << row << std::endl;
    std::cout << "col: " << column << std::endl;
    std::cout << "Cell belong to " << belongTo;
}
