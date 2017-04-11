//
//  Table.hpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include <stdio.h>
#include "Element.hpp"

#endif /* Table_hpp */

class Table{
private:
    Element *element;
    int size;
public:
    Table();
    Element* getElement();
    int getSize();
};
