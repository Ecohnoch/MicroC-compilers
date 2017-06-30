#include "transfer.h"

transfer::transfer(){

}

void transfer::getSourcecode(QString sourcecode){
    sourceCode = sourcecode.toStdString();
}

vector<Tokenizer::Token> transfer::getTokens(QString sourcecode){
    Tokenizer tokenizer;
    getSourcecode(sourcecode);
    tokenizer.getSourceCode(sourceCode);
    return tokenizer.getAllTokens();
}

Parser::TreeNode* transfer::getParserTree(QString sourcecode){
    Parser parser;
    return parser.parseMainStatement(getTokens(sourcecode));
}

QString transfer::tokensToJSON(QString sourcecode){
    vector<Tokenizer::Token> tokens = getTokens(sourcecode);
    int length = tokens.size();
    string ans;
    ans = ans + "{";
    for(int i = 0; i < length; ++i){
        ans = ans + "\"";
        ans = ans + to_string(i);
        ans = ans + "\"";
        ans = ans + ":";
        ans = ans + "\"";
        ans = ans + tokens.at(i).name;
        ans = ans + "\"";
        if(i != length - 1)
            ans = ans + ",";
    }
    ans = ans + "}";
    return QString::fromStdString(ans);
}

void transfer::recursion(Parser::TreeNode *tree, string& s){
    static int indentno = 0;
    indentno += 1;
    if (tree != nullptr){
        s = s + "{";
        s = s + "\"";
        s = s + to_string(indentno);
        s = s + "\"";
        s = s + ":";
        s = s + "[";

        switch (tree->nodetype){
        case Parser::STYPE:
            s = s + "\"";
            s = s + "S";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::LTYPE:
            s = s + "\"";
            s = s + "L";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::BOOLTYPE:
            s = s + "\"";
            s = s + "BOOL";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::STATEMENTTYPE:
            s = s + "\"";
            s = s + "STATEMENT";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::BTYPE:
            s = s + "\"";
            s = s + "B";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::ATYPE:
            s = s + "\"";
            s = s + "A";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::OTYPE:
            s = s + "\"";
            s = s + "O";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::ETYPE:
            s = s + "\"";
            s = s + "E";
            s = s + "\"";
            s = s + ",";
            break;
        case Parser::TERMITYPE:
            s = s + "\"";
            s = s + tree->token.name;
            s = s + "\"";
            s = s + ",";
            break;
        }
        recursion(tree->child[0], s);
        recursion(tree->child[1], s);
        recursion(tree->child[2], s);
        recursion(tree->child[3], s);
        recursion(tree->child[4], s);
        s.erase(s.length() - 1);
        s = s + "]},";
    }
    indentno -= 1;
}

QString transfer::parserToJSON(QString sourcecode){
    Parser::TreeNode* syntaxTree = getParserTree(sourcecode);
    string ans;
    recursion(syntaxTree, ans);
    ans.erase(ans.length() - 1);
    return QString::fromStdString(ans);
}

void transfer::test(){
    string s = "if((5>3)&&(a<b)||!(6)){(3+5*2+6*(3+7)*2+3*3);}else{c+1;while(5<3){3+3;}}";
    QString ss = tokensToJSON(QString::fromStdString(s));
    cout<<ss.toStdString()<<endl;
}




