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
    Table *table;
    int amountTables;
public:
    Database();
    void addTable(Table *newTable);
    Table* getTable(string name);
    int getAmountTables();
};

#endif /* Database_hpp */
