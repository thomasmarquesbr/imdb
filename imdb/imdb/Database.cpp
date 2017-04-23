//
//  Database.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include "Database.hpp"
#include "Table.hpp"

Database::Database(){
    this->firstTable = NULL;
    this->lastTable = NULL;
    this->amountTables = 0;
}

bool Database::empty(){
    return (firstTable == NULL);
}

int Database::getAmountTables(){
    return this->amountTables;
}

Table* Database::getFirstTable(){
    return this->firstTable;
}

Table* Database::getLastTable(){
    return this->lastTable;
}

Table* Database::getTable(string name){
    Table* table = firstTable;
    if (!empty()){
        while (table){
            if(table->getName().compare(name) == 0){
                return table;
            } else
                table = table->getNextTable();
        }
    }
    return table;
}

void Database::addTable(Table *newTable){
    Table* table = getTable(newTable->getName());
    if (table == NULL){//não existe
        if (empty()) {
            firstTable = newTable;
            lastTable = newTable;
        } else {
            lastTable->setNextTable(newTable);
            lastTable = newTable;
        }
        amountTables++;
    } else { //ja existe
        cout << "Falha ao criar tabela!"<<endl;
        cout << "A tabela " << newTable->getName() << "ja existe" << endl;
    }
}

void Database::removeTable(string name){
    Table* prevTable = firstTable;
    Table* currTable = firstTable;
    if (currTable->getName().compare(name) == 0){
        firstTable = currTable->getNextTable();
        if (firstTable == NULL)
            lastTable = NULL;
        amountTables--;
    } else {
        while(currTable != NULL)
            if(currTable->getName().compare(name) != 0){
                prevTable = currTable;
                currTable = currTable->getNextTable();
            } else {
                prevTable->setNextTable(currTable->getNextTable());
                delete currTable;
                amountTables--;
                break;
            }
    }
}

void Database::clear(){
    
}
