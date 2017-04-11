//
//  Database.hpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include "Table.hpp"

#endif /* Database_hpp */

class Database{
private:
    Table* table;
    int size;
public:
    Database();
    Table* getTable();
    int getSize();
};
