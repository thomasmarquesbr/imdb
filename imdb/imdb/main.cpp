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
    Element *element1 = new Element();
    element1->addField("campo1", "lkjoijoijlijlijlijlijlij");
    element1->addField("campo2", "aeskalja");
    element1->addField("campo3", "lasejs");
    element1->addField("campo4", "aseklajel");
    element1->addField("campo5", "lasjalkj");
    element1->setPrimaryKey(table->getFirstAttribute());
    table->addElement(element1);

    Element *element2 = new Element();
    element2->addField("campo1", "teste2");
    element2->addField("campo2", "valoalsejr2");
    element2->addField("campo3", "asleaj");
    element2->addField("campo4", "qowuieoq");
    element2->addField("campo5", "zbmznxbz");
    element2->setPrimaryKey(table->getFirstAttribute());
    table->addElement(element2);
    
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
    
    Element *element3 = new Element();
    element3->addField("key", "asleaj0lk");
    element3->addField("campo1", "maça");
    element3->addField("campo2", "aeskalja");
    element3->setPrimaryKey(table2->getFirstAttribute());
    table2->addElement(element3);
    
    Element *element4 = new Element();
    element4->addField("key", "asleaj");
    element4->addField("campo1", "banana");
    element4->addField("campo2", "valoalsejr2");
    element4->setPrimaryKey(table2->getFirstAttribute());
    table2->addElement(element4);
//    cout << (table2->getAttribute("campo2")->getTableReference() != NULL) << endl;
//    Menu::showHeader();
    
    database.addTable(table2);
    Menu::showMainMenu(&database);
    
        
    return 0;
}
