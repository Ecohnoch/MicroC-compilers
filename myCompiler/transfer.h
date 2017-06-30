#ifndef TRANSFER_H
#define TRANSFER_H
#include <iostream>
#include <QObject>
#include <vector>
#include "tokenizer.h"
#include "parser.h"
using namespace std;

class transfer: public QObject
{
    Q_OBJECT
public:
    transfer();

signals:
    void doTokens();
    void doParser();
    void doSimbolTable();
    void doAnalyser();

public slots:
    void getSourcecode(QString sourcecode);
    vector<Tokenizer::Token> getTokens(QString sourcecode);
    Parser::TreeNode* getParserTree(QString sourcecode);
    void recursion(Parser::TreeNode*, string &s);
    QString parserToJSON(QString sourcecode);
    QString tokensToJSON(QString sourcecode);

    void test();
private:
    string sourceCode;

};

#endif // TRANSFER_H
