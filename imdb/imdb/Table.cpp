//
//  Table.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Table.hpp"

Table::Table(string name){
    this->name = name;
    this->element = NULL;
    this->amountElements = 0;
    this->nextTable = NULL;
}

string Table::getName(){
    return this->name;
}

void Table::putTable(Table *newTable){
    if (this->nextTable == NULL)
        this->nextTable = newTable;
    else
        this->nextTable->putTable(nextTable);
}

Element* Table::getElement(){
    return this->element;
}

int Table::getAmountElements(){
    return this->amountElements;
}
