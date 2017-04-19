//
//  main.cpp
//  imdb
//
//  Created by Thomás Marques on 11/04/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>

#include "Database.hpp"
#include "Table.hpp"
#include "Element.hpp"
#include "Field.hpp"

using namespace std;

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

string removeCharsFromString(const string str, char* charsToRemove ) {
    char c[str.length()+1]; // + terminating char
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

void print(vector<string> list) {
    for(int i=0; i < list.size(); i++){
        cout<<list[i]<<endl;
    }
}

Database* readFile(string pathFile){
    Database database;
    
    string line;
    ifstream myfile (pathFile);
    bool mustRead = false;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            if (isdigit(*line.begin()) || isalpha(*line.begin())) {
                string name_table;
                vector<string> fields;
                vector<string> listAttrib;
                split(line,fields);
                for (vector<string>::iterator field=fields.begin(); field!=fields.end(); ++field) {
                    if (*field == "COPY") {
                        field++;
                        name_table = *field;
//                        cout<<name_table<<endl;
                        field++;
                        string name_attrib = *field;
                        if (name_attrib.find('(') != string::npos){
                            listAttrib.clear();
                            while (name_attrib.find(')') == string::npos){
                                listAttrib.push_back(removeCharsFromString(name_attrib, "\"(,"));
                                field++;
                                name_attrib = *field;
                            }
                            listAttrib.push_back(removeCharsFromString(name_attrib, "\"(,)"));
//                            print(listAttrib);
                        }
                        field++;
                    } else if(*field == "stdin;"){
                        getline(myfile,line);
                        mustRead = true;
                    }
                }
                if (mustRead) {
                    //                    cout<<line<<endl;
                }
            } else if (line.substr(0,2) == "\\."){
                mustRead = false;
                //                cout<<"PARAR DE LER"<<endl;
            }
        }
        myfile.close();
    } else
        cout << "Erro ao abrir o arquivo";
    
    return &database;
}

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
  
    Database *database = readFile("file.txt");
    
    if (database == NULL) {
        cout<<"ERRO ao criar banco"<<endl;
    } else {
        cout<<"Total de tabelas: "<<database->getAmountTables()<<endl;
    }
    
    return 0;
}
