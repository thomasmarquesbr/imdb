//
//  Table.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include "Table.hpp"

Table::Table(string name){
    this->name = name;
    this->firstAttribute = NULL;
    this->lastAttribute = NULL;
    this->firstElement = NULL;
    this->amountElements = 0;
    this->nextTable = NULL;
}

bool Table::empty(){
    return (firstElement == NULL);
}

bool Table::validateAttributes(Attribute *attribute){
    Attribute *aux = this->firstAttribute;
    Attribute *testAttribute = attribute;
    while(testAttribute){
        while (aux) {
            if (aux->getName().compare(testAttribute->getName()) != 0){
                aux = aux->getNext();
                if (aux == NULL)
                    return false;
            } else {
                testAttribute = testAttribute->getNext();
            }
        }
    }
    return true;
}

int Table::getAmountElements(){
    return this->amountElements;
}

string Table::getName(){
    return this->name;
}

Element* Table::getFirstElement(){
    return this->firstElement;
}

Table* Table::getNextTable(){
    return this->nextTable;
}

void Table::addAttribute(string name){
    Attribute *newAttribute = new Attribute(name);
    if (this->firstAttribute == NULL) {
        firstAttribute = newAttribute;
        lastAttribute = newAttribute;
    } else {
        lastAttribute->setNext(newAttribute);
        lastAttribute = newAttribute;
    }
}

void Table::setNextTable(Table *newTable){
    this->nextTable = newTable;
}

void Table::printAttributes(){
    Attribute *aux = this->firstAttribute;
    if (aux != NULL) {
        cout << "Atributos: ";
        while (aux) {
            cout << aux->getName() << ", ";
            aux = aux->getNext();
        }
        cout<<endl;
    } else
        cout << "Não existem atributos na tabela " << this->getName() << endl;
            
}
