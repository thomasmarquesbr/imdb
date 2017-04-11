//
//  Field.hpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Field_hpp
#define Field_hpp

#include <stdio.h>
#include <string>

using namespace std;

#endif /* Field_hpp */

class Field{
private:
    string name;
    string value;
    Field *next;
    
public:
    Field(string, string);
    string getName();
    string getValue();
    Field* getNext();
    void clear();
};
