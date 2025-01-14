#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const char DELIMITER='/';
const char DELIMITER_SPACE=' ';
const char DELIMITER_COMMA=',';
const char DELIMITER_SIMIC=';';
const char DELIMITER_YA='|';
const char DELIMITER_2_DOT=':';
const string CMD_POST="POST";
const string CMD_GET="GET";
const string CMD_PUT="PUT";
const string CMD_DELETE="DELETE";

const int DE_ACTIVE=0;
const int ACTIVE=1;

const int WRONG_CMD=-1;
const int CMD_SIGNUP=11;
const int CMD_LOGIN=12;
const int CMD_LOGOUT=13;
const int CMD_FULL_DISTRICTS=21;
const int CMD_DISTRICTS=211;
const int CMD_PUT_DISTRICT=31;
const int CMD_RESTAURANTS_WITHOUT_FOODNAME=221;
const int CMD_RESTAURANTS_WITH_FOODNAME=22;
const int CMD_RESERVE_WITHOUT_FOOD=141;
const int CMD_RESERVE_WITH_FOOD=14;
const int CMD_RESTAURANT_DETAIL=23;
const int CMD_INFO_CLIENT=26;
const int CMD_DELETE_M=4;
const int CMD_INCREASE_BUDGET=115;
const int CMD_SHOW_BUDGET=2111;



