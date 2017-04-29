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
#include <cstdlib>
#include <cmath>

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

//Database* readFile(string pathFile){
//    Database database;
//    
//    string line;
//    ifstream myfile (pathFile);
//    bool mustRead = false;
//    bool mustConstructTable = false;
//    if (myfile.is_open()) {
//        while (getline(myfile,line)) {
//            if (isdigit(*line.begin()) || isalpha(*line.begin())) {
//                string name_table;
//                vector<string> fields;
//                vector<string> listAttrib;
//                split(line,fields);
//                for (vector<string>::iterator field=fields.begin(); field!=fields.end(); ++field) {
//                    if (*field == "CREATE"){
//                        field += 2;
//                        string name_table = *field;
//                        getline(myfile,line);
//                    }
//                    if (*field == "COPY") {
//                        field++;
////                        name_table = *field;
////                        cout<<name_table<<endl;
//                        field++;
//                        string name_attrib = *field;
//                        if (name_attrib.find('(') != string::npos){
//                            listAttrib.clear();
//                            while (name_attrib.find(')') == string::npos){
//                                listAttrib.push_back(removeCharsFromString(name_attrib, "\"(,"));
//                                field++;
//                                name_attrib = *field;
//                            }
//                            listAttrib.push_back(removeCharsFromString(name_attrib, "\"(,)"));
////                            print(listAttrib);
//                        }
//                        field++;
//                    } else if(*field == "stdin;"){
//                        getline(myfile,line);
//                        mustRead = true;
//                    }
//                }
//                if (mustRead) {
//                    //                    cout<<line<<endl;
//                }
//            } else if (line.substr(0,2) == "\\."){
//                mustRead = false;
//                //                cout<<"PARAR DE LER"<<endl;
//            }
//        }
//        myfile.close();
//    } else
//        cout << "Erro ao abrir o arquivo";
//    
//    return &database;
//}



void readFiles(string pathFile) {
    string line;
    ifstream myFile(pathFile);
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

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
  
    //readFiles("file.txt");
    
//    Element element;
//    element.addField("campo1", "valor1");
//    element.addField("campo2", "valor2");
//    element.addField("campo3", "valor3");
//    
//    Element element2;
//    element2.addField("campo4", "valor4");
//    element2.addField("campo5", "valor5");
//    element2.addField("campo6", "valor6");
    
//    Element element;
    Database database;
    
//    int count = 1;
//    for(int i=0; i<3; i++){//tabelas
//        Table *table = new Table("table"+to_string(i));
//        table->addAttribute("attribute"+to_string(i+count));
//        count++;
//        table->addAttribute("attribute"+to_string(i+count));
//        count++;
//        table->addAttribute("attribute"+to_string(i+count));
//        count++;
//        
//        int count2 = 1;
//        for(int j=0; j<40; j++){
//            Element *element = new Element();
//            element->addField("campo"+to_string(j), "valor"+to_string(j));
//            count2++;
//            element->addField("campo"+to_string(j+count2), "valor"+to_string(j+count2));
//            count2++;
//            element->addField("campo"+to_string(j+count2), "valor"+to_string(j+count2));
//            count2++;
//            table->addElement(element);
//            element = NULL;
//        }
//        table->drawTree();
//        database.addTable(table);
//    }
    
    Table *table = new Table("table");
    table->addAttribute("attribute1");
    table->addAttribute("attribute2");
    table->addAttribute("attribute3");
    
    int count2 = 0;
    for(int j=0; j<500; j++){
        Element *element = new Element();
        element->addField("campo"+to_string(j), "valor"+to_string(j));
        table->addElement(element);
        element = NULL;
    }
    table->drawTree();
    
    
    
//    Table *table = new Table("table");
//    table->addAttribute("a");
//    table->addAttribute("b");
//    table->addAttribute("c");
//    table->addAttribute("d");
//    
//    Element *element0 = new Element();
//    element0->addField("campo0", "valor0");
//    element0->addField("campo1", "valor1");
//    element0->addField("campo2", "valor2");
//    table->addElement(element0);
//    
//    Element *element1 = new Element();
//    element1->addField("campo1", "valor1");
//    table->addElement(element1);
//    
//    Element *element2 = new Element();
//    element2->addField("campo2", "valor2");
//    table->addElement(element2);
////
//    Element *element3 = new Element();
//    element3->addField("campo3", "valor3");
//    table->addElement(element3);
////
//    Element *element4 = new Element();
//    element4->addField("campo4", "valor4");
//    table->addElement(element4);
////    
//    Element *element5 = new Element();
//    element5->addField("campo5", "valor5");
//    table->addElement(element5);
////
//    Element *element6 = new Element();
//    element6->addField("campo6", "valor6");
//    table->addElement(element6);
//
//    Element *element7 = new Element();
//    element7->addField("campo7", "valor7");
//    table->addElement(element7);
//
//    Element *element8 = new Element();
//    element8->addField("campo8", "valor8");
//    table->addElement(element8);
//    
//    Element *element9 = new Element();
//    element9->addField("campo9", "valor9");
//    table->addElement(element9);
//
//    Element *element10 = new Element();
//    element10->addField("campo10", "valor10");
//    table->addElement(element10);
//
//    Element *element11 = new Element();
//    element11->addField("campo11", "valor11");
//    table->addElement(element11);
//
//    Element *element12 = new Element();
//    element12->addField("campo12", "valor12");
//    table->addElement(element12);
    
//    table->drawTree();
//    table->removeElement("valor3");
    cout << endl;
    cout << endl;
//    table->drawTree();
    
//    string val = "SD02";
////    int newValue = val[0] * pow(10, val.length()-1) + strtol(val.c_str()+1, NULL, 10);
//    char *chars = new char[val.length()+1];
//    strcpy(chars,val.c_str());
    
    
//    cout << chars <<endl;
    
//    table->removeElement("valor1");
//    table->drawTree();
    
    
//    cout << table->getAmountElements() <<endl;
    
//    table->printElementsPreOrdem();
    
//    cout << table->getRootElement()->getFirstField()->getName() << endl;
    
//    cout << table->getRootElement()->getLeftElement()->getFirstField()->getValue() << endl;
//    cout << table->getRootElement()->getRightElement()->getFirstField()->getValue() << endl;
    
    
    
//    cout<<element.getAmountFields()<<endl;
//    element.printFields();
    
    

    
    
//    Database *database = readFile("file.txt");
//    
//    if (database == NULL) {
//        cout<<"ERRO ao criar banco"<<endl;
//    } else {
//        cout<<"Total de tabelas: "<<database->getAmountTables()<<endl;
//    }
    
    return 0;
}
