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
    Menu::showHeader();
    Menu::showMainMenu(&database);
    
        
    return 0;
}
