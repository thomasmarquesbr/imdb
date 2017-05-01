//
//  Table.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include "Table.hpp"

/* PRIVATE METHODS */

Direction Table::getOpposite(Direction direction){
    return (direction == RIGHT) ? LEFT : RIGHT;
}

void Table::singleRotation(Element *&element, Direction direction){
    int opposite = this->getOpposite(direction);
    Element* child = element->getSubTreeElement(direction);
    element->setSubTreeElement(child->getSubTreeElement(opposite), direction);
    child->setSubTreeElement(element, opposite);
    element = child;
}

void Table::doubleRotation(Element *&element, Direction direction){
    int opposite = this->getOpposite(direction);
    Element* child = element->getSubTreeElement(direction)->getSubTreeElement(opposite);
    element->getSubTreeElement(direction)->setSubTreeElement(child->getSubTreeElement(direction), opposite);
    child->setSubTreeElement(element->getSubTreeElement(direction), direction);
    element->setSubTreeElement(child, direction);
    child = element->getSubTreeElement(direction);
    element->setSubTreeElement(child->getSubTreeElement(opposite), direction);
    child->setSubTreeElement(element, opposite);
    element = child;
}

void Table::rebalanceInsert(Element*& element, Direction direction, bool& heightChanged){
    int opposite = this->getOpposite(direction);
    if (element->getBalance() == direction) {
        if (element->getSubTreeElement(direction)->getBalance() == direction) {
            element->getSubTreeElement(direction)->setBalance(2);
            element->setBalance(EQUAL);
            singleRotation(element, direction);
        } else {
            updateBalance(element, direction);
            doubleRotation(element, direction);
        }
        heightChanged = false;
    } else if (element->getBalance() == opposite) {
        element->setBalance(2);
        heightChanged = false;
    } else {
        element->setBalance(direction);
    }
}

void Table::updateBalance(Element* element, Direction direction){
    int opposite = this->getOpposite(direction);
    int bal = element->getSubTreeElement(direction)->getSubTreeElement(opposite)->getBalance();
    if (bal == direction) {
        element->setBalance(EQUAL);
        element->getSubTreeElement(direction)->setBalance(opposite);
    } else if (bal == opposite) {
        element->setBalance(direction);
        element->getSubTreeElement(direction)->setBalance(EQUAL);
    } else {
        element->setBalance(EQUAL);
        element->getSubTreeElement(direction)->setBalance(EQUAL);
    }
    element->getSubTreeElement(direction)->getSubTreeElement(opposite)->setBalance(EQUAL);
}

void Table::addElement(Element *newElement, Element*& currentElement, bool& heightChanged){
    if (currentElement == NULL) {
        currentElement = newElement;
        heightChanged = true;
        this->amountElements++;
    } else if (currentElement->getKey().compare(
                                                newElement->getKey()) == 0) { //já existe
        cout << "Elemento " << currentElement->getKey() << " ja existe na tabela " << this->getName();
        return;
    } else {
        Direction direction = (newElement->getKey().compare(
                                                            currentElement->getKey()) > 0) ? RIGHT : LEFT;
        heightChanged = false;
        addElement(newElement, currentElement->getSubTreeElement(direction), heightChanged);
        if (heightChanged) {
            rebalanceInsert(currentElement, direction, heightChanged);
        }
    }
}

//void Table::applyPrimaryKeyInElements(Element *element){
//    if (element == NULL) return;
//    element->setPrimaryKey(this->firstAttribute);
//    if (element->getLeftElement() != NULL) applyPrimaryKeyInElements(element->getLeftElement());
//    if (element->getRightElement() != NULL) applyPrimaryKeyInElements(element->getRightElement());
//}

void Table::readPreOrdem(Element*& node){
    if (node == NULL) return;
    cout << node->getKey() << ", ";
    if (node->getLeftElement() != NULL) readPreOrdem(node->getLeftElement());
    if (node->getRightElement() != NULL) readPreOrdem(node->getRightElement());
}

void Table::readInOrdem(Element*& node){
    if (node == NULL) return;
    if (node->getLeftElement() != NULL) readInOrdem(node->getLeftElement());
    cout << node->getKey() << ", ";
    if (node->getRightElement() != NULL) readInOrdem(node->getRightElement());
}

void Table::readPosOrdem(Element*& node){
    if (node == NULL) return;
    if (node->getLeftElement() != NULL) readPosOrdem(node->getLeftElement());
    if (node->getRightElement() != NULL) readPosOrdem(node->getRightElement());
    cout << node->getKey() << ", ";
}

void Table::drawTree(Element *element, int spaces){
    int i;
    if( element != NULL ) {
        drawTree( element->getRightElement(), spaces + 3 );
        for( i = 0; i < spaces; i++ )
            cout <<' ';
        cout << element->getKey() << endl;
        drawTree( element->getLeftElement(), spaces + 3 );
    }
}

void Table::clear(){
    Attribute *aux = this->firstAttribute;
    while (aux != NULL) {
        firstAttribute = firstAttribute->getNext();
        delete aux;
        aux = firstAttribute;
    }
    lastAttribute = NULL;
    
    delete rootElement;
    this->rootElement = NULL;
}

/* PUBLIC METHODS */

Table::Table(string name){
    this->name = name;
    this->firstAttribute = NULL;
    this->lastAttribute = NULL;
    this->rootElement = NULL;
    this->amountElements = 0;
    this->nextTable = NULL;
}

Table::~Table() {
    this->clear();
}

bool Table::empty(){
    return (rootElement == NULL);
}

bool Table::validateAttributes(vector<string> *attributes){
    Attribute *aux = this->firstAttribute;
    vector<string>::iterator attrib = attributes->begin();
    while (aux) {
        if (aux->getName() == *attrib) {
            aux = this->firstAttribute;
            attrib++;
        } else
            aux = aux->getNext();
    }
    if (attrib == attributes->end())
        return true;
    else {
        cout << "       O atributo \"" << *attrib << "\" não existe na tabela \"" << this->name << "\"." << endl;
        return false;
    }
    return true;
}

bool Table::existPrimaryKey(){
    Attribute *aux = this->firstAttribute;
    while (aux) {
        if (aux->isPrimarykey())
            return true;
        aux = aux->getNext();
    }
    return false;
}

int Table::getAmountElements(){
    return this->amountElements;
}

string Table::getName(){
    return this->name;
}

Attribute* Table::getFirstAttribute() {
    return this->firstAttribute;
}

Element* Table::getRootElement(){
    return this->rootElement;
}

Element* Table::findElement(string key) {
    Element* current = this->rootElement;
    while (current != NULL) {
        if (key.compare(current->getKey()) > 0) {
            current = current->getSubTreeElement(RIGHT);
        } else if (key.compare(current->getKey()) < 0) {
            current = current->getSubTreeElement(LEFT);
        } else {
            return current;
        }
    }
    return NULL;
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

void Table::addAttribute(string name, bool isPrimaryKey){
    Attribute *newAttribute = new Attribute(name, isPrimaryKey);
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
        cout << "       Atributos: ";
        while (aux) {
            cout << aux->getName() << ((aux->isPrimarykey()) ? " PK, " : ", ");
            aux = aux->getNext();
        }
        cout<<endl;
    } else
        cout << "Não existem atributos na tabela " << this->getName() << endl;
}

void Table::applyPrimaryKey(vector<string> attribs){
    Attribute *aux = this->firstAttribute;
    vector<string>::iterator attrib = attribs.begin();
    while (aux) {
        if (aux->getName() == *attrib) {
            aux->setPrimaryKey(true);
            aux = this->firstAttribute;
            attrib++;
        } else
            aux = aux->getNext();
    }
    if (attrib != attribs.end())
        cout << "       O atributo \"" << *attrib << "\" não existe na tabela \"" << this->name << "\"." << endl;
}

void Table::addElement(Element *newElement){
    bool heightChanged = false;
    this->addElement(newElement, this->rootElement, heightChanged);
}

void Table::printElementsPreOrdem(){
    cout << endl << "       ";
    if (this->rootElement != NULL)
        readPreOrdem(this->rootElement);
    else
        cout << "Tabela vazia.";
    cout << endl;
}

void Table::printElementsInOrdem(){
    cout << endl << "       ";
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "Tabela vazia";
    cout << endl;
}

void Table::printElementsPosOrdem(){
    cout << endl << "       ";
    if (this->rootElement != NULL)
        readPosOrdem(this->rootElement);
    else
        cout << "Tabela vazia";
    cout << endl;
}

void Table::drawTree(){
    drawTree(this->rootElement, 0);
}











