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

class Table;

#include "Util.hpp"
#include "Database.hpp"
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
    
    /* SQL com chaves primárias apenas */
    void selectInnerJoinPK(Element* elementTable1, Table *table2, vector<string>& listResult);
    void selectLeftOuterJoinPK(Element* elementTable1, Table *table2, vector<string>& listResults);
    void selectRightOuterJoinPK(Element* elementTable2, Table *table1, vector<string>& listResult);
    void selectFullOuterJoinLeft(Element* elementTable1, Table *table2, vector<string>& listResults);
    void selectFullOuterJoinRight(Element* elementTable2, Table *table1, vector<string>& listResults);
    
    /* SQL com chaves estrangeiras e primárias */
//    void selectInnerJoinFK(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResult);
    //    void selectLeftOuterJoinPrint(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResults);
    //    void selectRightOuterJoinPrint(Table* table1, Element *elementTable1, Element *elementTable2, string namePK, string nameFK, vector<string>& listResults);
    //    void selectLeftExcludingJoin(Element* elementTable1, Table *table2, string namePK, string nameFK, vector<string>& listResults);
    
    /* método recursivo da exibição da árvore */
    void drawTree(Element* element, int spaces);
    void countElements(Field *field, Element*& element, int& count);
    void clear();
    
public:
    Table(string name);
    ~Table();
    /* verifica se a arvore está vazia */
    bool empty();
    /* verifica se os atributos passados ao começar a ler uma sequencia de registros são válidos naquela tabela, ou seja, se existem todos os atributos que serão inseridos */
    bool validateAttributes(vector<string> *attributes);
    /* testa se foi definido pelo menos 1 atributo chave no momento da criação da tabela*/
    bool existPrimaryKey();
    
    int getAmountElements();
    string getName();
    Attribute* getFirstAttribute();
    Attribute* getAttribute(string name);
    Element* getRootElement();
    Element* findElement(string key);
    Table* getNextTable();
    
    void addAttribute(string name);
    void addAttribute(string name, bool isPrimaryKey);
    void setNextTable(Table *newTable);
    void printAttributes();
    void printAttributesInLine();
    void printAttributesNull();
    string getAttributesInLine();
    string getAttributesNull();
    
    /* define os atributos que irão compor a chave primária, usado ao ler o comando de ALTER TABLE do arquivo */
    void applyPrimaryKey(vector<string> attribs);
    /* define quais atributos são chaves estrangeiras na tabela */
    void applyForeignKey(Database* database, vector<string> attribs, vector<string> tables);
    
    void addElement(Element *newElement);
    bool removeElement(string key);
    
    /* Realiza percuros na árvore */
    void printElementsPreOrdem();
    void printElementsInOrdem();
    void printElementsPosOrdem();
    /* imprime a árvore no console de forma visual */
    void drawTree();
    
    /* Consultas SQL */
    int selectCount(string& name, string value);
    /* Apenas com chaves primárias */
    void selectInnerJoinPK(Table *table2, string nameFK, string namePK, vector<string>& listResults);
    void selectLeftOuterJoinPK(Table *table2, string nameFK, string namePK, vector<string>& listResults);
    void selectRightOuterJoinPK(Table *table2, string nameFK, string namePK, vector<string>& listResults);
    void selectFullOuterJoin(Table* table2, string nameFK, string namePK, vector<string>& listResults);
    
    /* Com chaves estrangeiras e primárias */
//    void selectInnerJoinFK(Table *table2, string nameFK, string namePK, vector<string>& listResults);
//    void selectLeftOuterJoin(Table *table2, string nameFK, string namePK, vector<string>& listResults);
//    void selectRightOuterJoin(Table *table2, string nameFK, string namePK, vector<string>& listResults);

    
    /* métodos usados para auxiliar a medição do tempo ao executar determinada operação */
    void startTime();
    void endTime(double *var);
};

#endif /* Table_hpp */

