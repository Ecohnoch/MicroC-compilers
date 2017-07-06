#ifndef TABLE_H
#define TABLE_H

#include "parser.h"
#include <iostream>
#include <stack>
#include <map>
using namespace std;

class STable
{
public:
    class TableInfo{
    public:
        string type = "INT";
        int scope;
        int val;
    };
    stack<map<string, TableInfo>> tableStack;
    STable();
    void addItem();
    void popItem();
    map<string, TableInfo> topItem();

};

#endif // TABLE_H
