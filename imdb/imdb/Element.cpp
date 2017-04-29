//
//  Element.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include "Element.hpp"

Element::Element(){
    this->height = 0;
    this->balance = EQUAL;
    this->firstField = NULL;
    this->lastField = NULL;
    this->amountFields = 0;
    this->subTreeElement[LEFT] = NULL;
    this->subTreeElement[RIGHT] = NULL;
//    this->leftElement = NULL;
//    this->rightElement = NULL;
}

Element::~Element() {
    this->clear();
}

bool Element::empty(){
    return (firstField == NULL);
}

bool Element::existField(string name){
    if (getField(name) == NULL)
        return false;
    else
        return true;
}

int Element::getAmountFields(){
    return this->amountFields;
}

Field* Element::getFirstField(){
    return this->firstField;
}

Field* Element::getLastField(){
    return this->lastField;
}

Field* Element::getField(string name){
    Field* field = firstField;
    if (!empty()){
        while (field){
            if(field->getName().compare(name) == 0){
                return field;
            } else
                field = field->getNext();
        }
    }
    return field;
}

Element*& Element::getSubTreeElement(int direction) {
    return this->subTreeElement[direction];
}

Element*& Element::getLeftElement(){
    return this->subTreeElement[LEFT];
}

Element*& Element::getRightElement(){
    return this->subTreeElement[RIGHT];
}

void Element::removeField(string name){
    Field* prevField = firstField;
    Field* currField = firstField;
    if (currField->getName().compare(name) == 0){
        firstField = currField->getNext();
        if (firstField == NULL)
            lastField = NULL;
        amountFields--;
    } else {
        while(currField != NULL)
            if(currField->getName().compare(name) != 0){
                prevField = currField;
                currField = currField->getNext();
            } else {
                prevField->setNext(currField->getNext());
                delete currField;
                amountFields--;
                break;
            }
    }
}

int Element::getBalance() {
    return this->balance;
}

void Element::setBalance(unsigned short balance) {
    this->balance = balance;
}

void Element::setSubTreeElement(Element *&element, int direction) {
    this->subTreeElement[direction] = element;
}

void Element::addField(string name, string value) {
    Field* field = getField(name);
    if (field == NULL){//não existe
        Field* newField = new Field(name, value);
        if (empty()) {
            firstField = newField;
            lastField = newField;
        } else {
            lastField->setNext(newField);
            lastField = newField;
        }
        amountFields++;
    } else { //atualiza o valor do campo
        field->setValue(value);
    }
}

void Element::printFields(){
    Field* field = firstField;
    if(empty())
        cout << "Os campos do elemento não existem! \n";
    else{
        while(field) {
            cout << field->getName() << ": " << field->getValue() << endl;
            field = field->getNext();
        }
        cout << endl;
    }
}

void Element::clear(){
    Field *aux = this->firstField;
    while (aux != NULL) {
        firstField = firstField->getNext();
        delete aux;
        aux = firstField;
    }
    lastField = NULL;
}
