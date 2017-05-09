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
    Table *table = new Table("table");
    for (int i=0; i<5; i++){
        if (i!=0)
            table->addAttribute("campo"+to_string(i));
        else
            table->addAttribute("key", true);
    }
    for (int i=0; i<11; i++){
        Element *element = new Element();
        element->addField("key", to_string(i));
        element->addField("campo2", "valor2");
        element->addField("campo3", "valor3");
        element->addField("campo4", "valor4");
        element->addField("campo5", "valor5");
        element->setPrimaryKey(table->getFirstAttribute());
        table->addElement(element);
    }
    //Menu::showHeader();
    Database database;
    database.addTable(table);
    //Menu::showMainMenu(&database);
    
        
    return 0;
}
