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

using namespace std;

class Field{
private:
    string name;
    string value;
    Field *next;
    
public:
    Field(string, string);
    string getName();
    string getValue();
    int getValueInt();
    Field* getNext();
    void setValue(string value);
    void setNext(Field *field);
    void clear();
};

#endif /* Field_hpp */
