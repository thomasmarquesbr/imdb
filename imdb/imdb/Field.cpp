//
//  Field.cpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Field.hpp"

Field::Field(string name, string value){
    this->name = name;
    this->value = value;
    this->next = NULL;
}

string Field::getName(){
    return this->name;
}

string Field::getValue(){
    return this->value;
}

Field* Field::getNext(){
    return this->next;
}

void Field::clear(){
    
}

