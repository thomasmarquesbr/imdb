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
#include "Table.hpp"

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

Element* Table::getRootElement(){
    return this->rootElement;
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

Attribute* Table::getFirstAttribute() {
    return this->firstAttribute;
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

Direction Table::getOpposite(Direction direction) {
    return (direction == RIGHT) ? LEFT : RIGHT;
}

void Table::singleRotation(Element *&element, Direction direction) {
    int opposite = this->getOpposite(direction);
    Element* child = element->getSubTreeElement(direction);
    element->setSubTreeElement(child->getSubTreeElement(opposite), direction);
    child->setSubTreeElement(element, opposite);
    element = child;
}

void Table::doubleRotation(Element *&element, Direction direction) {
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

void Table::rebalanceRemove(Element*& element, Direction direction, bool& heightChanged) {
    Direction opposite = this->getOpposite(direction);
    if (element->getBalance() == direction) {
        element->setBalance(EQUAL);
    } else if (element->getBalance() == opposite) {
        if (element->getSubTreeElement(opposite)->getBalance() == opposite) {
            element->getSubTreeElement(opposite)->setBalance(EQUAL);
            element->setBalance(EQUAL);
            singleRotation(element, opposite);
        } else if (element->getSubTreeElement(opposite)->getBalance() == EQUAL) {
            element->getSubTreeElement(opposite)->setBalance(direction);
            singleRotation(element, opposite);
        } else {
            updateBalance(element, opposite);
            doubleRotation(element, opposite);
        }
        heightChanged = false;
    } else {
        element->setBalance(opposite);
        heightChanged = false;
    }
}

void Table::updateBalance(Element* element, Direction direction) {
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

void Table::addElement(Element *newElement){
    bool heightChanged = false;
    this->addElement(newElement, this->rootElement, heightChanged);
}

void Table::addElement(Element *newElement, Element*& currentElement, bool& heightChanged){
    if (currentElement == NULL) {
        currentElement = newElement;
        heightChanged = true;
        this->amountElements++;
//    } else if (currentElement->getFirstField()->getValueInt() == newElement->getFirstField()->getValueInt()) { //já existe
    } else if (currentElement->getFirstField()->getValue().compare(
                        newElement->getFirstField()->getValue()) == 0) { //já existe
        cout << "Elemento " << currentElement->getFirstField()->getValue() << " ja existe na tabela " << this->getName();
        return;
    } else {
//        Direction direction = (newElement->getFirstField()->getValueInt() >
//                                    currentElement->getFirstField()->getValueInt()) ? RIGHT : LEFT;
        Direction direction = (newElement->getFirstField()->getValue().compare(
                                    currentElement->getFirstField()->getValue()) > 0) ? RIGHT : LEFT;
        heightChanged = false;
        addElement(newElement, currentElement->getSubTreeElement(direction), heightChanged);
        if (heightChanged) {
            rebalanceInsert(currentElement, direction, heightChanged);
        }
    }
}

bool Table::removeElement(string key) {
    bool heightChanged = false;
    return this->removeElement(key, this->rootElement, heightChanged);
}

bool Table::removeElement(const string &key, Element *&currentElement, bool &heightChanged) {
    bool success = false;
    if (currentElement == NULL) {
        heightChanged = false;
        return false;
    } else if (key.compare(currentElement->getFirstField()->getValue()) == 0) {
        if (currentElement->getLeftElement() != NULL && currentElement->getRightElement() != NULL ) {
            Element* substitute = currentElement->getLeftElement();
            while (substitute->getRightElement() != NULL) {
                substitute = substitute->getRightElement();
            }
            substitute->setSubTreeElement(currentElement->getRightElement(), RIGHT);
            currentElement = substitute;
//            success = removeElement(currentElement->getFirstField()->getValue(), currentElement->getLeftElement(), heightChanged);
            if (heightChanged) {
                rebalanceRemove(currentElement, LEFT, heightChanged);
            }
        } else {
            Element* temp = currentElement;
            Direction direction = (currentElement->getLeftElement() == NULL) ? RIGHT : LEFT;
            currentElement = currentElement->getSubTreeElement(direction);
            temp->getLeftElement() = NULL;
            temp->getRightElement() = NULL;
            heightChanged = true;
        }
        return true;
    } else {
        Direction direction = (key.compare(currentElement->getFirstField()->getValue()) > 0) ? RIGHT : LEFT;
        if (currentElement->getSubTreeElement(direction) != NULL) {
            success = this->removeElement(key, currentElement->getSubTreeElement(direction), heightChanged);
        } else {
            heightChanged = false;
            return false;
        }
        if (heightChanged) {
            this->rebalanceRemove(currentElement, direction, heightChanged);
        }
        return success;
    }
}

Element* Table::findElement(string key) {
//    int iKey = key[0] * pow(10, key.length()-1) + strtol(key.c_str()+1, NULL, 10);
    Element* current = this->rootElement;
    while (current != NULL) {
//        if (iKey > current->getFirstField()->getValueInt()) {
        if (key.compare(current->getFirstField()->getValue()) > 0) {
            current = current->getSubTreeElement(RIGHT);
//        } else if (iKey < current->getFirstField()->getValueInt()) {
        } else if (key.compare(current->getFirstField()->getValue()) < 0) {
            current = current->getSubTreeElement(LEFT);
        } else {
            return current;
        }
    }
    return NULL;
}

void Table::printElementsPreOrdem(){
    cout << "       ";
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "       Tabela vazia.";
    cout << endl;
}

void Table::readPreOrdem(Element*& node){
    if (node == NULL) return;
    cout << node->getFirstField()->getValue() << ", ";
    if (node->getLeftElement() != NULL) readInOrdem(node->getLeftElement());
    if (node->getRightElement() != NULL) readInOrdem(node->getRightElement());
}

void Table::printElementsInOrdem(){
    cout << "       ";
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "       Tabela vazia";
    cout << endl;
}

void Table::readInOrdem(Element*& node) {
    if (node == NULL) return;
    if (node->getLeftElement() != NULL) readInOrdem(node->getLeftElement());
    cout << node->getFirstField()->getValue() << ", ";
    if (node->getRightElement() != NULL) readInOrdem(node->getRightElement());
}

void Table::printElementsPosOrdem() {
    cout << "       ";
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "       Tabela vazia";
    cout << endl;
}

void Table::readPosOrdem(Element*& node) {
    if (node == NULL) return;
    if (node->getLeftElement() != NULL) readInOrdem(node->getLeftElement());
    if (node->getRightElement() != NULL) readInOrdem(node->getRightElement());
    cout << node->getFirstField()->getValue() << ", ";
}

void Table::drawTree() {
    drawTree(this->rootElement, 0);
}

void Table::drawTree(Element *element, int spaces){
    int i;
    if( element != NULL ) {
        drawTree( element->getRightElement(), spaces + 3 );
        for( i = 0; i < spaces; i++ )
            cout <<' ';
        cout << element->getFirstField()->getValue() << endl;
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











