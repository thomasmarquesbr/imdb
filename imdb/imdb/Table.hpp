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
    void updateBalance(Element* element, Direction direction);
    void addElement(Element *newElement, Element*& currentElement, bool& heightChanged);
    void applyPrimaryKeyInElements(Element *element);
    void readPreOrdem(Element*& node);
    void readInOrdem(Element*& node);
    void readPosOrdem(Element*& node);
    void drawTree(Element* element, int spaces);
    void clear();
    
public:
    Table(string name);
    ~Table();
    
    bool empty();
    bool validateAttributes(vector<string> *attributes);
    bool existPrimaryKey();
    int getAmountElements();
    string getName();
    Attribute* getFirstAttribute();
    Element* getRootElement();
    Element* findElement(string key);
    Table* getNextTable();
    
    void addAttribute(string name);
    void addAttribute(string name, bool isPrimaryKey);
    void setNextTable(Table *newTable);
    void printAttributes();
    void applyPrimaryKey(vector<string> attribs);
    void addElement(Element *newElement);
    void printElementsPreOrdem();
    void printElementsInOrdem();
    void printElementsPosOrdem();
    void drawTree();
};

#endif /* Table_hpp */

