//
//  Element.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include <string>
#include "Element.hpp"

/* PRIVATE METHODS */

void Element::clear(){
    Field *aux = this->firstField;
    while (aux != NULL) {
        this->key.clear();
        firstField = firstField->getNext();
//        delete aux;
        aux = firstField;
    }
    lastField = NULL;
}

/* PUBLIC METHODS */

Element::Element(){
    this->balance = EQUAL;
    this->key = "";
    this->mustPrint = true;
    this->firstField = NULL;
    this->lastField = NULL;
    this->amountFields = 0;
    this->subTreeElement[LEFT] = NULL;
    this->subTreeElement[RIGHT] = NULL;
}

Element::~Element(){
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

bool Element::getMustPrint(){
    return this->mustPrint;
}

void Element::setMustPrint(bool value){
    this->mustPrint = value;
}

int Element::getBalance(){
    return this->balance;
}

int Element::getAmountFields(){
    return this->amountFields;
}

string Element::getKey(){
    return this->key;
}

Field* Element::getFirstField(){
    return this->firstField;
}

Field* Element::getLastField(){
    return this->lastField;
}

Field* Element::getField(string name){ //percorre os campos até encontrar o Field, se não existir retorna NULL
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

void Element::substituteElement(Element *newElement){
    this->amountFields = newElement->getAmountFields();
    this->key = newElement->getKey();
    this->firstField = newElement->getFirstField();
    this->lastField = newElement->getLastField();
}

Element*& Element::getSubTreeElement(int direction){
    return this->subTreeElement[direction];
}

Element*& Element::getLeftElement(){
    return this->subTreeElement[LEFT];
}

Element*& Element::getRightElement(){
    return this->subTreeElement[RIGHT];
}

void Element::setPrimaryKey(Attribute *attrib){//concatena os campos que compõem a primary key
    this->key = "";
    Attribute *auxAttrib = attrib;
    while(auxAttrib != NULL){
        if((auxAttrib->isPrimarykey()) && (this->getField(auxAttrib->getName()) != NULL))
            this->key += this->getField(auxAttrib->getName())->getValue();
        auxAttrib = auxAttrib->getNext();
    }
}

void Element::setSubTreeElement(Element *&element, int direction){
    this->subTreeElement[direction] = element;
}

void Element::setBalance(unsigned short balance){
    this->balance = balance;
}

void Element::addField(string name, string value){
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

void Element::printFields(){
    Field* field = firstField;
    if(empty())
        cout << "       Os campos do elemento não existem! \n";
    else{
        cout << "       Chave primária: " << this->key << endl;
        while(field) {
            cout << "       "+ field->getName() << ": " << field->getValue() << endl;
            field = field->getNext();
        }
        cout << endl;
    }
}

void Element::printFieldsInLine(){
    Field *field = firstField;
    cout << "       ";
    if (empty())
        cout << "Os campos do elemento não existem! \n";
    else {
        while (field){
            cout << field->getValue() << "      ";
            field = field->getNext();
        }
    }
}

string Element::getFieldsInLine(){
    Field *field = firstField;
    string line = "       ";
    if (!empty()){
        while (field){
            line += field->getValue() + "      ";
            field = field->getNext();
        }
    }
    return line;
}
