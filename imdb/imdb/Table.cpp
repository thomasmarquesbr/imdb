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

/*
 Retorna a direção oposta a direção passada como parâmetro
 */
Direction Table::getOpposite(Direction direction){
    return (direction == RIGHT) ? LEFT : RIGHT;
}

/*
 Rotação simples para a direção passada como parâmetro
 */
void Table::singleRotation(Element *&element, Direction direction){ //executa a rotação simples na direção passada por parâmetro
    int opposite = this->getOpposite(direction);
    Element* child = element->getSubTreeElement(direction);
    element->setSubTreeElement(child->getSubTreeElement(opposite), direction);
    child->setSubTreeElement(element, opposite);
    element = child;
}

/*
 Rotação dupla para a direção passada como parâmetro
 */
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

/*
 Verifica os pesos das subárvores e é feito o rebalanceamento após a inserção de algum elemento.
 Se necessário é feita a rotação simples ou dupla
 */
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

/*
 Verifica os pesos das subárvores e é feito o rebalanceamento após a remoção de algum elemento.
 Se necessário é feita a rotação simples ou dupla
 */
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

/*
 Insere o elemento na árvore e após a inserção é feito o rebalanceamento se necessário
 */
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

/*
 Busca de forma recursiva um elemento na árvore, se encontrar é feita a troca com o maior elemento
 que seja menor que o elemento buscado e em seguida é removido o menor elemento da esquerda. Também é feita
 a verificação sobre a existencia dos filhoes e é feito o rebalanceamento da árvore após a remoção
 */
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

/*
 Imprime a árvore no console Recursivamente em PreOrdem
 */
void Table::readPreOrdem(Element*& node){
    if (node == NULL) return;
    cout << node->getKey() << ", ";
    if (node->getLeftElement() != NULL) readPreOrdem(node->getLeftElement());
    if (node->getRightElement() != NULL) readPreOrdem(node->getRightElement());
}

/*
 Imprime a árvore no console Recursivamente em InOrdem
 */
void Table::readInOrdem(Element*& node){
    if (node == NULL) return;
    if (node->getLeftElement() != NULL) readInOrdem(node->getLeftElement());
    cout << node->getKey() << ", ";
    if (node->getRightElement() != NULL) readInOrdem(node->getRightElement());
}

/*
 Imprime a árvore no console Recursivamente em PosOrdem
 */
void Table::readPosOrdem(Element*& node){
    if (node == NULL) return;
    if (node->getLeftElement() != NULL) readPosOrdem(node->getLeftElement());
    if (node->getRightElement() != NULL) readPosOrdem(node->getRightElement());
    cout << node->getKey() << ", ";
}

void Table::cleanMarked(Element *&node){
    if (node == NULL) return;
    node->setMustPrint(true);
    if (node->getLeftElement() != NULL) cleanMarked(node->getLeftElement());
    if (node->getRightElement() != NULL) cleanMarked(node->getRightElement());
}

/*
 Imprime a árvore no console de forma visual recursivamente
 */
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

/*
 Verifica se a lista de atributos passada também está existe na tabela
 */
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

/*
 Percorre a lista de atributos e verifica que existe pelo menos 1 primary key definida na tabela
 */
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

/*
 Busca um elemento na lista encadeada de atributos, se não existir retorna NULL
 */
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

/*
 Busca um elemento na árvore, se não existir retorna NULL
 */
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

/*
 Imprime no console atributos de uma tabela e indicação de quais compoem a chave primária
 */
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

/*
 Imprime no console uma linha que contém a sequência de atributos de uma tabela
 */
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

/*
 Imprime no console uma linha com valores Null de acordo com a quantidade de atributos na tabela
 */
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

/*
 Retorna uma string que contém a sequência de atributos de uma tabela
 */
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

/*
 Retorna uma string que contém palavras Null de acordo com a quantidade de atributos na tabela
 */
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

/*
 a partir da leitura do arquivo, esse método é chamado para criar a lista de atributos da tabela que irão compor a chave primária
 */
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

/*
 Adiciona uma refêrencia para a tabela a qual a chave estrangeira referencia. Também é feito os testes 
 para verificar se os campos realmente existem na Tabela referenciada e se é chave primária da mesma
 */
void Table::applyForeignKey(Database* database, vector<string> attrib, vector<string> table){
    Attribute *aux = this->firstAttribute;
    vector<string>::iterator itAttrib = attrib.begin();
    vector<string>::iterator itTable = table.begin();
    while (aux) {
        if (aux->getName() == *itAttrib) {
            Table *table = database->getTable(*itTable);
            if (table != NULL){//tabela existe
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

/*
 Chama a função recursiva de inserção de elementos na árvore
 */
void Table::addElement(Element *newElement){
    bool heightChanged = false;
    this->addElement(newElement, this->rootElement, heightChanged);
}

/*
 Chama a função recursiva de remoção de elementos e decrementa a quantidade total de elementos na árvore
 */
bool Table::removeElement(string key){
    bool heightChanged = false;
    bool success = this->removeElement(key, this->rootElement, heightChanged);
    if (success)
        this->amountElements--;
    return success;
}

/*
 Chama a função recursiva de percurso PreOrdem
 */
void Table::printElementsPreOrdem(){
    cout << endl << "       ";
    if (this->rootElement != NULL)
        readPreOrdem(this->rootElement);
    else
        cout << "Tabela vazia.";
    cout << endl;
}

/*
 Chama a função recursiva de percurso InOrdem
 */
void Table::printElementsInOrdem(){
    cout << endl << "       ";
    if (this->rootElement != NULL)
        readInOrdem(this->rootElement);
    else
        cout << "Tabela vazia";
    cout << endl;
}

/*
 Chama a função recursiva de percurso PosOrdem
 */
void Table::printElementsPosOrdem(){
    cout << endl << "       ";
    if (this->rootElement != NULL)
        readPosOrdem(this->rootElement);
    else
        cout << "Tabela vazia";
    cout << endl;
}

/*
 Chama a função recursiva de desenho da árvore
 */
void Table::drawTree(){
    drawTree(this->rootElement, 0);
}

/* 
 Limpa marcações dos elementos feita durante o RIGHT OUTER JOIN e FULL OUTER JOIN
 */
void Table::cleanMarked(){
    this->cleanMarked(this->rootElement);
}

/*
 Percorre os elementos da tabela recursivamente e faz a contagem dos elementos 
 que possuem o campo passado para comparação
 */
void Table::countElements(Field *field, Element*& element, int& count){
    if (element == NULL) return;
    Field *fieldElem = element->getField(field->getName());
    if ((fieldElem != NULL) && (fieldElem->getValue().compare(field->getValue()) == 0))
        count++;
    if (element->getLeftElement() != NULL) countElements(field, element->getLeftElement(), count);
    if (element->getRightElement() != NULL) countElements(field, element->getRightElement(), count);
}

/*
 Função pública que executa a chamada para função recursiva de COUNT(*) acima
 */
int Table::selectCount(string& name, string value){
    int count = 0;
    Field *field = new Field(name,value);
    this->countElements(field, this->rootElement, count);
    return count;
}

/***********************************        SQL JOINS       ***********************************/
/* Chaves estrangeiras e primárias */

/* 
 Função recursiva que executa o INNER JOIN, percorre a Tabela1 obtendo as chaves primárias e faz uma
 busca na Tabela2 com essa chave primária, e combina apenas os elementos que tiverem a mesma chave
 Ex: SELECT * FROM TabelaA INNER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectInnerJoinPK(Element* elementTable1, Table *table2, vector<string>& listResult){
    if (elementTable1 == NULL) return;
    string keyElement1 = elementTable1->getKey();
    Element *elementTable2 = table2->findElement(keyElement1);
    if(elementTable2 != NULL){
        listResult.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
    }
    if (elementTable1->getLeftElement() != NULL) selectInnerJoinPK(elementTable1->getLeftElement(), table2, listResult);
    if (elementTable1->getRightElement() != NULL) selectInnerJoinPK(elementTable1->getRightElement(), table2, listResult);
}

/* 
 Função pública que executa a chamada para função recursiva de INNER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves primárias e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectInnerJoinPK(Table *table2, string namePK1, string namePK2, vector<string>& listResults){
    if (this->getAttribute(namePK1) != NULL && this->getAttribute(namePK1)->isPrimarykey()
        && table2->getAttribute(namePK2) != NULL && table2->getAttribute(namePK2)->isPrimarykey()) {
        string line1 = this->getAttributesInLine()+table2->getAttributesInLine();
        listResults.push_back(line1);
        selectInnerJoinPK(this->getRootElement(), table2, listResults);
    } else
        cout << "       Os campos " << namePK1 << " e " << namePK2 << " não são chaves primárias; " << endl;
}

/*
 Função recursiva que executa o LEFT OUTER JOIN, percorre a Tabela1 obtendo as chaves primárias e faz uma
 busca na Tabela2 com essa chave primária, e combina os elementos que tiverem a mesma chave, caso não encontre na Tabela 2,
 combina os elementos da tabela 1 com campos Nulos
 Ex: SELECT * FROM TabelaA LEFT OUTER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectLeftOuterJoinPK(Element* elementTable1, Table *table2, vector<string>& listResult){
    if (elementTable1 == NULL) return;
    string keyElement1 = elementTable1->getKey();
    Element *elementTable2 = table2->findElement(keyElement1);
    if (elementTable2 != NULL)
        listResult.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
    else
        listResult.push_back(elementTable1->getFieldsInLine() + table2->getAttributesNull());
    if (elementTable1->getLeftElement() != NULL) selectLeftOuterJoinPK(elementTable1->getLeftElement(), table2, listResult);
    if (elementTable1->getRightElement() != NULL) selectLeftOuterJoinPK(elementTable1->getRightElement(), table2, listResult);
}

/*
 Função pública que executa a chamada para função recursiva de LEFT OUTER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves primárias e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectLeftOuterJoinPK(Table *table2, string namePK1, string namePK2, vector<string>& listResults){
    if (this->getAttribute(namePK1) != NULL && this->getAttribute(namePK1)->isPrimarykey()
        && table2->getAttribute(namePK2) != NULL && table2->getAttribute(namePK2)->isPrimarykey()) {
        string line1 = this->getAttributesInLine()+table2->getAttributesInLine();
        listResults.push_back(line1);
        selectLeftOuterJoinPK(this->getRootElement(), table2, listResults);
    } else
        cout << "       Os campos " << namePK1 << " e " << namePK2 << " não são chaves primárias; " << endl;
}

/*
 Função recursiva que executa o RIGHT OUTER JOIN, percorre a Tabela2 obtendo as chaves primárias e faz uma
 busca na Tabela1 com essa chave primária, e combina os elementos que tiverem a mesma chave, caso não encontre na Tabela 1,
 combina os elementos da tabela 2 com campos Nulos
 Ex: SELECT * FROM TabelaA RIGHT OUTER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectRightOuterJoinPK(Element* elementTable2, Table *table1, vector<string>& listResult){
    if (elementTable2 == NULL) return;
    string keyElement2 = elementTable2->getKey();
    Element *elementTable1 = table1->findElement(keyElement2);
    if (elementTable1 != NULL)
        listResult.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
    else
        listResult.push_back(table1->getAttributesNull() + elementTable2->getFieldsInLine());
    if (elementTable2->getLeftElement() != NULL) selectRightOuterJoinPK(elementTable2->getLeftElement(), table1, listResult);
    if (elementTable2->getRightElement() != NULL) selectRightOuterJoinPK(elementTable2->getRightElement(), table1, listResult);
}

/*
 Função pública que executa a chamada para função recursiva de RIGHT OUTER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves primárias e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectRightOuterJoinPK(Table *table2, string namePK1, string namePK2, vector<string>& listResults){
    if (this->getAttribute(namePK1) != NULL && this->getAttribute(namePK1)->isPrimarykey()
        && table2->getAttribute(namePK2) != NULL && table2->getAttribute(namePK2)->isPrimarykey()) {
        string line1 = this->getAttributesInLine()+table2->getAttributesInLine();
        listResults.push_back(line1);
        selectRightOuterJoinPK(table2->getRootElement(), this, listResults);
    } else
        cout << "       Os campos " << namePK1 << " e " << namePK2 << " não são chaves primárias; " << endl;
}

/*
 Função recursiva que executa o FULL OUTER JOIN, percorre a Tabela1 obtendo as chaves primárias e faz uma
 busca na Tabela2 com essa chave primária, e combina os elementos que tiverem a mesma chave, caso não encontre na Tabela 2,
 combina os elementos da tabela 1 com campos Nulos. Neste caso, quando existe o campo nas duas tabelas, os elementos da Tabela 2
 são marcados para que na próxima etapa não seja impresso repetidamente
 Ex: SELECT * FROM TabelaA FULL OUTER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectFullOuterJoinLeft(Element *elementTable1, Table *table2, vector<string> &listResults){
    if (elementTable1 == NULL) return;
    string keyElement1 = elementTable1->getKey();
    Element *elementTable2 = table2->findElement(keyElement1);
    if (elementTable2 != NULL){
        listResults.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
        elementTable2->setMustPrint(false);
    } else
        listResults.push_back(elementTable1->getFieldsInLine() + table2->getAttributesNull());
    if (elementTable1->getLeftElement() != NULL) selectFullOuterJoinLeft(elementTable1->getLeftElement(), table2, listResults);
    if (elementTable1->getRightElement() != NULL) selectFullOuterJoinLeft(elementTable1->getRightElement(), table2, listResults);
}

/*
 Percorre a Tabela 2 e imprime os elementos não marcados pela primeira parte e concatena esses elementos com elementos Nulos
 Os elementos marcados também são desmarcados nessa parte. Esta parte tem um resultado similar ao right excluding join, desde que a 
 função acima seja executada antes.
 */
void Table::selectFullOuterJoinRight(Element *elementTable2, Table *table1, vector<string> &listResults){
    if (elementTable2 == NULL) return;
    if (elementTable2->getMustPrint()){
        listResults.push_back(table1->getAttributesNull() + elementTable2->getFieldsInLine());
    } else {
        elementTable2->setMustPrint(true);
    }
    if (elementTable2->getLeftElement() != NULL) selectFullOuterJoinRight(elementTable2->getLeftElement(), table1, listResults);
    if (elementTable2->getRightElement() != NULL) selectFullOuterJoinRight(elementTable2->getRightElement(), table1, listResults);
}

/*
 Função pública que executa a chamada para as duas funções recursivas de FULL OUTER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves primárias e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectFullOuterJoin(Table* table2, string namePK1, string namePK2, vector<string>& listResults){
    if (this->getAttribute(namePK1) != NULL && this->getAttribute(namePK1)->isPrimarykey()
        && table2->getAttribute(namePK2) != NULL && table2->getAttribute(namePK2)->isPrimarykey()){
        string line1 = this->getAttributesInLine() + table2->getAttributesInLine();
        listResults.push_back(line1);
        selectFullOuterJoinLeft(this->getRootElement(), table2, listResults);
        selectFullOuterJoinRight(table2->getRootElement(), this, listResults);
    } else
        cout << "       Os campos " << namePK1 << " e " << namePK2 << " não são chaves primárias; " << endl;
}


/*  Chaves estrangeiras e primárias */

/*
 Função recursiva que executa o INNER JOIN, percorre a Tabela1 procurando pela chave estrangeira e faz uma
 busca na Tabela2 com o valor dessa chave, e combina apenas os elementos que tiverem a mesma chave estrangeira=primária
 Ex: SELECT * FROM TabelaA INNER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectInnerJoinFK(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResult){
    if (elementTable1 == NULL) return;
    Field *field = elementTable1->getField(nameFK);
    if (field != NULL){
        Element *elementTable2 = table2->findElement(field->getValue());
        if (field != NULL && elementTable2 != NULL && field->getValue().compare(elementTable2->getKey()) == 0){
            listResult.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
        }
        if (elementTable1->getLeftElement() != NULL) selectInnerJoinFK(elementTable1->getLeftElement(), table2, namePK, nameFK, listResult);
        if (elementTable1->getRightElement() != NULL) selectInnerJoinFK(elementTable1->getRightElement(), table2, namePK, nameFK, listResult);
    }
}

/*
 Função pública que executa a chamada para função recursiva de INNER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves estrangeira e primária respectivamente, verifica a referencia da chave
 estrangeira na tabela definida e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectInnerJoinFK(Table *table2, string nameFK, string namePK, vector<string>& listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) == 0 //verifica referencia da chave estrangeira
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()) {
        string line1 = this->getAttributesInLine()+table2->getAttributesInLine();
        listResults.push_back(line1);
        selectInnerJoinFK(this->getRootElement(), table2, nameFK, namePK, listResults);
    } else {
        if (!this->getAttribute(nameFK)->isForeignKey() || table2->getAttribute(namePK)->isPrimarykey())
            cout << "       Os campos \"" << nameFK << "\" e \"" << namePK << "\" não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
        if (this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) != 0)
            cout << "       O campo \"" << nameFK << "\" da tabela \"" << this->name << "\" não está referenciando a tabela \"" << table2->name;
    }
}

/*
 Função recursiva que executa o LEFT OUTER JOIN, percorre a Tabela1 obtendo a chave estrangeira e faz uma
 busca na Tabela2 com essa chave, e combina os elementos que tiverem a mesma chave, caso não encontre na Tabela 2,
 combina os elementos da tabela 1 com campos Nulos
 Ex: SELECT * FROM TabelaA LEFT OUTER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectLeftOuterJoinFK(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResults){
    if (elementTable1 == NULL) return;
    Field *field = elementTable1->getField(nameFK);
    if (field != NULL) {
        Element *elementTable2 = table2->findElement(field->getValue());
        if (field != NULL && elementTable2 != NULL && field->getValue().compare(elementTable2->getKey()) == 0){
            listResults.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
        } else if(field != NULL && elementTable2 == NULL){
            listResults.push_back(elementTable1->getFieldsInLine() + table2->getAttributesNull());
        }
        if (elementTable1->getLeftElement() != NULL) selectLeftOuterJoinFK(elementTable1->getLeftElement(), table2, namePK, nameFK, listResults);
        if (elementTable1->getRightElement() != NULL) selectLeftOuterJoinFK(elementTable1->getRightElement(), table2, namePK, nameFK, listResults);
    }
}

/*
 Função pública que executa a chamada para função recursiva de LEFT OUTER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves estrangeira e primária respectivamente, verifica a referencia da chave
 estrangeira na tabela definida e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectLeftOuterJoinFK(Table *table2, string nameFK, string namePK, vector<string>& listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) == 0 //verifica referencia da chave estrangeira
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()){
        string line1 = this->getAttributesInLine() + table2->getAttributesInLine();
        selectLeftOuterJoinFK(this->getRootElement(), table2, nameFK, namePK, listResults);
    } else {
        if (!this->getAttribute(nameFK)->isForeignKey() || table2->getAttribute(namePK)->isPrimarykey())
            cout << "       Os campos \"" << nameFK << "\" e \"" << namePK << "\" não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
        if (this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) != 0)
            cout << "       O campo \"" << nameFK << "\" da tabela \"" << this->name << "\" não está referenciando a tabela \"" << table2->name;
    }
}

/*
 Função recursiva que executa o RIGHT OUTER JOIN, percorre a Tabela2 obtendo a chave primaria e faz uma
 busca na Tabela1 buscando pela chave estrangeira, e combina os elementos que tiverem a mesma chave, caso não encontre na Tabela 1,
 combina os elementos da tabela 2 com campos Nulos. Marca os elementos ja combinados para que eles não sejam exibidos novamente
 Ex: SELECT * FROM TabelaA LEFT OUTER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectRightOuterJoinFK(Table* table1, Element *elementTable1, Element *elementTable2, string namePK, string nameFK, vector<string>& listResults){
    if (elementTable2 == NULL) return;
    Field *field2 = elementTable2->getField(namePK);
    Field *field1 = elementTable1->getField(nameFK);
    if (field2 != NULL && field1 != NULL && field2->getValue().compare(field1->getValue()) == 0){
        if (elementTable2->getMustPrint()) {
            listResults.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
            elementTable2->setMustPrint(false);
        }
        if (elementTable2->getLeftElement() != NULL) selectRightOuterJoinFK(table1, table1->getRootElement(), elementTable2->getLeftElement(), namePK, nameFK, listResults);
        if (elementTable2->getRightElement() != NULL) selectRightOuterJoinFK(table1, table1->getRootElement(), elementTable2->getRightElement(), namePK, nameFK, listResults);
    } else {
        if (elementTable1->getLeftElement() != NULL) selectRightOuterJoinFK(table1, elementTable1->getLeftElement(), elementTable2, namePK, nameFK, listResults);
        if (elementTable1->getRightElement() != NULL) selectRightOuterJoinFK(table1, elementTable1->getRightElement(), elementTable2, namePK, nameFK, listResults);
        if (elementTable1->getLeftElement() == NULL && elementTable1->getRightElement() == NULL && elementTable2->getMustPrint()){
            listResults.push_back(table1->getAttributesNull() + elementTable2->getFieldsInLine());
            elementTable2->setMustPrint(false);
        }
    }
}

/*
 Função pública que executa a chamada para função recursiva de RIGHT OUTER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves estrangeira e primeira respectivamente, verifica a referencia da chave
 estrangeira na tabela definida e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectRightOuterJoinFK(Table *table2, string nameFK, string namePK, vector<string>& listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) == 0 //verifica referencia da chave estrangeira
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()){
        string line1 = this->getAttributesInLine() + table2->getAttributesInLine();
        listResults.push_back(line1);
        selectRightOuterJoinFK(this, this->getRootElement(), table2->getRootElement(), nameFK, namePK, listResults);
        table2->cleanMarked();
    } else {
        if (!this->getAttribute(nameFK)->isForeignKey() || table2->getAttribute(namePK)->isPrimarykey())
            cout << "       Os campos \"" << nameFK << "\" e \"" << namePK << "\" não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
        if (this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) != 0)
            cout << "       O campo \"" << nameFK << "\" da tabela \"" << this->name << "\" não está referenciando a tabela \"" << table2->name;
    }
}

/*
 Função recursiva que executa o FULL OUTER JOIN, percorre a Tabela1 obtendo as chaves estrangeiras e faz uma
 busca na Tabela2 com essa chave, e combina os elementos que tiverem a mesma chave, caso não encontre na Tabela 2,
 combina os elementos da tabela 1 com campos Nulos. Neste caso, quando existe o campo nas duas tabelas, os elementos da Tabela 2
 são marcados para que na próxima etapa não seja impresso repetidamente
 Ex: SELECT * FROM TabelaA FULL OUTER JOIN TabelaB ON TabelaA.numero = TabelaB.numero;
 */
void Table::selectFullOuterJoinLeftFK(Element *elementTable1, Table *table2, string namePK, string nameFK, vector<string> &listResults){
    if (elementTable1 == NULL) return;
    Field *field = elementTable1->getField(nameFK);
    if (field != NULL) {
        Element *elementTable2 = table2->findElement(field->getValue());
        if (field != NULL && elementTable2 != NULL && field->getValue().compare(elementTable2->getKey()) == 0){
            listResults.push_back(elementTable1->getFieldsInLine() + elementTable2->getFieldsInLine());
            elementTable2->setMustPrint(false);
        } else if(field != NULL && elementTable2 == NULL){
            listResults.push_back(elementTable1->getFieldsInLine() + table2->getAttributesNull());
        }
        if (elementTable1->getLeftElement() != NULL) selectLeftOuterJoinFK(elementTable1->getLeftElement(), table2, namePK, nameFK, listResults);
        if (elementTable1->getRightElement() != NULL) selectLeftOuterJoinFK(elementTable1->getRightElement(), table2, namePK, nameFK, listResults);
    }
}

/*
 Percorre a Tabela 2 e imprime os elementos não marcados pela primeira parte e concatena esses elementos com elementos Nulos
 Os elementos marcados também são desmarcados nessa parte. Esta parte tem um resultado similar ao right excluding join, desde que a
 função acima seja executada antes.
 */
void Table::selectFullOuterJoinRightFK(Element *elementTable2, Table *table1, vector<string> &listResults){
    if (elementTable2 == NULL) return;
    if (elementTable2->getMustPrint()){
        listResults.push_back(table1->getAttributesNull() + elementTable2->getFieldsInLine());
    } else {
        elementTable2->setMustPrint(true);
    }
    if (elementTable2->getLeftElement() != NULL) selectFullOuterJoinRight(elementTable2->getLeftElement(), table1, listResults);
    if (elementTable2->getRightElement() != NULL) selectFullOuterJoinRight(elementTable2->getRightElement(), table1, listResults);
}

/*
 Função pública que executa a chamada para as duas funções recursivas de FULL OUTER JOIN acima, antes da chamada é feito os testes
 para verificar se as chaves passadas são chaves primárias e prepara a impressão dos nomes dos campos das duas tabelas
 */
void Table::selectFullOuterJoinFK(Table *table2, string nameFK, string namePK, vector<string> &listResults){
    if (this->getAttribute(nameFK) != NULL && this->getAttribute(nameFK)->isForeignKey()
        && this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) == 0 //verifica referencia da chave estrangeira
        && table2->getAttribute(namePK) != NULL && table2->getAttribute(namePK)->isPrimarykey()){
        string line1 = this->getAttributesInLine() + table2->getAttributesInLine();
        listResults.push_back(line1);
        selectFullOuterJoinLeftFK(this->rootElement, table2, nameFK, namePK, listResults);
        selectFullOuterJoinRightFK(table2->getRootElement(), this, listResults);
    } else {
        if (!this->getAttribute(nameFK)->isForeignKey() || table2->getAttribute(namePK)->isPrimarykey())
            cout << "       Os campos \"" << nameFK << "\" e \"" << namePK << "\" não são chaves estrangeiras e chaves primárias respectivamente; " << endl;
        if (this->getAttribute(nameFK)->getTableReference()->getName().compare(table2->getName()) != 0)
            cout << "       O campo \"" << nameFK << "\" da tabela \"" << this->name << "\" não está referenciando a tabela \"" << table2->name;
    }
}

/* 
 Função que inicia a contagem de tempo de alguma operação
 */
void Table::startTime(){
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->timeStart);
}

/*
 Função que encerra a contagem de tempo de alguma operação e armazena em uma variável double
 */
void Table::endTime(double *var){
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->timeEnd);
    *var += (this->timeEnd.tv_sec - this->timeStart.tv_sec) + (this->timeEnd.tv_nsec - this->timeStart.tv_nsec) / 1e9;
}











