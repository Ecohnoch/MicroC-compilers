#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Tokenizer
{
private:
    bool isLetter(char c);
    bool isDigit(char c);
    bool isID(string  s);
    bool isNum(string s);
    bool isSimbol(string s);
    bool isKeywords(string s);
    void setStart(int s);
    string keywords[50] = {"if", "else", "while"};
    string simbol[50] = {"{", "}", ";", "#", "+", "*", "=", "=="
              , "&&", "||", "!", ">", ">=", "<", "<=", "(", ")"};

    string sourceCode;
    int start;


public:
    enum State{
        START_STATE,
        ID_STATE,
        SIMBOL_STATE,
        NUM_STATE,
        DONE_STATE,
        ERROR_STATE
    };
    enum TokenType
    {
        NONE,
        KEYWORD,
        ID,
        INT,			// 整型数字
        BOOL,			// 布尔类型
        SIMBOL,         // 合法的符号
        ERROR,		    // 错误
        EOFTYPE	    // 文件结束
    };
    struct Token{
        string name;
        TokenType type;
    };
    Tokenizer();
    void getSourceCode(string s);
    Token getNextToken();
    vector<Token> getAllTokens();

    void testGetNextToken();
    void testGetAllTokens();

};

#endif // TOKENIZER_H
