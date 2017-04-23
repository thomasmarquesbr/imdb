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

using namespace std;

class Attribute{
private:
    string name;
    bool primaryKey;
    Attribute *next;
    
public:
    Attribute(string);
    Attribute(string, bool);
    string getName();
    bool isPrimarykey();
    Attribute* getNext();
    void setNext(Attribute *attribute);
    void setPrimaryKey(bool value);
    void clear();
};

#endif /* Attribute_hpp */
