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

enum Direction {
    LEFT  = 0,
    RIGHT = 1,
    EQUAL = 2,
};

class Element{
private:
    int amountFields;
    int height;
    Field *firstField;
    Field *lastField;
    unsigned short balance;
//    Element *leftElement;
//    Element *rightElement;
    Element *subTreeElement[2];
public:
    Element();
    bool empty();
    bool existField(string name);
    int getAmountFields();
    Field* getFirstField();
    Field* getLastField();
    Field* getField(string name);
    Element*& getSubTreeElement(int direction);
    Element*& getLeftElement();
    Element*& getRightElement();
    int getBalance();
    void setSubTreeElement(Element*& element, int direction);
    void setBalance(unsigned short balance);
    void addField(string name, string value);
    void removeField(string name);
    void printFields();
    void clear();
};

#endif /* Element_hpp */
