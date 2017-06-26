#include <iostream>
#include "token_parser.h"

//int tokens::idNum = 0;
//map<string, int> ids;

bool token_parser::isLetter(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-' || c == '_') return true;
    return false;
}

bool token_parser::isDigit(char c){
    if(c >= '0' && c <= '9') return true;
    return false;
}

bool token_parser::isNum(string s){
    int i = 0, l = s.length();
    while(i < l){
        if(!isDigit(s.at(i))) return false;
        i++;
    }
    return true;
}

bool token_parser::isKeywords(string s){
    for(auto item: keywords){
        if(s == item)
            return true;
    }
    return false;
}

int token_parser::getKeywordsNum(string s){
    if(!isKeywords(s))
        return -1;
    if(s == "if")
        return 0;
    if(s == "else")
        return 1;
    if(s == "while")
        return 2;
    return -1;
}

bool token_parser::isID(string s){
    if(!isLetter(s.at(0))) return false;
    int l = s.length();
    for(int i = 0; i < l; ++i)
        if((!isLetter(s.at(i))) && (!isDigit(s.at(i)))) return false;
    return true;
}

void token_parser::parser(string &s){
    ans.clear();
    ids.clear();
    tokens::idNum = 0;

    int start = 0, end = 0;
    int l = s.length();
    while(start <= l - 1){
        bool jumpOut = false;
        bool jumpOut2 = false;
        if(isLetter(s[start])){
            string ifID = "";
            ifID = ifID + s[start];
            start ++;
            while(isID(ifID)){
                if(start > l - 1){
                    if(isKeywords(ifID))
                        ans.push_back(tokens(ifID, getKeywordsNum(ifID)));
                    else{
                        map<string, int>::iterator it;
                        it = ids.find(ifID);
                        if(it == ids.end()){
                            ans.push_back(tokens(ifID, tokens::idNum));
                            ids.insert(map<string, int>::value_type(ifID, tokens::idNum));
                            tokens::idNum ++;
                        }else{
                            ans.push_back(tokens(it->first, it->second));
                        }
                    }
                    jumpOut = true;
                    break;
                }
                ifID = ifID + s[start];
                start ++;
            }
            if(jumpOut)
                break;

            ifID.erase(ifID.length() - 1);
            start --;

            if(isKeywords(ifID))
                ans.push_back(tokens(ifID, getKeywordsNum(ifID)));
            else{
                map<string, int>::iterator it;
                it = ids.find(ifID);
                if(it == ids.end()){
                    ans.push_back(tokens(ifID, tokens::idNum));
                    ids.insert(map<string, int>::value_type(ifID, tokens::idNum));
                    tokens::idNum ++;
                }else{
                    ans.push_back(tokens(it->first, it->second));
                }
            }
        }else if(isDigit(s[start])){
            string ifNum = "";
            ifNum = ifNum + s[start];
            start ++;
            while(isNum(ifNum)){
                if(start > l - 1){
                    int xl = ifNum.length(), x = 0;
                    for(int i = 0; i < xl; ++i){
                        int ten = 1;
                        for(int j = 0; j < i; ++j){
                            ten *= 10;
                        }
                        x += (ifNum.at(i) - '0') * ten;
                    }
                    jumpOut2 = true;
                    break;
                }
                ifNum = ifNum + s[start];
                start ++;
            }
            if(jumpOut2)
                break;
            ifNum.erase(ifNum.length() - 1);
            start --;
            int xl = ifNum.length(), x = 0;
            for(int i = 0; i < xl; ++i){
                int ten = 1;
                for(int j = 0; j < i; ++j){
                    ten *= 10;
                }
                x += (ifNum.at(i) - '0') * ten;
            }
            ans.push_back(tokens("const", x));
        }else{
            switch (s[start]) {
            case '{':
                ans.push_back(tokens("{", 3));
                break;
            case '}':
                ans.push_back(tokens("}", 4));
                break;
            case ';':
                ans.push_back(tokens(";", 6));
                break;
            case '#':
                ans.push_back(tokens("#", 8));
                break;
            case '+':
                ans.push_back(tokens("+", 14));
                break;
            case '*':
                ans.push_back(tokens("*", 15));
                break;
            case '=':
                if((start + 1) > l - 1){
                    ans.push_back(tokens("=", 16));
                    break;
                }
                if(s[start + 1] == '='){
                    ans.push_back(tokens("rop", 20));
                    start ++;
                    break;
                }
                ans.push_back(tokens("=", 16));
                break;
            case '&':
                if((start + 1) > l - 1)
                    break;
                if(s[start + 1] == '&'){
                    ans.push_back(tokens("&&", 17));
                    start ++;
                    break;
                }
                break;
            case '|':
                if((start + 1) > l - 1)
                    break;
                if(s[start + 1] == '|'){
                    ans.push_back(tokens("||", 18));
                    start ++;
                    break;
                }
                break;
            case '!':
                ans.push_back(tokens("!", 19));
                break;
            case '>':
                if((start + 1) > l - 1)
                    break;
                if(s[start + 1] == '='){
                    ans.push_back(tokens("rop", 20));
                    start ++;
                    break;
                }
                ans.push_back(tokens("rop", 20));
                break;
            case '<':
                if((start + 1) > l - 1)
                    break;
                if(s[start + 1] == '='){
                    ans.push_back(tokens("rop", 20));
                    start ++;
                    break;
                }
                ans.push_back(tokens("rop", 20));
                break;
            case '(':
                ans.push_back(tokens("(", 21));
                break;
            case ')':
                ans.push_back(tokens(")", 22));
                break;
            default:
                break;
            }
            start ++;
        }

    }
    for(int i = 0; i < ans.size(); ++i){
        cout<< i<<": ";
        ans.at(i).show();
    }
}


void token_parser::trim(string &s){
    int pos = 0;
    if(!s.empty()){
        while(s.find(' ') != string::npos){
            pos = s.find(' ');
            s.erase(pos, 1);
        }
        while(s.find('\n') != string::npos){
            pos = s.find('\n');
            s.erase(pos, 1);
        }
    }
}

string token_parser::getInput(string filename){
//    string ans = "";
//    ifstream inputFile(filename);
//    if(!inputFile){
//        cout<<"*** Error, not find this file."<<endl;
//        return "*** Error, not find this file";
//    }
//    while(!inputFile.eof()){
//        string s;
//        getline(inputFile, s);
//        trim(s);
//        ans = ans + s;
//    }
//    inputFile.close();
//    trim(ans);
    string ans = "";

    return ans;
}

QString token_parser::toJSON(){
    string x = input;
    parser(x);
    string thisAns;
    thisAns += "{";
    for(int i = 0; i < ans.size(); ++i){
        thisAns += "\"";
        thisAns += to_string(i) + "";
        thisAns += "\":{";
        thisAns += "\"token_name\":\"" + ans.at(i).token_name + "\",";
        thisAns += "\"token_num\" :";
        thisAns += to_string(ans.at(i).token_num);
        thisAns += "}";
        if(i != ans.size() - 1){
            thisAns += ",";
        }
    }
    thisAns += "}";
    return QString::fromStdString(thisAns);
}

void token_parser::getSourcecode(QString sourceCode){
    string ans = sourceCode.toStdString();
    input = ans;
}


