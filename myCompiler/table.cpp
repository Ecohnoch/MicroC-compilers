#include "table.h"

STable::STable()
{
    addItem();
}

void STable::addItem(){
    map<string, TableInfo> tmp;
    tableStack.push(tmp);
}

void STable::popItem(){
    tableStack.pop();
}

map<string, STable::TableInfo> STable::topItem(){
    return tableStack.top();
}


