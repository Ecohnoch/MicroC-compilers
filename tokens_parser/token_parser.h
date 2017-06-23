#ifndef TOKEN_PARSER_H
#define TOKEN_PARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;
class tokens{
public:
    string token_name;
    int token_num;
    static int idNum;
    tokens(string tn, int tnum): token_name(tn), token_num(tnum){}
    void set(string tn, int tnum){token_name = tn; token_num = tnum;}
    void show(){cout<<"tokenName: "<< token_name<< " token_num: "<< token_num<<endl;}
};
class token_parser{
public:
    bool isLetter(char c);
    bool isDigit(char c);
    bool isNum(string s);
    bool isKeywords(string s);
    int getKeywordsNum(string s);
    bool isID(string s);
    void parser(string &s);
    void trim(string &s);
    string getInput(string filename = "./input.txt");
    string input;
};

#endif // TOKEN_PARSER_H
