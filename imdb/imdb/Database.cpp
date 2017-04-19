//
//  Database.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Database.hpp"

Database::Database(){
    this->table = NULL;
    this->amountTables = 0;
}

void Database::addTable(Table *newTable){
    this->table->putTable(newTable);
    this->amountTables++;
}

Table* Database::getTable(string name){
    return this->table;
}

int Database::getAmountTables(){
    return this->amountTables;
}
