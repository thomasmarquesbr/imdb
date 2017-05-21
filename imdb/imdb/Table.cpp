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
#include "time.h"
#include "Table.hpp"
#include "Database.hpp"
#include "Util.hpp"

/* PRIVATE METHODS */

Direction Table::getOpposite(Direction direction){
    return (direction == RIGHT) ? LEFT : RIGHT;
}

void Table::singleRotation(Element *&element, Direction direction){ //executa a rotação simples na direção passada por parâmetro
    int opposite = this->getOpposite(direction);
    Element* child = element->getSubTreeElement(direction);
    element->setSubTreeElement(child->getSubTreeElement(opposite), direction);
    child->setSubTreeElement(element, opposite);
    element = child;
}

void Table::doubleRotation(Element *&element, Direction direction){ //executa a rotação dupla na direção passada por parâmetro
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

void Table::rebalanceInsert(Element*& element, Direction direction, bool& heightChanged){ //rebalanceia a subárvore após a inserção de um elemento
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

void Table::rebalanceRemove(Element*& element, Direction direction, bool& hChanged){
    Direction opposite = this->getOpposite(direction);
    if (element->getBalance() == direction){
        element->setBalance(EQUAL);
    } else if (element->getBalance() == opposite) {
        if (element->getSubTreeElement(opposite)->getBalance() == opposite){
            element->getSubTreeElement(opposite)->setBalance(EQUAL);
            element->setBalance(EQUAL);
            singleRotation(element, opposite);
        } else if (element->getSubTreeElement(opposite)->getBalance() == EQUAL){
            element->getSubTreeElement(opposite)->setBalance(direction);
            singleRotation(element, opposite);
        } else {
            updateBalance(element, opposite);
            doubleRotation(element, opposite);
        }
        hChanged = false;
    } else {
        element->setBalance(opposite);
        hChanged = false;
    }
}

void Table::updateBalance(Element* element, Direction direction){ //atualiza o fator de balanceamento após uma operação na subárvore
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

void Table::addElement(Element *newElement, Element*& currentElement, bool& heightChanged){ //insere o elemento subárvore, recursivamente
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

bool Table::removeElement(const string& key, Element*& element, bool& heightChanged){
    bool success = false;
    if (element == NULL){
        heightChanged = false;
        return false;
    }
    else if (key.compare(element->getKey()) == 0){
        if (element->getSubTreeElement(LEFT) != NULL && element->getSubTreeElement(RIGHT) != NULL ){
            Element* substitute = element->getSubTreeElement(LEFT);
            while (substitute->getSubTreeElement(RIGHT) != NULL){
                substitute = substitute->getSubTreeElement(RIGHT);
            }
            element->substituteElement(substitute);
            success = removeElement(element->getKey(), element->getSubTreeElement(LEFT), heightChanged);
            if (heightChanged){
                rebalanceRemove(element, LEFT, heightChanged);
            }
        } else {
            Element* temp = element;
            Direction direction = (element->getSubTreeElement(LEFT) == NULL) ? RIGHT : LEFT;
            element = element->getSubTreeElement(direction);
            temp->getSubTreeElement(LEFT) = NULL;
            temp->getSubTreeElement(RIGHT) = NULL;
            delete temp;
            heightChanged = true;
        }
        return true;
    } else {
        Direction direction = (key.compare(element->getKey()) > 0) ? RIGHT : LEFT;
        if (element->getSubTreeElement(direction) != NULL){
            success = this->removeElement(key, element->getSubTreeElement(direction), heightChanged);
        } else {
            heightChanged = false;
            return false;
        }
        if (heightChanged) {
            this->rebalanceRemove(element, direction, heightChanged);
        }
        return success;
    }
}

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

void Table::drawTree(Element *element, int spaces){ //desenha a subárvore no console, recursivamente
    int i;
    if( element != NULL ) {
        drawTree( element->getRightElement(), spaces + 3 );
        for( i = 0; i < spaces; i++ )
            cout <<' ';
        cout << element->getKey() << endl;
        drawTree( element->getLeftElement(), spaces + 3 );
    }
}

void Table::countElements(Field *field, Element*& element, int& count){
    if (element == NULL) return;
    Field *fieldElem = element->getField(field->getName());
    if ((fieldElem != NULL) && (fieldElem->getValue().compare(field->getValue()) == 0))
        count++;
    if (element->getLeftElement() != NULL) countElements(field, element->getLeftElement(), count);
    if (element->getRightElement() != NULL) countElements(field, element->getRightElement(), count);
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

bool Table::validateAttributes(vector<string> *attributes){ //verifica se a lista de atributos passada também está existe na tabela
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

bool Table::existPrimaryKey(){ //percorre a lista de atributos e verifica que existe pelo menos 1 primary key definida na tabela
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

Attribute* Table::getAttribute(string name){
    Attribute* attribute = firstAttribute;
    while (attribute){
        if(attribute->getName().compare(name) == 0){
            return attribute;
        } else
            attribute = attribute->getNext();
        }
    return attribute;
}

Element* Table::getRootElement(){
    return this->rootElement;
}

Element* Table::findElement(string key) { //busca um elemento na árvore, se não existir retorna NULL
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

void Table::printAttributesInLine(){
    Attribute *aux = this->firstAttribute;
    cout << "       ";
    if (aux != NULL) {
        while (aux) {
            cout << aux->getName() << "     ";
            aux = aux->getNext();
        }
    } else
        cout << "   Não existem atributos na tabela " << this->getName() << endl;
}

void Table::printAttributesNull(){
    Attribute *aux = this->firstAttribute;
    cout << "       ";
    if (aux != NULL) {
        while (aux) {
            cout << "NULL     ";
            aux = aux->getNext();
        }
    } else
        cout << "   Não existem atributos na tabela " << this->getName() << endl;
}

string Table::getAttributesInLine(){
    Attribute *aux = this->firstAttribute;
    string line = "       ";
    if (aux != NULL) {
        while (aux) {
            line += aux->getName() + "     ";
            aux = aux->getNext();
        }
    }
    return line;
}

string Table::getAttributesNull(){
    Attribute *aux = this->firstAttribute;
    string line = "       ";
    if (aux != NULL) {
        while (aux) {
            line += "NULL     ";
            aux = aux->getNext();
        }
    }
    return line;
}

void Table::applyPrimaryKey(vector<string> attribs){//a partir da leitura do arquivo, esse método é chamado para criar a lista de atributos da tabela
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

void Table::applyForeignKey(Database* database, vector<string> attrib, vector<string> table){
    Attribute *aux = this->firstAttribute;
    vector<string>::iterator itAttrib = attrib.begin();
    vector<string>::iterator itTable = table.begin();
    while (aux) {
        if (aux->getName() == *itAttrib) {
            Table *table = database->getTable(*itTable);
            if (table != NULL){//verifica se a tabela existe no banco
                Attribute *attribute = table->getAttribute(*itAttrib);
                if ((attribute) && (attribute->isPrimarykey())) {//verifica se o attributo existe na tabela referenciada e se é chave primária
                    aux->setTableReference(table);
                    aux->setForeignKey(true);
                } else
                    cout << "       O atributo \"" << *itAttrib << "\" não existe na tabela \"" << table->getName() << "\"." << endl;
            } else
                cout << "       A tabela \"" << *itTable << "\" não existe no banco." << endl;
            aux = this->firstAttribute;
            itAttrib++;
            itTable++;
        } else
            aux = aux->getNext();
    }
    if (itAttrib != attrib.end())
        cout << "       O atributo \"" << *itAttrib << "\" não existe na tabela \"" << this->name << "\"." << endl;
}

void Table::addElement(Element *newElement){
    bool heightChanged = false;
    this->addElement(newElement, this->rootElement, heightChanged);
}

bool Table::removeElement(string key){
    bool heightChanged = false;
    bool success = this->removeElement(key, this->rootElement, heightChanged);
    if (success)
        this->amountElements--;
    return success;
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

int Table::selectCount(string& name, string value){
    int count = 0;
    Field *field = new Field(name,value);
    this->countElements(field, this->rootElement, count);
    return count;
}

// -- INNER JOIN -- // SELECT * FROM datsrcln INNER JOIN data_src ON datsrcln.datasrc_id = data_src.datasrc_id;
//SELECT * FROM tabelab INNER JOIN tabelaa ON tabelab.numero=tabelaa.numero;
// SELECT * FROM table2 INNER JOIN table ON table2.campo1=table.campo1;

void Table::selectInnerJoinPrint(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResult){
    if (elementTable1 == NULL) return;
    Field *field = elementTable1->getField(nameFK);
    if (field != NULL){
        Element *elementTable2 = table2->findElement(field->getValue());
        if (field != NULL && elementTable2 != NULL && field->getValue().compare(elementTable2->getKey()) == 0){
            listResult.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
        }
        if (elementTable1->getLeftElement() != NULL) selectInnerJoinPrint(elementTable1->getLeftElement(), table2, namePK, nameFK, listResult);
        if (elementTable1->getRightElement() != NULL) selectInnerJoinPrint(elementTable1->getRightElement(), table2, namePK, nameFK, listResult);
    }
}

void Table::selectInnerJoin(Table *table2, string nameFK, string namePK, vector<string>& listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()) {
        string line1 = this->getAttributesInLine()+table2->getAttributesInLine();
        listResults.push_back(line1);
        selectInnerJoinPrint(this->getRootElement(), table2, nameFK, namePK, listResults);
    } else
        cout << "       Os campos " << nameFK << " e " << namePK << " não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
}

// -- LEFT OUTER JOIN -- //     SELECT * FROM datsrcln LEFT OUTER JOIN data_src ON datsrcln.datasrc_id = data_src.datasrc_id;
//     SELECT * FROM table2 LEFT OUTER JOIN table ON table2.campo1 = table.campo1;

void Table::selectLeftOuterJoinPrint(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResults){
    if (elementTable1 == NULL) return;
    Field *field = elementTable1->getField(nameFK);
    if (field != NULL) {
        Element *elementTable2 = table2->findElement(field->getValue());
        if (field != NULL && elementTable2 != NULL && field->getValue().compare(elementTable2->getKey()) == 0){
            listResults.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
        } else if(field != NULL && elementTable2 == NULL){
            listResults.push_back(elementTable1->getFieldsInLine() + table2->getAttributesNull());
        }
        if (elementTable1->getLeftElement() != NULL) selectLeftOuterJoinPrint(elementTable1->getLeftElement(), table2, namePK, nameFK, listResults);
        if (elementTable1->getRightElement() != NULL) selectLeftOuterJoinPrint(elementTable1->getRightElement(), table2, namePK, nameFK, listResults);
    }
}

void Table::selectLeftOuterJoin(Table *table2, string nameFK, string namePK, vector<string>& listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()){
        string line1 = this->getAttributesInLine() + table2->getAttributesInLine();
        selectLeftOuterJoinPrint(this->getRootElement(), table2, nameFK, namePK, listResults);
    } else
        cout << "       Os campos " << nameFK << " e " << namePK << " não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
}

// -- RIGHT OUTER JOIN -- //  SELECT * FROM datsrcln RIGHT OUTER JOIN data_src ON datsrcln.datasrc_id = data_src.datasrc_id;
// SELECT * FROM table2 RIGHT OUTER JOIN table ON table2.campo1 = table1.campo1;

void Table::selectRightOuterJoinPrint(Table* table1, Element *elementTable1, Element *elementTable2, string namePK, string nameFK, vector<string>& listResults){
    if (elementTable2 == NULL) return;
    Field *field2 = elementTable2->getField(namePK);
    Field *field1 = elementTable1->getField(nameFK);
    if (field2 != NULL && field1 != NULL && field2->getValue().compare(field1->getValue()) == 0){
        listResults.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
        if (elementTable2->getLeftElement() != NULL) selectRightOuterJoinPrint(table1, table1->getRootElement(), elementTable2->getLeftElement(), namePK, nameFK, listResults);
        if (elementTable2->getRightElement() != NULL) selectRightOuterJoinPrint(table1, table1->getRootElement(), elementTable2->getRightElement(), namePK, nameFK, listResults);
    } else {
        if (elementTable1->getLeftElement() != NULL) selectRightOuterJoinPrint(table1, elementTable1->getLeftElement(), elementTable2, namePK, nameFK, listResults);
        if (elementTable1->getRightElement() != NULL) selectRightOuterJoinPrint(table1, elementTable1->getRightElement(), elementTable2, namePK, nameFK, listResults);
        if (elementTable1->getLeftElement() == NULL && elementTable1->getRightElement() == NULL){
            listResults.push_back(table1->getAttributesNull() + elementTable2->getFieldsInLine());
        }
    }
}

void Table::selectRightOuterJoin(Table *table2, string nameFK, string namePK, vector<string>& listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()){
        string line1 = this->getAttributesInLine() + table2->getAttributesInLine();
        listResults.push_back(line1);
        selectRightOuterJoinPrint(this, this->getRootElement(), table2->getRootElement(), nameFK, namePK, listResults);
    } else
        cout << "       Os campos " << nameFK << " e " << namePK << " não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
}

// -- RIGHT OUTER JOIN -- // SELECT * FROM datsrcln FULL OUTER JOIN data_src ON datsrcln.datasrc_id=data_src.datasrc_id;
// SELECT * FROM table2 FULL OUTER JOIN table ON table2.campo1 = table1.campo1;

void Table::selectLeftExcludingJoin(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResults){
    if (elementTable1 == NULL) return;
    Field *field = elementTable1->getField(nameFK);
    if (field != NULL) {
        Element *elementTable2 = table2->findElement(field->getValue());
        if(field != NULL && elementTable2 == NULL){
            listResults.push_back(elementTable1->getFieldsInLine() + table2->getAttributesNull());
        }
        if (elementTable1->getLeftElement() != NULL) selectLeftOuterJoinPrint(elementTable1->getLeftElement(), table2, namePK, nameFK, listResults);
        if (elementTable1->getRightElement() != NULL) selectLeftOuterJoinPrint(elementTable1->getRightElement(), table2, namePK, nameFK, listResults);
    }
}

void Table::selectFullOuterJoin(Table* table2, string nameFK, string namePK, vector<string>& listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()){
        string line1 = this->getAttributesInLine() + table2->getAttributesInLine();
        listResults.push_back(line1);
        selectLeftExcludingJoin(this->getRootElement(), table2, nameFK, namePK, listResults);
        selectRightOuterJoinPrint(this, this->getRootElement(), table2->getRootElement(), nameFK, namePK, listResults);
    } else
        cout << "       Os campos " << nameFK << " e " << namePK << " não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
}

void Table::startTime(){
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->timeStart);
}

void Table::endTime(double *var){
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->timeEnd);
    *var += (this->timeEnd.tv_sec - this->timeStart.tv_sec) + (this->timeEnd.tv_nsec - this->timeStart.tv_nsec) / 1e9;
}











