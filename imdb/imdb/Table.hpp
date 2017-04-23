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
#include "Attribute.hpp"

class Table{
private:
    string name;
    int amountElements;
    Attribute *firstAttribute;
    Attribute *lastAttribute;
    Element *firstElement;
    Table *nextTable;
public:
    Table(string name);
    bool empty();
    bool validateAttributes(Attribute *attribute);
    int getAmountElements();
    string getName();
    Element* getFirstElement();
    Table* getNextTable();
    void addAttribute(string name);
    void setNextTable(Table *newTable);
    void printAttributes();
    void clear();
};

#endif /* Table_hpp */

