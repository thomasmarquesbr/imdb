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
    double queryTime;
    
    void clearQueryTime();
    void clear();
    
public:
    Database();
    ~Database();
    bool empty();
    int getAmountTables();
    double getCreationTime();
    Table* getFirstTable();
    Table* getLastTable();
    Table* getTable(string name);
    void executeParserSql(string querySql, bool onlyPK);
    void printTables();
    void addTable(Table *newTable);
    void removeTable(string name);
    void readFile(string path); 
    void startTime(); //captura o tempo de início na medição do tempo
    void endTime(double *var); //captura o tempo de fim e calcula o tempo percorrido para executar determinada ação
};

#endif /* Database_hpp */
