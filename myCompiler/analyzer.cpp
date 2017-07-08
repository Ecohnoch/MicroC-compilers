#include "analyzer.h"
#include <stdlib.h>
Analyzer::Analyzer()
{

}


void Analyzer::treeOrder(Parser::TreeNode *tree){
    if(tree != nullptr){
        for(int i = 0; i < 5; ++i){
            treeOrder(tree->child[i]);
        }

        if(tree->token.type == Tokenizer::ID){
            map<string, STable::TableInfo>::iterator it = stable.tableStack.top().find(tree->token.name);
            if(it != stable.tableStack.top().end()){
                // do something
            }else{
                STable::TableInfo info;
                info.scope = stable.tableStack.size() - 1;
                info.val = 0;
                stable.tableStack.top()[tree->token.name] = info;
            }
        }
    }
}

Parser::TreeNode* Analyzer::getTreeNode(vector<Tokenizer::Token> tokens){
    Parser parser;
    return parser.parseMainStatement(tokens);
}

Parser::TreeNode* Analyzer::getTreeNode(string sourcecode){
    Tokenizer tokenizer;
    vector<Tokenizer::Token> tokens;
    tokenizer.getSourceCode(sourcecode);
    tokens = tokenizer.getAllTokens();
    return getTreeNode(tokens);
}

bool Analyzer::doBoolStatement(Parser::TreeNode *tree){
    if(tree != nullptr){
        if((tree->nodetype == Parser::BOOLTYPE) || (tree->nodetype == Parser::BTYPE)){
            if(tree->child[0]->nodetype == Parser::IDTYPE &&
               tree->child[1] == nullptr){
                if(tree->child[0]->token.type == Tokenizer::INT){
                    if(tree->child[0]->token.name != "0")
                        return true;
                }else{
                    map<string, STable::TableInfo>::iterator it = stable.tableStack.top().find(tree->child[0]->token.name);
                    if(it != stable.tableStack.top().end() && it->second.val != 0){
                        return true;
                    }else{
                        return false;
                    }
                }
            }else if(tree->child[1] != nullptr && tree->child[2] != nullptr &&
                     tree->child[0]->nodetype == Parser::IDTYPE && tree->child[1]->nodetype == Parser::ROPTYPE &&
                     tree->child[2]->nodetype == Parser::IDTYPE){
                int x, y;
                map<string, STable::TableInfo>::iterator it = stable.tableStack.top().find(tree->child[0]->token.name);
                if(it != stable.tableStack.top().end()){
                    x = it->second.val;
                }else{
                    x = 0;
                }
                it = stable.tableStack.top().find(tree->child[2]->token.name);
                if(it != stable.tableStack.top().end()){
                    y = it->second.val;
                }else{
                    y = 0;
                }

                if(tree->child[0]->token.type == Tokenizer::INT && tree->child[2]->token.type == Tokenizer::INT){
                    x = atol(tree->child[0]->token.name.c_str());
                    y = atol(tree->child[2]->token.name.c_str());
                }else if(tree->child[0]->token.type == Tokenizer::INT && tree->child[2]->token.type == Tokenizer::ID){
                    x = atol(tree->child[0]->token.name.c_str());
                }else if(tree->child[0]->token.type == Tokenizer::ID && tree->child[2]->token.type == Tokenizer::INT){
                    y = atol(tree->child[2]->token.name.c_str());
                }else if(tree->child[0]->token.type == Tokenizer::ID && tree->child[2]->token.type == Tokenizer::ID){
                    // do nothing
                }
                if(tree->child[1]->token.name == ">" && x > y){
                    return true;
                }else if(tree->child[1]->token.name == ">=" && x >= y){
                    return true;
                }else if(tree->child[1]->token.name == "<" && x < y){
                    return true;
                }else if(tree->child[1]->token.name == "<=" && x <= y){
                    return true;
                }else if(tree->child[1]->token.name == "==" && x == y){
                    return true;
                }else
                    return false;
            }else if(tree->child[1] != nullptr && tree->child[2] != nullptr &&
                     tree->child[0]->nodetype == Parser::TERMITYPE && tree->child[1]->nodetype == Parser::BTYPE
                     && tree->child[2]->nodetype == Parser::TERMITYPE){
                return doBoolStatement(tree->child[1]);
            }else if(tree->child[1] != nullptr &&
                     tree->child[0]->nodetype == Parser::BOOLSIMBOOLTYPE && tree->child[1]->nodetype == Parser::BTYPE){
                return !doBoolStatement(tree->child[1]);
            }else if(tree->child[1] != nullptr &&
                     tree->child[0]->nodetype == Parser::ATYPE && tree->child[1]->nodetype == Parser::BTYPE){
                return doBoolStatement(tree->child[0]) && doBoolStatement(tree->child[1]);
            }else if(tree->child[1] != nullptr &&
                     tree->child[0]->nodetype == Parser::OTYPE && tree->child[1]->nodetype == Parser::BTYPE){
                return doBoolStatement(tree->child[0]) || doBoolStatement(tree->child[1]);
            }
        }else if(tree->nodetype == Parser::ATYPE){
            if(tree->child[0]->nodetype == Parser::BTYPE && tree->child[1]->nodetype == Parser::BOOLSIMBOOLTYPE){
                return doBoolStatement(tree->child[0]);
            }
        }else if(tree->nodetype == Parser::OTYPE){
            if(tree->child[0]->nodetype == Parser::BTYPE && tree->child[1]->nodetype == Parser::BOOLSIMBOOLTYPE){
                return doBoolStatement(tree->child[0]);
            }
        }else{
            cout<<"***Error when doBoolStatement!"<<endl;
            return false;
        }
    }
}

void Analyzer::doAssignStatements(Parser::TreeNode *tree){
    if(tree->child[0]->nodetype != Parser::IDTYPE){
        cout<<"***Error when doAssignStatement, first child should be id."<<endl;
        return;
    }
    if(tree->child[1] != nullptr && tree->child[1]->token.name != "="){
        cout<<"***Error when doAssignStatement, second child should be ="<<endl;
        return;
    }
    if(tree->child[2] != nullptr && tree->child[2]->nodetype != Parser::STATEMENTTYPE){
        cout<<"***Error when doAssignStatement, third child shoube be statement"<<endl;
        return;
    }
    map<string, STable::TableInfo>::iterator it = stable.tableStack.top().find(tree->child[0]->token.name);
    cout<<stable.tableStack.size()<<stable.tableStack.top().size()<<tree->child[0]->token.name<<endl;
    if(it != stable.tableStack.top().end()){
        it->second.val = doCalculateStatement(tree->child[2]);
        // cout<<"ans"<<doCalculateStatement(tree->child[2])<<endl;

    }else{
        STable::TableInfo tmp;
        tmp.val = doCalculateStatement(tree->child[2]);
        // cout<<"x"<<tmp.val<<endl;
        stable.tableStack.top().insert(pair<string, STable::TableInfo>(tree->child[0]->token.name, tmp));
        cout<<stable.tableStack.top().find(tree->child[0]->token.name)->first<<endl;
        //cout<<top[tree->child[0]->token.name].val<<endl;
    }

    cout<<tree->child[0]->token.name<<" "<<stable.tableStack.top()[tree->child[0]->token.name].val<<endl;;
    Output tmpOutput;
    tmpOutput.name = tree->child[0]->token.name;
    tmpOutput.val = stable.tableStack.top()[tree->child[0]->token.name].val;
    output.push_back(tmpOutput);
}

int Analyzer::doCalculateStatement(Parser::TreeNode *tree){
    if(tree != nullptr){
        if(tree->nodetype == Parser::ETYPE || tree->nodetype == Parser::STATEMENTTYPE){
            if(tree->child[1] != nullptr && tree->child[1]->token.name == "+"){
                return doCalculateStatement(tree->child[0]) + doCalculateStatement(tree->child[2]);
            }else if(tree->child[1] != nullptr && tree->child[1]->token.name == "*"){
                return doCalculateStatement(tree->child[0]) * doCalculateStatement(tree->child[2]);
            }else if(tree->child[1] != nullptr && tree->child[1] != nullptr &&
                     tree->child[0]->nodetype == Parser::TERMITYPE &&
                     tree->child[1]->nodetype == Parser::ETYPE &&
                     tree->child[2]->nodetype == Parser::TERMITYPE){
                return doCalculateStatement(tree->child[1]);
            }else if(tree->child[0]->nodetype == Parser::IDTYPE){
                int x;
                map<string, STable::TableInfo>::iterator it = stable.tableStack.top().find(tree->child[0]->token.name);

                if(it != stable.tableStack.top().end()){
                    x = it->second.val;
                }else{
                    x = 0;
                }
                if(tree->child[0]->token.type == Tokenizer::INT)
                    x = atol(tree->child[0]->token.name.c_str());
                return x;
            }else{
                cout<<"***Error, when do calculateStatement, can't know this token"<<endl;
                return -1;
            }
        }/*else{
            cout<<
            cout<<"***Error, when do calculateStatement, can't know this Non-Term"<<endl;
            return -1;
        }*/
    }
}

void Analyzer::doMainStatement(Parser::TreeNode *tree){
    if(tree != nullptr){
        if((tree->nodetype == Parser::STYPE) || (tree->nodetype == Parser::MAIN)){
            if(tree->child[1] != nullptr && tree->child[2] != nullptr &&
               tree->child[3] != nullptr && tree->child[4] != nullptr &&
               tree->child[0]->token.name == "if" && tree->child[3]->token.name == "else"){
                map<string, STable::TableInfo> tmp2;
                stable.tableStack.push(tmp2);
                if(doBoolStatement(tree->child[1])){
                    doMainStatement(tree->child[2]);
                }else{
                    doMainStatement(tree->child[4]);
                }
            }else if(tree->child[0]->token.name == "while"){
                map<string, STable::TableInfo> tmp2;
                stable.tableStack.push(tmp2);
                while(doBoolStatement(tree->child[1])){
                    doMainStatement(tree->child[2]);
                }
            }else if(tree->child[1] != nullptr && tree->child[2] != nullptr &&
                     tree->child[0]->nodetype == Parser::TERMITYPE &&
                     tree->child[1]->nodetype == Parser::LTYPE &&
                     tree->child[2]->nodetype == Parser::TERMITYPE){

                treeOrder(tree->child[1]);
                doMainStatement(tree->child[1]);
            }else if(tree->child[1] != nullptr && tree->child[1]->token.name == ";"){
                doAssignStatements(tree->child[0]);
            }
        }else if(tree->nodetype == Parser::LTYPE){
            if(tree->child[1] == nullptr && tree->child[0]->nodetype == Parser::STYPE){
                doMainStatement(tree->child[0]);
            }else if(tree->child[1] != nullptr && tree->child[0]->nodetype == Parser::STYPE &&
                     tree->child[1]->nodetype == Parser::LTYPE){
                doMainStatement(tree->child[0]);
                doMainStatement(tree->child[1]);
            }
        }else{
            cout<<"***Error when doMainStatement, can't know this non-Term"<<endl;
            return;
        }
    }
}

void Analyzer::testDoBoolStatement(){
    // treeOrder(getTreeNode("if((5>3)&&(a<b)||!(6)){c=(3+5*2+6*(3+7)*2+3*3);}else{c=c+1;while(5<3){c=3+3;}}"));
    Parser::TreeNode* r = new Parser::TreeNode;
    r->child[0] = new Parser::TreeNode;
    r->child[1] = new Parser::TreeNode;
    r->child[2] = new Parser::TreeNode;
    r->child[1]->child[0] = new Parser::TreeNode;
    r->child[1]->child[1] = new Parser::TreeNode;
    r->child[1]->child[2] = new Parser::TreeNode;

    r->nodetype = Parser::BOOLTYPE;
    r->child[0]->nodetype = Parser::TERMITYPE;
    Tokenizer::Token sim1;
    sim1.name = "(";
    sim1.type = Tokenizer::SIMBOL;
    r->child[0]->token = sim1;
    r->child[1]->nodetype = Parser::BTYPE;
    r->child[2]->nodetype = Parser::TERMITYPE;
    Tokenizer::Token sim2;
    sim2.name = ")";
    sim2.type = Tokenizer::SIMBOL;
    r->child[2]->token = sim2;

    r->child[1]->child[0]->nodetype = Parser::IDTYPE;
    Tokenizer::Token tmp1;
    tmp1.name = "1";
    tmp1.type = Tokenizer::INT;
    r->child[1]->child[0]->token = tmp1;
    r->child[1]->child[1]->nodetype = Parser::ROPTYPE;
    Tokenizer::Token tmp2;
    tmp2.name = ">";
    tmp2.type = Tokenizer::SIMBOL;
    r->child[1]->child[1]->token = tmp2;

    r->child[1]->child[2]->nodetype = Parser::IDTYPE;
    Tokenizer::Token tmp3;
    tmp3.name = "x";
    tmp3.type = Tokenizer::ID;
    r->child[1]->child[2]->token = tmp3;
    Parser p;
    p.printSyntaxTree(r);
}

void Analyzer::testDoAssignStatement(){
    // treeOrder(getTreeNode("if((5>3)&&(a<b)||!(6)){c=(3+5*2+6*(3+7)*2+3*3);}else{c=c+1;while(5<3){c=3+3;}}"));
    Parser::TreeNode* r = new Parser::TreeNode;
    r->child[0] = new Parser::TreeNode;
    r->child[1] = new Parser::TreeNode;
    r->child[2] = new Parser::TreeNode;
    r->child[2]->child[0] = new Parser::TreeNode;
    r->child[2]->child[1] = new Parser::TreeNode;
    r->child[2]->child[2] = new Parser::TreeNode;
    r->child[2]->child[1]->child[0] = new Parser::TreeNode;
    r->child[2]->child[1]->child[1] = new Parser::TreeNode;
    r->child[2]->child[1]->child[2] = new Parser::TreeNode;
    r->child[2]->child[1]->child[0]->child[0] = new Parser::TreeNode;
    r->child[2]->child[1]->child[2]->child[0] = new Parser::TreeNode;

    r->nodetype = Parser::ASSIGN;

    Tokenizer::Token tmp0;tmp0.name = "="; tmp0.type = Tokenizer::SIMBOL;
    r->child[1]->token = tmp0;
    r->child[1]->nodetype = Parser::TERMITYPE;

    Tokenizer::Token tmp1;tmp1.name = "x"; tmp1.type = Tokenizer::ID;
    r->child[0]->token = tmp1;
    r->child[0]->nodetype = Parser::IDTYPE;

    r->child[2]->nodetype = Parser::STATEMENTTYPE;

    Tokenizer::Token tmp2;tmp2.name = "("; tmp2.type = Tokenizer::SIMBOL;
    r->child[2]->child[0]->token = tmp2;
    r->child[2]->child[0]->nodetype = Parser::TERMITYPE;

    r->child[2]->child[1]->nodetype = Parser::ETYPE;

    Tokenizer::Token tmp3;tmp3.name = ")"; tmp3.type = Tokenizer::SIMBOL;
    r->child[2]->child[2]->token = tmp3;
    r->child[2]->child[2]->nodetype = Parser::TERMITYPE;

    r->child[2]->child[1]->child[0]->nodetype = Parser::ETYPE;

    Tokenizer::Token tmp4;tmp4.name = "*"; tmp4.type = Tokenizer::SIMBOL;
    r->child[2]->child[1]->child[1]->token = tmp4;
    r->child[2]->child[1]->child[1]->nodetype = Parser::TERMITYPE;

    r->child[2]->child[1]->child[2]->nodetype = Parser::ETYPE;

    Tokenizer::Token tmp5;tmp5.name = "233333"; tmp5.type = Tokenizer::INT;
    r->child[2]->child[1]->child[0]->child[0]->token = tmp5;
    r->child[2]->child[1]->child[0]->child[0]->nodetype = Parser::IDTYPE;

    Tokenizer::Token tmp6;tmp6.name = "4000"; tmp6.type = Tokenizer::INT;
    r->child[2]->child[1]->child[2]->child[0]->token = tmp6;
    r->child[2]->child[1]->child[2]->child[0]->nodetype = Parser::IDTYPE;

    doAssignStatements(r);
}

void Analyzer::outputOutput(){
    for(auto item: output){
        cout<<"Item: "<<item.name<<" "<<item.val<<endl;
    }
}

void Analyzer::test(){
    Parser::TreeNode* r = getTreeNode("{if(((3>=3)&&(a<b))||!(6)){c=(3+5*2+6*(3+7)*2+3*3);}else{c=c+1;c=c+1;}c=c+1;}");
    doMainStatement(r);
    outputOutput();
}


