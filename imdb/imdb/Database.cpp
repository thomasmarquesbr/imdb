//
//  Database.cpp
//  imdb
//
//  Created by Thomás Marques on 19/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include "Database.hpp"
#include "Table.hpp"

using namespace std;

/* PRIVATE METHODS */

void Database::split(const std::string& str, std::vector<std::string>& v) {
    std::stringstream ss(str);
    ss >> std::noskipws;
    std::string field;
    char ws_delim;
    while(1) {
        if( ss >> field )
            v.push_back(field);
        else if (ss.eof())
            break;
        else
            v.push_back(std::string());
        ss.clear();
        ss >> ws_delim;
    }
}

string Database::removeCharsFromString(const string str, char* charsToRemove) {
    char c[str.length()+1]; 
    const char *p = str.c_str();
    unsigned int z=0, size = str.length();
    unsigned int x;
    bool rem=false;
    for(x=0; x<size; x++) {
        rem = false;
        for (unsigned int i = 0; charsToRemove[i] != 0; i++) {
            if (charsToRemove[i] == p[x]) {
                rem = true;
                break;
            }
        }
        if (rem == false) c[z++] = p[x];
    }
    c[z] = '\0';
    return string(c);
}

void Database::print(vector<string> list) {
    for(int i=0; i < list.size(); i++){
        cout<<list[i]<<endl;
    }
}


/* PUBLIC METHODS */

Database::Database(){
    this->firstTable = NULL;
    this->lastTable = NULL;
    this->amountTables = 0;
}

Database::~Database(){
    this->clear();
}

bool Database::empty(){
    return (firstTable == NULL);
}

int Database::getAmountTables(){
    return this->amountTables;
}

Table* Database::getFirstTable(){
    return this->firstTable;
}

Table* Database::getLastTable(){
    return this->lastTable;
}

Table* Database::getTable(string name){
    Table* table = firstTable;
    if (!empty()){
        while (table){
            if(table->getName().compare(name) == 0){
                return table;
            } else
                table = table->getNextTable();
        }
    }
    return table;
}

void Database::addTable(Table *newTable){
    Table* table = getTable(newTable->getName());
    if (table == NULL){//não existe
        if (empty()) {
            firstTable = newTable;
            lastTable = newTable;
        } else {
            lastTable->setNextTable(newTable);
            lastTable = newTable;
        }
        amountTables++;
        cout << "       Tabela criada com sucesso." << endl;
    } else { //ja existe
        cout << "       Falha ao criar tabela!"<<endl;
        cout << "       A tabela " << newTable->getName() << "ja existe" << endl;
    }
}

void Database::removeTable(string name){
    Table* prevTable = firstTable;
    Table* currTable = firstTable;
    if (currTable->getName().compare(name) == 0){
        firstTable = currTable->getNextTable();
        if (firstTable == NULL)
            lastTable = NULL;
        amountTables--;
    } else {
        while(currTable != NULL)
            if(currTable->getName().compare(name) != 0){
                prevTable = currTable;
                currTable = currTable->getNextTable();
            } else {
                prevTable->setNextTable(currTable->getNextTable());
                delete currTable;
                amountTables--;
                break;
            }
    }
}

void Database::printTables() {
    Table *aux = this->firstTable;
    string names = "";
    while (aux != NULL) {
        names+= " " + aux->getName() + ",";
        aux = aux->getNextTable();
    }
    if (names.empty()) {
        cout << "       Não existem tabelas no banco" <<endl;
    } else {
        names = "       R." + names.substr(0, names.size()-1) + ".";
        cout << endl;
        cout << names << endl;
    }
}

void Database::clear(){
    Table *aux = this->firstTable;
    while (aux != NULL) {
        firstTable = firstTable->getNextTable();
        delete aux;
        aux = firstTable;
    }
    lastTable = NULL;
}

void Database::readFile(string path) {
    string line;
    ifstream myFile(path);
    if (myFile.is_open()){
        while (getline(myFile,line)) {
            
            if (isdigit(*line.begin()) || isalpha(*line.begin()) || line.substr(0,2) == "\\." || line.substr(0,2) == ");") {
                //                cout<<line<<endl;
                vector<string> words;
                split(line, words);
                if (*words.begin() == "CREATE") { //Criando tabelas
                    while(line.substr(0,2) != ");"){
                        getline(myFile, line);
                        vector<string> words;
                        split(line, words);
                        for (vector<string>::iterator field=words.begin(); field!=words.end(); ++field) {
                            if ((*field != "")&&(*field != ");")) {
                                string name_attrib = removeCharsFromString(*field, "\"");
                                break;
                            }
                        }
                    }
                } else if (*words.begin() == "COPY") {//populando tabelas
                    string name_table = words[1];
                    vector<string> attribs;
                    vector<string>::iterator field = words.begin()+2;
                    while (field != words.end() - 2){
                        attribs.push_back(removeCharsFromString(*field, "\"(,)"));
                        ++field;
                    }
                    while (getline(myFile, line)){
                        if (line.substr(0,2) == "\\.")
                            break;
                        istringstream iss(line);
                        string value;
                        while(getline(iss, value, '\t')){
                            if (!value.empty()){
                                
                            }
                        }
                    }
                    //Copiar da antiga pra cá
                }
                
            }
            
        }
        myFile.close();
    } else {
        cout<<"Falha ao abrir o arquivo"<<endl;
    }
}
