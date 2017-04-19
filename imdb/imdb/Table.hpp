//
//  Table.hpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include <stdio.h>
#include "Element.hpp"

class Table{
private:
    Element *element;
    Table *nextTable;
    string name;
    int amountElements;
public:
    Table(string name);
    string getName();
    void putTable(Table *newTable);
    Element* getElement();
    int getAmountElements();
};

#endif /* Table_hpp */

