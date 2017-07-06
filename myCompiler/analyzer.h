#ifndef ANALYZER_H
#define ANALYZER_H
#include <iostream>
#include "parser.h"
#include "table.h"
using namespace std;
class Analyzer
{
public:
    Analyzer();
    Parser::TreeNode* getTreeNode(string sourcecode);
    Parser::TreeNode* getTreeNode(vector<Tokenizer::Token> tokens);

    class Output{
    public:
        string name;
        int val;
    };

    vector<Output> output;
    void doMainStatement(Parser::TreeNode*);
    void doAssignStatements(Parser::TreeNode*);
    int doCalculateStatement (Parser::TreeNode*);
    bool doBoolStatement(Parser::TreeNode*);
    void treeOrder(Parser::TreeNode* );
    void testDoBoolStatement();
    void testDoAssignStatement();
    void test();
    void outputOutput();
private:
    STable stable;
};

#endif // ANALYZER_H
