//
//  Database.hpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include <time.h>

class Database;

#include "Table.hpp"

using namespace std;

class Database{
private:
    Table *firstTable;
    Table *lastTable;
    int amountTables;
    timespec timeStart; // variáveis para auxiliar a medição do tempo de leitura, criação das estruturas ou de buscas
    timespec timeEnd;
    double readFileTime;
    double creationTime;
    
//    string trim(std::string & str); //remove espaços em branco dos campos
//    string removeCharsFromString(const string str, char* charsToRemove); //remove cacacteres passados como parametros de uma string
//    string toUpper(string strToConvert);
//    void split(const std::string& str, std::vector<std::string>& v); //quebra string em partes
//    void print(vector<string> list); //imprime lista no console, auxilia na criação das estruturas
    void clear();
    
public:
    Database();
    ~Database();
    bool empty();
    int getAmountTables();
    double getCreationTime(); // retorna o tempo total de criação das estruturas, criação de tabelas, inserção de registros, etc.
    Table* getFirstTable();
    Table* getLastTable();
    Table* getTable(string name); //retorna se existir a tabela da lista encadeada, caso contrário retorna NULL
    void executeParserSql(string querySql);
    void printTables(); //imprime no console o nome das tabelas já criadas no banco
    void addTable(Table *newTable); //adiciona uma nova tabela com nome distindo na lista encadeada
    void removeTable(string name); //remove uma tabela da lista encadeada se existir
    void readFile(string path); //executa a leitura do arquivo e armazena em listas vector<string> e só depois são criados as estruturas de acordo com as informações carregadas
    void startTime(); //captura o tempo de início na medição do tempo
    void endTime(double *var); //captura o tempo de fim e calcula o tempo percorrido para executar determinada ação
};

#endif /* Database_hpp */
