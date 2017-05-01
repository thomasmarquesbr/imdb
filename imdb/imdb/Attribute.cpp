//
//  Attribute.cpp
//  imdb
//
//  Created by Thomás Marques on 22/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Attribute.hpp"

Attribute::Attribute(string name){
    this->name = name;
    this->next = NULL;
    this->primaryKey = false;
}

Attribute::Attribute(string name, bool isPrimaryKey){
    this->name = name;
    this->next = NULL;
    this->primaryKey = isPrimaryKey;
}

string Attribute::getName(){
    return this->name;
}

bool Attribute::isPrimarykey(){
    return this->primaryKey;
}

Attribute* Attribute::getNext(){
    return this->next;
}

void Attribute::setNext(Attribute *attribute){
    this->next = attribute;
}

void Attribute::setPrimaryKey(bool value){
    this->primaryKey = value;
}

void Attribute::clear(){
}
