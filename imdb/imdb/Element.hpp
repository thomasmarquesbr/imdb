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
    Field *field;
    int size;
    Element *leftElement;
    Element *rightElement;
public:
    Element();
    Field* getField();
    int getSize();
    Element* getLeftElement();
    Element* getRightElement();
    void clear();
};

#endif /* Element_hpp */
