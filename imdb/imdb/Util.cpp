//
//  Types.cpp
//  imdb
//
//  Created by Thomás Marques on 10/05/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//


#include <iostream>
#include "Util.hpp"

string trim(std::string & str){
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

string removeCharsFromString(const string str, char* charsToRemove){
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

string toUpper(string strToConvert){
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
    return strToConvert;
}

void split(const std::string& str, std::vector<std::string>& v) {
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

void printVector(vector<string> list){
    for(vector<string>::iterator it = list.begin(); it != list.end(); it++) {
        cout << "       " << *it << endl;
    }
}

/*
 Parser sql de COUNT(*) quando há um WHERE na query
 */
void parserSelectWhere(vector<string>::iterator word, bool& selectAll, string& nameField, string& valueField){
    string afterTableName = *(word+1);
    if ((afterTableName.empty() || *(word->end()-1) == ';')){//não existe mais tabelas ou termina com ';'
        selectAll = true;
    } else if ((afterTableName.compare("WHERE") == 0)){
        nameField = "";
        valueField = "";
        word += 2;
        if (word->find("=") != string::npos) {//não existe espaços antes e depois do '='
            string str = *word;
            vector<char>::iterator it = str.begin();
            while(*it != '='){
                nameField += *it;
                it++;
            }
            nameField = removeCharsFromString(nameField,"\"(,);");
            it++;
            while(it != str.end()){
                valueField +=*it;
                it++;
            }
            valueField = removeCharsFromString(valueField, "\"(,);");
        } else {// espera espaços antes e depois do '='
            nameField = removeCharsFromString(*word,"\"(,);");;
            valueField = removeCharsFromString(*(word+2), "\"(,);");
        }
    }
}

/*
 Parser sql dos joins
 */
void parserSelectJoin(vector<string>::iterator word, string& tableName2, string& nameT1, string& nameA1, string& nameT2, string& nameA2){
    word += 2;
    tableName2 = *word;
    word++;
    if (toUpper(*word).compare("ON") == 0) {
        word++;
        if (word->find("=") != string::npos) {//não existe espaços antes e depois do '='
            nameT1 = "";
            nameA1 = "";
            nameT2 = "";
            nameA2 = "";
            string str = *word;
            vector<char>::iterator it = str.begin();
            while(*it != '.'){
                nameT1 += *it;
                it++;
            }
            nameT1 = removeCharsFromString(nameT1,"\"(,);");
            it++;
            while(*it != '='){
                nameA1 += *it;
                it++;
            }
            nameA1 = removeCharsFromString(nameA1, "\"(,);");
            it++;
            while(*it != '.'){
                nameT2 += *it;
                it++;
            }
            nameT2 = removeCharsFromString(nameT2,"\"(,);=");
            it++;
            while(*it != '.'){
                nameA2 += *it;
                it++;
            }
            nameA2 = removeCharsFromString(nameA2,"\"(,);=");
        } else { //existe espaços entre o '='
            nameT1 = "";
            nameA1 = "";
            nameT2 = "";
            nameA2 = "";
            string str = *word;
            vector<char>::iterator it = (*word).begin();
            while(*it != '.'){
                nameT1 += *it;
                it++;
            }
            nameT1 = removeCharsFromString(nameT1,"\"(,);=");
            it++;
            while(*it != '='){
                nameA1 += *it;
                it++;
            }
            nameA1 = removeCharsFromString(nameA1, "\"(,);=");
            word += 2;
            str = *word;
            it = str.begin();
            while(*it != '.'){
                nameT2 += *it;
                it++;
            }
            nameT2 = removeCharsFromString(nameT2,"\"(,);=");
            it++;
            while(it != str.end()){
                nameA2 += *it;
                it++;
            }
            nameA2 = removeCharsFromString(nameA2, "\"(,);=");
        }
    }

}
