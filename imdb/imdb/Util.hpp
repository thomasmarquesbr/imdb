//
//  Util.hpp
//  imdb
//
//  Created by Thomás Marques on 10/05/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <stdio.h>

using namespace std;

enum Direction {
    LEFT  = 0,
    RIGHT = 1,
    EQUAL = 2,
};

string trim(std::string & str);

string removeCharsFromString(const string str, char* charsToRemove);

string toUpper(string strToConvert);

void split(const std::string& str, std::vector<std::string>& v);

void parserSelectWhere(vector<string>::iterator word, bool& selectAll, string& nameField, string& valueField);

void parserSelectJoin(vector<string>::iterator word, string& tableName2, string& nameT1, string& nameA1, string& nameT2, string& nameA2);

#endif /* Util_hpp */
