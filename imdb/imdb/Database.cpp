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
#include <ctime>
#include <time.h>

#include "Database.hpp"
#include "Table.hpp"

using namespace std;

/* PRIVATE METHODS */

string Database::trim(std::string & str){
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
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

void Database::print(vector<string> list) {
    for(int i=0; i < list.size(); i++){
        cout<<list[i]<<endl;
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

/* PUBLIC METHODS */

Database::Database(){
    this->firstTable = NULL;
    this->lastTable = NULL;
    this->amountTables = 0;
    this->readFileTime = 0.0;
    this->creationTime = 0.0;
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

double Database::getCreationTime(){
    return this->creationTime;
}

Table* Database::getFirstTable(){
    return this->firstTable;
}

Table* Database::getLastTable(){
    return this->lastTable;
}

Table* Database::getTable(string name){ //busca por uma tabela no banco, retorna NULL se não existir
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

void Database::addTable(Table *newTable){ //insere uma tabela no banco
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
        cout << "       Tabela " + newTable->getName() + " criada com sucesso." << endl;
    } else { //ja existe
        cout << "       Falha ao criar tabela!"<<endl;
        cout << "       A tabela " << newTable->getName() << " ja existe" << endl;
    }
}

void Database::removeTable(string name){ //remove uma tabela do banco
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

void Database::readFile(string path){
    vector<vector<string>> createTables; //carrega as tabelas que deverão ser criadas
    vector<vector<vector<string>>> copyTables; //carrega os registros a serem inseridos em cada tabela, a primeira linha do comando também é carregada para saber em qual tabela e quais campos serão inseridos
    vector<vector<string>> alterTables; //carrega as informações de quais campos serão chaves primárias
    
    startTime();
    string line;
    ifstream myFile(path);
    if (myFile.is_open()){
        cout << endl;
        while(getline(myFile,line)){
            vector<vector<string>> listTables;
            if (isdigit(*line.begin()) || isalpha(*line.begin()) || line.substr(0,2) == "\\." || line.substr(0,2) == ");") {
                vector<string> words;
                split(line, words);
                if ((*words.begin() == "CREATE") && (words[1] == "TABLE")) { //primeiro é carregado as informações sobre a criação das tabelas
                    cout << "       Lendo informações de criação de tabelas..." << endl;
                    vector<string> table;
                    table.push_back(words[2]);//nameTable
                    while(line.substr(0,2) != ");"){
                        getline(myFile, line);
                        vector<string> words;
                        split(line, words);
                        for (vector<string>::iterator field=words.begin(); field!=words.end(); ++field) {
                            if ((*field != "")&&(*field != ");")) {
                                table.push_back(removeCharsFromString(*field, "\"")); // name atributes
                                break;
                            }
                        }
                    }
                    createTables.push_back(table);
                } else if (*words.begin() == "COPY") {//segundo é carregado as informações dos registros
                    cout << "       Lendo informações de registros..." << endl;
                    vector<string> table;
                    table.push_back(words[1]);
                    vector<string>::iterator field = words.begin()+2;
                    while (field != words.end() - 2){
                        table.push_back(removeCharsFromString(*field, "\"(,)"));
                        ++field;
                    }
                    listTables.push_back(table);
                    while (getline(myFile, line)){
                        if (line.substr(0,2) == "\\.")
                            break;
                        istringstream iss(line);
                        string value;
                        vector<string>::iterator itAttrib = table.begin()+1;
                        vector<string> values;
                        while(getline(iss, value, '\t')){
                            if (!value.empty()){
                                string nameAtrrib = *itAttrib;
                                values.push_back(trim(value));
                                ++itAttrib;
                            }
                        }
                        listTables.push_back(values);
                    }
                    copyTables.push_back(listTables);
                } else if (*words.begin() == "ALTER") {//por fim carrega as informações que se tornarão chaves primárias
                    cout << "       Lendo informações adicionais sobre as tabelas..." << endl;
                    vector<string> table;
                    string nameTable = words[3];
                    getline(myFile, line);
                    vector<string> words;
                    split(line, words);
                    bool mustRead = false;
                    for(vector<string>::iterator word=words.begin(); word != words.end(); word++){
                        if ((*word == "PRIMARY")||(mustRead)) {
                            if (!mustRead){
                                word += 2;
                                table.push_back(nameTable);
                            }
                            mustRead = true;
                            table.push_back(removeCharsFromString(*word, "\"(,);"));//attrib primary Key
                        }
                    }
                    if (mustRead)
                        alterTables.push_back(table);
                }
            }
        }
        myFile.close();
    } else {
        cout << "       Falha ao abrir o arquivo!" << endl;
    }
    endTime(&this->readFileTime);
    
    cout << endl;
    cout << "       Tempo de leitura do arquivo: " << this->readFileTime << " segundos." << endl;
    cout << endl;
    cout << "       Criando tabelas..." << endl;
    startTime();
    //cria as tabelas no banco lendo as informações do vector<vector<string>> createTables
    for(vector<vector<string>>::iterator table = createTables.begin(); table != createTables.end(); table++){
        Table *t = nullptr;
        for(vector<string>::iterator value = table->begin(); value != table->end(); value++){
            if (value == table->begin())//nome da tabela
                t = new Table(*value);
            else
                t->addAttribute(*value);
        }
        this->addTable(t);
    }
    endTime(&this->creationTime);
    cout << "       Aplicando chaves primárias..." << endl;
    startTime();
    //define quais atributos irao compor as chaves primárias a partir da leitura das informações carregadas no vector<vector<string>> alterTables
    for(vector<vector<string>>::iterator table=alterTables.begin(); table != alterTables.end(); table++){
        vector<string> attribs;
        string nameTable = *table->begin();
        for(vector<string>::iterator value = ++table->begin(); value != table->end(); value++){
            attribs.push_back(*value);
        }
        this->getTable(nameTable)->applyPrimaryKey(attribs);
    }
    endTime(&this->creationTime);
    cout << "       Inserindo registros nas tabelas..." << endl;
    startTime();
    //insere os registros em suas respectivas tabelas que a partir da leitura das informações carregadas no vector<vector<vector<string>>> copyTables
    //foi necessário inverter com o laço anterior porque só é possivel inserir na árvore sabendo quais campos são chave primária
    for(vector<vector<vector<string>>>::iterator it=copyTables.begin(); it != copyTables.end(); it++){
        string nameTable;
        vector<string> attribs;
        for(vector<vector<string>>::iterator i=it->begin(); i != it->end(); i++){
            if (i == it->begin()){
                nameTable = *i->begin();
                for(vector<string>::iterator value = ++i->begin(); value != i->end(); value++)
                    attribs.push_back(*value);
            } else {
                Element *element = new Element();
                int count = 0;
                for(vector<string>::iterator value = i->begin(); value != i->end(); value++){
                    element->addField(attribs[count], *value);
                    element->setPrimaryKey(this->getTable(nameTable)->getFirstAttribute());
                    count++;
                }
                this->getTable(nameTable)->addElement(element);
            }
        }
    }
    endTime(&this->creationTime);
    cout << "       Finalizado." << endl;
    cout << endl;
    cout << "       Tempo de criação da estrutura: " << this->creationTime << " segundos." << endl;
}

void Database::startTime(){
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->timeStart);
}

void Database::endTime(double *var){
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->timeEnd);
    *var += (this->timeEnd.tv_sec - this->timeStart.tv_sec) + (this->timeEnd.tv_nsec - this->timeStart.tv_nsec) / 1e9;
}
