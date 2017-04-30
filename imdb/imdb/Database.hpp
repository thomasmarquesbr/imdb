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
#include "Table.hpp"

class Database{
private:
    Table *firstTable;
    Table *lastTable;
    int amountTables;
    
    void split(const std::string& str, std::vector<std::string>& v);
    string removeCharsFromString(const string str, char* charsToRemove);
    void print(vector<string> list);
public:
    Database();
    ~Database();
    bool empty();
    int getAmountTables();
    Table* getFirstTable();
    Table* getLastTable();
    Table* getTable(string name);
    void printTables();
    void addTable(Table *newTable);
    void removeTable(string name);
    void clear();
    void readFile(string path);
};

#endif /* Database_hpp */
