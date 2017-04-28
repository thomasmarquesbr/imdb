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
    this->rootElement = NULL;
    this->amountElements = 0;
    this->nextTable = NULL;
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
    element->setSubTreeElement(child->getSubTreeElement(direction), opposite);
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
    } else if (currentElement->getFirstField()->getValue().compare(
                    newElement->getFirstField()->getValue()) == 0) { //já existe
        cout << "Elemento " << currentElement->getFirstField()->getValue() << " ja existe na tabela " << this->getName();
        return;
    } else {
        Direction direction = (currentElement->getFirstField()->getValue().compare(
                                newElement->getFirstField()->getValue()) < 0) ? RIGHT : LEFT;
        heightChanged = false;
        addElement(newElement, currentElement->getSubTreeElement(direction), heightChanged);
        if (heightChanged) {
            rebalanceInsert(currentElement, direction, heightChanged);
        }
    }
}

void Table::removeElement(string key) {
    
}

Element* Table::findElement(string key) {
    Element* current = this->rootElement;
    while (current != NULL) {
        if (key.compare(current->getFirstField()->getValue()) > 0) {
            current = current->getSubTreeElement(RIGHT);
        } else if (key.compare(current->getFirstField()->getValue()) < 0) {
            current = current->getSubTreeElement(LEFT);
        } else {
            return current;
        }
    }
    return NULL;
}

void Table::printElementsPreOrdem(){
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "tabela vazia";
    cout << endl;
}

void Table::readPreOrdem(Element*& node){
    if (node == NULL) return;
    cout << node->getFirstField()->getValue() << ", ";
    if (node->getLeftElement() != NULL) readInOrdem(node->getLeftElement());
    if (node->getRightElement() != NULL) readInOrdem(node->getRightElement());
}

void Table::printElementsInOrdem(){
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "tabela vazia";
    cout << endl;
}

void Table::readInOrdem(Element*& node) {
    if (node == NULL) return;
    if (node->getLeftElement() != NULL) readInOrdem(node->getLeftElement());
    cout << node->getFirstField()->getValue() << ", ";
    if (node->getRightElement() != NULL) readInOrdem(node->getRightElement());
}

void Table::printElementsPosOrdem() {
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "tabela vazia";
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











