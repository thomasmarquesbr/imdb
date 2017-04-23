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

class Element{
private:
    int amountFields;
    Field *firstField;
    Field *lastField;
    Element *leftElement;
    Element *rightElement;
public:
    Element();
    bool empty();
    bool existField(string name);
    int getAmountFields();
    Field* getFirstField();
    Field* getLastField();
    Field* getField(string name);
    Element* getLeftElement();
    Element* getRightElement();
    void addField(string name, string value);
    void removeField(string name);
    void printFields();
    void clear();
};

#endif /* Element_hpp */
