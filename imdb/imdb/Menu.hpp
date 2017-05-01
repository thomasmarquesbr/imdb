//
//  Menu.hpp
//  imdb
//
//  Created by Thomás Marques on 01/05/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include "Database.hpp"

class Menu {
public:
    static void showHeader();
    static void showMainMenu(Database *database);
    static void showMenuDatabase(Database *database);
    static void showMenuTables(Database *database);
    static void showMenuSearchTable(Table *table);
};

#endif /* Menu_hpp */
