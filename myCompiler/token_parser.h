#ifndef TOKEN_PARSER_H
#define TOKEN_PARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <QObject>
#include <QList>

using namespace std;
class tokens{//: public QObject{
    // Q_OBJECT
public:
    string token_name;
    int token_num;
    static int idNum;
    tokens(string tn = "", int tnum = 0): token_name(tn), token_num(tnum){}
    void set(string tn, int tnum){token_name = tn; token_num = tnum;}
    void show(){cout<<"tokenName: "<< token_name<< " token_num: "<< token_num<<endl;}
};
class token_parser: public QObject{
    Q_OBJECT
signals:
    void doParse();

public slots:
    // parser, output the ans.   basicElement: <tokenName, tokenNum>
    void parser(string &s);
    // output the input, get the source codes from a txt
    string getInput(string filename = "./input.txt");
    void getSourcecode(QString sourceCode);
    QString toJSON();
public:

    // judge if(ch == letter)    letter: a_z, A_Z, -, _
    bool isLetter(char c);
    // judge if(ch == digit)     digit: 0-9
    bool isDigit(char c);
    // judge if(str== num)       num: 0 - 2147483648
    bool isNum(string s);
    // judge if(str== key)       key: keywords, see private
    bool isKeywords(string s);
    // get the num of keywords
    int getKeywordsNum(string s);
    // judge if(str == ID)       id: letter(letter|digit)*
    bool isID(string s);
    // trim, cut off all ' ' and '\n' in the source codes
    void trim(string &s);
    // source code after trim
public:
    string input;
    // tokens flow
    vector<tokens> ans;
    // ids table
    map<string, int> ids;

private:
    // all keywords
    string keywords[20] = {"if", "else", "while"};
};

#endif // TOKEN_PARSER_H