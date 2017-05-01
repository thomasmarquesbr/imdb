//
//  Element.hpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include <stdio.h>
#include "Field.hpp"
#include "Attribute.hpp"

enum Direction {
    LEFT  = 0,
    RIGHT = 1,
    EQUAL = 2,
};

class Element{
private:
    unsigned short balance;
    int amountFields;
    int height;
    string key;
    Field *firstField;
    Field *lastField;
    Element *subTreeElement[2];
    
    void clear();
public:
    Element();
    ~Element();
    
    bool empty();
    bool existField(string name);
    int getBalance();
    int getAmountFields();
    string getKey();
    Field* getFirstField();
    Field* getLastField();
    Field* getField(string name);
    Element*& getSubTreeElement(int direction);
    Element*& getLeftElement();
    Element*& getRightElement();
    
    void setPrimaryKey(Attribute *attrib);
    void setSubTreeElement(Element*& element, int direction);
    void setBalance(unsigned short balance);
    void addField(string name, string value);
    void removeField(string name);
    void printFields();
};

#endif /* Element_hpp */
