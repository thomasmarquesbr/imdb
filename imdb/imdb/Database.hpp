//
//  Database.hpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include "Table.hpp"

class Database{
private:
    Table *firstTable;
    Table *lastTable;
    int amountTables;
public:
    Database();
    bool empty();
    int getAmountTables();
    Table* getFirstTable();
    Table* getLastTable();
    Table* getTable(string name);
    void addTable(Table *newTable);
    void removeTable(string name);
    void clear();
};

#endif /* Database_hpp */
