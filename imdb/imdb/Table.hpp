//
//  Table.hpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include <stdio.h>
#include "Element.hpp"
#include "Attribute.hpp"

class Table{
private:
    string name;
    int amountElements;
    Attribute *firstAttribute;
    Attribute *lastAttribute;
    Element *rootElement;
    Table *nextTable;
    
    inline Direction getOpposite(Direction direction);
    void singleRotation(Element*& element, Direction direction);
    void doubleRotation(Element*& element, Direction direction);
    void rebalanceInsert(Element*& element, Direction direction, bool& heightChanged);
    void rebalanceRemove(Element*& element, Direction direction, bool& heightChanged);
    void updateBalance(Element* element, Direction direction);
    void addElement(Element *newElement, Element*& currentElement, bool& heightChanged);
    bool removeElement(const string& key, Element*& currentElement, bool& heightChanged);
    void readPreOrdem(Element*& node);
    void readInOrdem(Element*& node);
    void readPosOrdem(Element*& node);
    void drawTree(Element* element, int spaces);
public:
    Table(string name);
    bool empty();
    bool validateAttributes(Attribute *attribute);
    int getAmountElements();
    string getName();
    Element* getRootElement();
    Table* getNextTable();
    void addAttribute(string name);
    void setNextTable(Table *newTable);
    void printAttributes();
    void clear();
    
    void addElement(Element *newElement);
    bool removeElement(string key);
    Element* findElement(string key);
    
    void printElementsPreOrdem();
    void printElementsInOrdem();
    void printElementsPosOrdem();
    void drawTree();
};

#endif /* Table_hpp */

