//
//  Table.cpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Table.hpp"

Table::Table(){
    this->element = NULL;
    this->size = 0;
}

Element* Table::getElement(){
    return this->element;
}

int Table::getSize(){
    return this->size;
}

