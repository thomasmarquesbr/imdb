//
//  Attribute.cpp
//  imdb
//
//  Created by Thomás Marques on 22/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Attribute.hpp"

/* PRIVATE METHODS */

void Attribute::clear(){
    this->name.clear();
}

/* PUBLIC METHODS */

Attribute::Attribute(string name){
    this->primaryKey = false;
    this->foreignKey = false;
    this->name = name;
    this->next = NULL;
    this->table = NULL;
}

Attribute::Attribute(string name, bool isPrimaryKey){
    this->name = name;
    this->next = NULL;
    this->primaryKey = isPrimaryKey;
}

Attribute::~Attribute(){
    this->clear();
}

bool Attribute::isPrimarykey(){
    return this->primaryKey;
}

bool Attribute::isForeignKey(){
    return this->foreignKey;
}

string Attribute::getName(){
    return this->name;
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

void Attribute::setForeignKey(bool value){
    this->foreignKey = value;
}

void Attribute::setTableReference(Table *table){
    this->table = table;
}

Table* Attribute::getTableReference(){
    return this->table;
}
