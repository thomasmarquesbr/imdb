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

#include "Menu.hpp"
#include "Database.hpp"
#include "Table.hpp"
#include "Element.hpp"
#include "Field.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    Database database;
    Table *table = new Table("table");
    for (int i=0; i<5; i++){
        if (i!=0)
            table->addAttribute("campo"+to_string(i+1));
        else
            table->addAttribute("campo"+to_string(i+1), true);
    }
    for (int i=0; i<11; i++){
        Element *element = new Element();
        element->addField("campo1", "valor"+to_string(i));
//        if (i % 2 == 0)
            element->addField("campo2", "valor2");
        element->addField("campo3", "valor3");
        element->addField("campo4", "valor4");
        element->addField("campo5", "valor5");
        element->setPrimaryKey(table->getFirstAttribute());
        table->addElement(element);
    }
    
    
    database.addTable(table);
    
    
    
    Table *table2 = new Table("table2");
    for (int i=0; i<3; i++){
        if (i!=0)
            table2->addAttribute("campo"+to_string(i));
        else
            table2->addAttribute("key", true);
    }
    vector<string> listAttribs;
    listAttribs.push_back("campo1");
    vector<string> listTables;
    listTables.push_back("table");
    table2->applyForeignKey(&database, listAttribs, listTables);
    
    for (int i=0; i<11; i++){
        Element *element = new Element();
        element->addField("key", to_string(i));
        element->addField("campo1", "valor"+to_string(i));
        element->addField("campo2", "valor2");
        element->setPrimaryKey(table2->getFirstAttribute());
        table2->addElement(element);
    }
    
    Element *element1 = new Element();
    element1->addField("key", "lasejs");
    element1->addField("campo1", "lkjoijoijlijlijlijlijlij");
    element1->addField("campo2", "aeskalja");
    element1->setPrimaryKey(table->getFirstAttribute());
    table2->addElement(element1);
    
    Element *element2 = new Element();
    element2->addField("key", "lasejs");
    element2->addField("campo1", "ASDLKA");
    element2->addField("campo2", "valoalsejr2");
    element2->setPrimaryKey(table->getFirstAttribute());
    table2->addElement(element2);
//    cout << (table2->getAttribute("campo2")->getTableReference() != NULL) << endl;
//    Menu::showHeader();
    
    database.addTable(table2);
    Menu::showMainMenu(&database);
    
        
    return 0;
}
