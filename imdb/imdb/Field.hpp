//
//  Field.hpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <stdio.h>
#include <string>

class Field;

using namespace std;

class Field{
private:
    string name;
    string value;
    Field *next;
    
    void clear();
public:
    Field(string, string);
    ~Field();
    
    string getName();
    string getValue();
    Field* getNext();
    
    void setValue(string value);
    void setNext(Field *field);
};

#endif /* Field_hpp */
