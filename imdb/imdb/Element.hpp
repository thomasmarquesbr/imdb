//
//  Element.hpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include <stdio.h>

class Element;

#include "Field.hpp"
#include "Attribute.hpp"
#include "Util.hpp"

class Element{
private:
    unsigned short balance; //fator de balanceamento da subárvore
    int amountFields;
    string key; //chave primária do elemento, se houver chave composta, a mesma é concatenada e armazenada na variável key
    Field *firstField;
    Field *lastField;
    Element *subTreeElement[2]; //referências para as subárvores
    
    void clear();
public:
    Element();
    ~Element();
    
    /* verifica se o elemento possui dados */
    bool empty();
    
    /* verifica se o elemento possui determinado valor em um atributo */
    bool existField(string name);
    
    int getBalance();
    int getAmountFields();
    string getKey();
    Field* getFirstField();
    Field* getLastField();
    Field* getField(string name);
    
    void substituteElement(Element *newElement);
    
    /* retorna subarvore necessária de acordo com a direção da mesma que é passada como parâmetro */
    Element*& getSubTreeElement(int direction);
    Element*& getLeftElement();
    Element*& getRightElement();
    
    /* analisa os atributos da tabela e atualiza/concatena a chave primária key */
    void setPrimaryKey(Attribute *attrib);
    
    void setSubTreeElement(Element*& element, int direction);
    void setBalance(unsigned short balance);
    
    /* adiciona novo elemento na lista encadeada de campos do elemento, se o campo ja existir, o mesmo é atualizado */
    void addField(string name, string value);
    void removeField(string name);
    void printFields();
    void printFieldsInLine();
};

#endif /* Element_hpp */
