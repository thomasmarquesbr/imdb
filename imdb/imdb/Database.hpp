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
#include "Table.hpp"

class Database{
private:
    Table *firstTable;
    Table *lastTable;
    int amountTables;
    timespec timeStart;
    timespec timeEnd;
    double readFileTime;
    double creationTime;
    
    string trim(std::string & str);
    string removeCharsFromString(const string str, char* charsToRemove);
    void split(const std::string& str, std::vector<std::string>& v);
    void print(vector<string> list);
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
    void printTables();
    void addTable(Table *newTable);
    void removeTable(string name);
    void readFile(string path);
    void startTime();
    void endTime(double *var);
};

#endif /* Database_hpp */
