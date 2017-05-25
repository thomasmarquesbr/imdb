//
//  Attribute.hpp
//  imdb
//
//  Created by Thomás Marques on 22/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Attribute_hpp
#define Attribute_hpp

#include <stdio.h>
#include <string>

class Attribute;

#include "Table.hpp"

using namespace std;

class Attribute{
private:
    bool primaryKey; //determina se o atributo compõe a chave primária
    bool foreignKey;
    string name;
    Attribute *next;
    Table *table;
    
    void clear();
public:
    Attribute(string);
    Attribute(string, bool);
    ~Attribute();
    
    bool isPrimarykey();
    bool isForeignKey();
    string getName();
    Attribute* getNext();
    
    void setNext(Attribute *attribute);
    void setPrimaryKey(bool value);
    void setForeignKey(bool value);
    void setTableReference(Table* table);
    
    Table* getTableReference();
};

#endif /* Attribute_hpp */
