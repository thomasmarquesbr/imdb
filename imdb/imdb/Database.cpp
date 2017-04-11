//
//  Database.cpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Database.hpp"

Database::Database(){
    this->table = NULL;
    this->size = 0;
}

Table* Database::getTable(){
    return this->table;
}

int Table::getSize(){
    return this->size;
}
