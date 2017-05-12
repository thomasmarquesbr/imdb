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

class Menu;

#include "Database.hpp"

class Menu{
public:
    static void showHeader(); //Cabeçalho
    static void showMainMenu(Database *database); //Menu Inicial
    static void showMenuDatabase(Database *database); //Menu de informações sobre o banco de dados
    static void showMenuTables(Database *database); //Menu de informações sobre as tabelas
    static void showMenuSearchTable(Table *table); //Menu de informações sobre uma tabela acessada
};

#endif /* Menu_hpp */
