//
//  Element.hpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include <stdio.h>
#include "Field.hpp"


#endif /* Element_hpp */

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
