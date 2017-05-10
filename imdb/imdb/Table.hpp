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
    timespec timeStart;
    timespec timeEnd;
    
    inline Direction getOpposite(Direction direction); //retorna a direção oposta usada nas rotações
    
    /* rotação simples de forma generalizada, portanto é passado como parâmetro a direção em que se deseja fazer a rotação */
    void singleRotation(Element*& element, Direction direction);
    
    /* rotação dupla de forma generalizada, da mesma forma é passado como parâmetro a direção em que se deseja fazer a rotação */
    void doubleRotation(Element*& element, Direction direction);
    
    /* rebalanceia a subarvore após a inserção de um elemento verificando se houve alteração na subarvore de maior altura, determinando se é necessário fazer uma rotação simples ou dupla */
    void rebalanceInsert(Element*& element, Direction direction, bool& heightChanged);
    
    void rebalanceRemove(Element*& element, Direction direction, bool& heightChanged);
    
    /* atualiza os fatores de balanceamento após executar uma rotação */
    void updateBalance(Element* element, Direction direction);
    
    /* percorre a árvore e adiciona um elemento na árvore se possível de acordo com a chave primária definida */
    void addElement(Element *newElement, Element*& currentElement, bool& heightChanged);
    
    // Remove um item da árvore a partir de sua chave (palavra)
    bool removeElement(const string& chave, Element*& element, bool& hChanged);
    
    /* métodos recursivos dos percursos PreOrdem, InOrdem e PosOrdem  */
    void readPreOrdem(Element*& node);
    void readInOrdem(Element*& node);
    void readPosOrdem(Element*& node);
    
    /* método recursivo da exibição da árvore */
    void drawTree(Element* element, int spaces);
    void clear();
    
public:
    Table(string name);
    ~Table();
    
    bool empty(); // verifica se a arvore está vazia
    
    /* verifica se os atributos passados ao começar a ler uma sequencia de registros são válidos naquela tabela, ou seja, se existem todos os atributos que serão inseridos */
    bool validateAttributes(vector<string> *attributes);
    
    /* testa se foi definido pelo menos 1 atributo chave no momento da criação da tabela*/
    bool existPrimaryKey();
    
    int getAmountElements();
    string getName();
    Attribute* getFirstAttribute();
    Element* getRootElement();
    
    /* localiza elemento na árvore, caso contrário retorna NULL */
    Element* findElement(string key);
    
    Table* getNextTable();
    
    void addAttribute(string name);
    void addAttribute(string name, bool isPrimaryKey);
    void setNextTable(Table *newTable);
    void printAttributes();
    
    /* define os atributos que irão compor a chave primária, usado ao ler o comando de ALTER TABLE do arquivo */
    void applyPrimaryKey(vector<string> attribs);
    
    /* define quais atributos são chaves estrangeiras na tabela */
    void applyForeignKey(vector<string> attribs);
    
    /* insere um elemento na árvore */
    void addElement(Element *newElement);
    
    bool removeElement(string key);
    
    void printElementsPreOrdem();
    void printElementsInOrdem();
    void printElementsPosOrdem();
    
    /* imprime a árvore no console de forma visual */
    void drawTree();
    
    /* métodos usados para auxiliar a medição do tempo ao executar determinada operação */
    void startTime();
    void endTime(double *var);
};

#endif /* Table_hpp */

