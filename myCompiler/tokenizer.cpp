#include "tokenizer.h"

Tokenizer::Tokenizer(){
    start = 0;
}

bool Tokenizer::isLetter(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') return true;
    return false;
}

bool Tokenizer::isDigit(char c){
    if(c >= '0' && c <= '9') return true;
    return false;
}

bool Tokenizer::isID(string s){
    if(!isLetter(s.at(0))) return false;
    int l = s.length();
    for(int i = 0; i < l; ++i)
        if((!isLetter(s.at(i))) && (!isDigit(s.at(i)))) return false;
    return true;
}

bool Tokenizer::isNum(string s){
    int i = 0, l = s.length();
    while(i < l){
        if(!isDigit(s.at(i))) return false;
        i++;
    }
    return true;
}

bool Tokenizer::isSimbol(string s){
    for(auto item : simbol)
        if(s == item)
            return true;
    return false;
}

bool Tokenizer::isKeywords(string s){
    for(auto item : keywords)
        if(s == item)
            return true;
    return false;
}

void Tokenizer::setStart(int s){
    start = s;
}
//----------------------------------------
//               private
//
//
//                public
//----------------------------------------
void Tokenizer::getSourceCode(string s){
    sourceCode = s;
}

Tokenizer::Token Tokenizer::getNextToken(){
    Token token;
    State s = START_STATE;

    while (s != DONE_STATE){
        if(start > sourceCode.size()){
            s = ERROR_STATE;
        }
        char ch = sourceCode[start++];
        string chSubstitute = "";
        chSubstitute = chSubstitute + ch;

        switch (s) {
        case START_STATE:
            if(isLetter(ch)){
                s = ID_STATE;
                token.name = token.name + ch;
                token.type = ID;
                break;
            }else if(isDigit(ch)){
                s = NUM_STATE;
                token.name = token.name + ch;
                token.type = INT;
                break;
            }else if(isSimbol(chSubstitute) || ch == '&' || ch == '|'){
                s = SIMBOL_STATE;
                token.name = token.name + ch;
                token.type = SIMBOL;
                break;
            }
            break;

        case SIMBOL_STATE:
            if(!isSimbol(token.name + chSubstitute)){
                s = DONE_STATE;
                start --;
                break;
            }else{
                token.name = token.name + ch;
                break;
            }
            break;
        case ID_STATE:
            if(isLetter(ch) || isDigit(ch)){
                token.name = token.name + ch;
                break;
            }else{
                if(isKeywords(token.name))
                    token.type = KEYWORD;
                s = DONE_STATE;
                start --;
                break;
            }
            break;
        case NUM_STATE:
            if(isDigit(ch)){
                token.name = token.name + ch;
                break;
            }else{
                s = DONE_STATE;
                start --;
                break;
            }
            break;
        case ERROR_STATE:
            s = DONE_STATE;
            token.name = "EOF";
            token.type = EOFTYPE;
        default:
            break;
        }
    }
    return token;
}

vector<Tokenizer::Token> Tokenizer::getAllTokens(){
    vector<Token> ans;
    Token next = getNextToken();
    if(next.type == EOFTYPE){
        ans.push_back(next);
        return ans;
    }
    while(next.type != EOFTYPE){
        ans.push_back(next);
        next = getNextToken();
    }
    ans.push_back(next);
    return ans;
}

void Tokenizer::testGetAllTokens(){
    getSourceCode("if(c>b){c=c+1;}else{d = d+1;}");
    vector<Token> ans = getAllTokens();
    for(auto item : ans){
        cout<<item.name<<endl;
    }
}

void Tokenizer::testGetNextToken(){
    getSourceCode("if(c>b){c=c+1;}else{d = d-1;}");
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
    cout<<getNextToken().name<<endl;
}
