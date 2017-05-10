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
    bool primaryKey; //determina se o atributo compõe a chave primária
    bool foreignKey;
    string name;
    Attribute *next;
    
    void clear();
public:
    Attribute(string);
    Attribute(string, bool);
    ~Attribute();
    
    bool isPrimarykey();
    string getName();
    Attribute* getNext();
    
    void setNext(Attribute *attribute);
    void setPrimaryKey(bool value);
    void setForeignKey(bool value);
};

#endif /* Attribute_hpp */
