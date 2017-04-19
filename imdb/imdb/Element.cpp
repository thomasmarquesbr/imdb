//
//  Element.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include "Element.hpp"

Element::Element(){
    this->field = NULL;
    this->size = 0;
}

Field* Element::getField(){
    return this->field;
}

int Element::getSize(){
    return this->size;
}

Element* Element::getLeftElement(){
    return this->leftElement;
}

Element* Element::getRightElement(){
    return this->rightElement;
}

void Element::clear(){
    
}
