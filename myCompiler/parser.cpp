#include "parser.h"
void Table::initColumn1(map<string, int> &c1){
    c1["if"]    = 0;
    c1["else"]  = 1;
    c1["while"] = 2;
    c1["{"]     = 3;
    c1["}"]     = 4;
    c1["a"]     = 5;
    c1[";"]     = 6;
    c1["e"]     = 7;
    c1["EOF"]     = 8;
    c1["S"]     = 9;
    c1["L"]     = 10;
}

void Table::initColumn2(map<string, int> &c2){
    c2["I"]  = 0;
    c2["+"]  = 1;
    c2["*"]  = 2;
    c2["("]  = 3;
    c2[")"]  = 4;
    c2["#"]  = 5;
    c2["E"]  = 6;
}

void Table::initColumn3(map<string, int> &c3){
    c3["i"]   =  0;
    c3[">"]   =  1;
    c3[">="]  =  1;
    c3["<"]   =  1;
    c3["<="]  =  1;
    c3["=="]  =  1;
    c3["("]   =  2;
    c3[")"]   =  3;
    c3["!"]   =  4;
    c3["&&"]  =  5;
    c3["||"]  =  6;
    c3["#"]   =  7;
    c3["B"]   =  8;
    c3["A"]   =  9;
    c3["O"]   = 10;
}

void Table::initColumn4(map<string, int> &c4){
    c4["i"] = 0;
    c4["="] = 1;
    c4["a"] = 2;
    c4["#"] = 3;
    c4["G"] = 4;
}

Parser::Parser(){}

void Parser::getSourceCode(string s){
    sourceCode = s;
}

void Parser::getTokens(){
    tokener.getSourceCode(sourceCode);
    tokens = tokener.getAllTokens();
}

Parser::TreeNode* Parser::parseBoolStatement(vector<Tokenizer::Token> tokens){
    Table t;
    TreeNode *root = new TreeNode;
    root->nodetype = BOOLTYPE;
    vector<stackElement> stack;
    int start = 0;
    Tokenizer::Token firstToken;
    firstToken.name = "0";
    firstToken.type = Tokenizer::NONE;
    stack.push_back(stackElement(0, firstToken));
    int avoidEndlessLoop = 0;
    while(1){
        stackElement s = stack.back();
        Tokenizer::Token thisToken = tokens.at(start);
        int thisState;
        if(thisToken.type == Tokenizer::INT || thisToken.type == Tokenizer::ID){
            thisState = t.action2[s.state][t.column3["i"]];
        }else{
            thisState = t.action2[s.state][t.column3[thisToken.name]];
        }
        if(thisState > 0 && thisState < 100){
            // shift in
           stack.push_back(stackElement(thisState, thisToken));
           start = start + 1;
        }else if(thisState == 101){
            stackElement tmpPop = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["B"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "B";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = BTYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = IDTYPE;
            tmpPush.ptr->child[0]->token = tmpPop.token;
            stack.push_back(tmpPush);
        }else if(thisState == 102){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["B"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "B";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = BTYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = new TreeNode;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2] = new TreeNode;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            tmpPush.ptr->nodetype = BTYPE;
            tmpPush.ptr->child[0]->nodetype = IDTYPE;
            tmpPush.ptr->child[0]->token = tmpPop3.token;
            tmpPush.ptr->child[1]->nodetype = ROPTYPE;
            tmpPush.ptr->child[1]->token = tmpPop2.token;
            tmpPush.ptr->child[2]->nodetype = IDTYPE;
            tmpPush.ptr->child[2]->token = tmpPop1.token;
            stack.push_back(tmpPush);
        }else if(thisState == 103){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["B"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "B";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = tmpPop2.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2] = new TreeNode;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            tmpPush.ptr->nodetype = BTYPE;
            tmpPush.ptr->child[0]->nodetype = TERMITYPE;
            tmpPush.ptr->child[0]->token = tmpPop3.token;
            tmpPush.ptr->child[2]->nodetype = TERMITYPE;
            tmpPush.ptr->child[2]->token = tmpPop1.token;
            stack.push_back(tmpPush);
        }else if(thisState == 104){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["B"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "B";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = tmpPop1.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->nodetype = BTYPE;
            tmpPush.ptr->child[0]->nodetype = BOOLSIMBOOLTYPE;
            tmpPush.ptr->child[0]->token = tmpPop2.token;
            stack.push_back(tmpPush);
        }else if(thisState == 105){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["A"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "A";
            tmpToken.type = Tokenizer::NONE;

            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = ATYPE;
            tmpPush.ptr->child[0] = tmpPop2.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = new TreeNode;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1]->nodetype = BOOLSIMBOOLTYPE;
            tmpPush.ptr->child[1]->token = tmpPop1.token;
            stack.push_back(tmpPush);
        }else if(thisState == 106){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["B"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "B";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = BTYPE;
            tmpPush.ptr->child[0] = tmpPop2.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = tmpPop1.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 107){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["O"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "O";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = OTYPE;
            tmpPush.ptr->child[0] = tmpPop2.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = BTYPE;
            tmpPush.ptr->child[1] = new TreeNode;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1]->nodetype = BOOLSIMBOOLTYPE;
            tmpPush.ptr->child[1]->token = tmpPop1.token;
            stack.push_back(tmpPush);
        }else if(thisState == 108){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            int gotoState = t.action2[stack.back().state][t.column3["B"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "B";
            tmpToken.type = Tokenizer::NONE;

            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = BTYPE;
            tmpPush.ptr->child[0] = tmpPop2.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = tmpPop1.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 100){
            stackElement tmpPop = stack.back();
            root = tmpPop.ptr;
            root->nodetype = BOOLTYPE;
            break;
        }else{
            cout<<"***Error, boolStatement"<<endl;
            break;
        }

        avoidEndlessLoop ++;
        if(avoidEndlessLoop >= 100){
            cout<<"***EndlessLoop appears!"<<endl;
            break;
        }
    }

    return root;
}

Parser::TreeNode* Parser::parseCalculateStatement(vector<Tokenizer::Token> tokens){
    Table t;
    TreeNode *root = new TreeNode;
    root->nodetype = STATEMENTTYPE;
    vector<stackElement> stack;
    int start = 0;
    Tokenizer::Token firstToken;
    firstToken.name = "0";
    firstToken.type = Tokenizer::NONE;
    stack.push_back(stackElement(0, firstToken));
    int avoidEndlessLoop = 0;
    while(1){
        stackElement s = stack.back();
        Tokenizer::Token thisToken = tokens.at(start);
        int thisState;
        if(thisToken.type == Tokenizer::INT || thisToken.type == Tokenizer::ID){
            thisState = t.action1[s.state][t.column2["i"]];
        }else{
            thisState = t.action1[s.state][t.column2[thisToken.name]];
        }
        if(thisState > 0 && thisState < 100){
            // shift in
           stack.push_back(stackElement(thisState, thisToken));
           start = start + 1;
        }else if(thisState == 101){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action1[stack.back().state][t.column2["E"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "E";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = ETYPE;
            tmpPush.ptr->child[0] = tmpPop3.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = new TreeNode;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1]->nodetype = TERMITYPE;
            tmpPush.ptr->child[1]->token = tmpPop2.token;
            tmpPush.ptr->child[2] = tmpPop1.ptr;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 102){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action1[stack.back().state][t.column2["E"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "E";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = ETYPE;
            tmpPush.ptr->child[0] = tmpPop3.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = new TreeNode;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1]->nodetype = TERMITYPE;
            tmpPush.ptr->child[1]->token = tmpPop2.token;
            tmpPush.ptr->child[2] = tmpPop1.ptr;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 103){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action1[stack.back().state][t.column2["E"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "E";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = ETYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = TERMITYPE;
            tmpPush.ptr->child[0]->token = tmpPop3.token;
            tmpPush.ptr->child[1] = tmpPop2.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2] = new TreeNode;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2]->nodetype = TERMITYPE;
            tmpPush.ptr->child[2]->token = tmpPop1.token;
            stack.push_back(tmpPush);
        }else if(thisState == 104){
            stackElement tmpPop = stack.back();
            stack.pop_back();
            int gotoState = t.action1[stack.back().state][t.column2["E"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "E";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = ETYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = Parser::IDTYPE;
            tmpPush.ptr->child[0]->token = tmpPop.token;
            stack.push_back(tmpPush);
        }else if(thisState == 100){
            stackElement tmpPop = stack.back();
            root = tmpPop.ptr;
            root->nodetype = STATEMENTTYPE;
            break;
        }else{
            cout<<"***Error, calculateStatement"<<endl;
            break;
        }

        avoidEndlessLoop ++;
        if(avoidEndlessLoop >= 100){
            cout<<"***EndlessLoop appears!"<<endl;
            break;
        }
    }

    return root;
}

Parser::TreeNode* Parser::parseMainStatement(vector<Tokenizer::Token> tokens){
    Table t;
    TreeNode *root = new TreeNode;
    vector<stackElement> stack;
    int start = 0;
    Tokenizer::Token firstToken;
    firstToken.name = "0";
    firstToken.type = Tokenizer::NONE;
    stack.push_back(stackElement(0, firstToken));
    int avoidEndlessLoop = 0;
    while(1){
        stackElement s = stack.back();
        Tokenizer::Token thisToken = tokens.at(start);

        int thisState;
        //-------------------GET E!!----------------------------------------//
        //-------------------GET S!!----------------------------------------//
        if((thisToken.name == "if" && t.action[s.state][t.column1["if"]] < 100) ||
        (thisToken.name == "while" && t.action[s.state][t.column1["while"]] < 100)){
            if(thisToken.name == "if"){
                Tokenizer::Token simbolToken;
                simbolToken.name = "if";
                simbolToken.type = Tokenizer::SIMBOL;
                stack.push_back(stackElement(t.action[s.state][t.column1["if"]], simbolToken));
            }else if(thisToken.name == "while"){
                Tokenizer::Token simbolToken;
                simbolToken.name = "while";
                simbolToken.type = Tokenizer::SIMBOL;
                stack.push_back(stackElement(t.action[s.state][t.column1["while"]], simbolToken));
            }
            vector<Tokenizer::Token> boolStatement;
            while(thisToken.name != "{"){
                start = start + 1;
                thisToken = tokens.at(start);
                boolStatement.push_back(thisToken);
            }
            boolStatement.pop_back();
            Tokenizer::Token endToken;
            endToken.name = "#";
            endToken.type = Tokenizer::SIMBOL;
            boolStatement.push_back(endToken);
            Tokenizer::Token pushToken;
            pushToken.name = "e";
            pushToken.type = Tokenizer::BOOL;
            stackElement tmpPush(t.action[stack.back().state][t.column1["e"]], pushToken);
            tmpPush.ptr = parseBoolStatement(boolStatement);
            stack.push_back(tmpPush);
            continue;
        }else if(thisToken.name != "{" && thisToken.name != "}" &&
                 thisToken.name != ";" && thisToken.name != "else" &&
                 thisToken.name != "EOF" && t.action[s.state][t.column1[thisToken.name]] < 100){
            vector<Tokenizer::Token> calculateStatement;
            while(thisToken.name != ";"){
                calculateStatement.push_back(thisToken);
                start = start + 1;
                thisToken = tokens.at(start);
            }
            Tokenizer::Token endToken;
            endToken.name = "#";
            endToken.type = Tokenizer::SIMBOL;
            calculateStatement.push_back(endToken);
            Tokenizer::Token pushToken;
            pushToken.name = "a";
            pushToken.type = Tokenizer::INT;
            stackElement tmpPush(t.action[s.state][t.column1["a"]], pushToken);
            tmpPush.ptr = parseAssignStatement(calculateStatement);
            stack.push_back(tmpPush);
            continue;
        }
        thisState = t.action[s.state][t.column1[thisToken.name]];
        if(thisState > 0 && thisState < 100){
           stack.push_back(stackElement(thisState, thisToken));
           start = start + 1;
        }else if(thisState == 101){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            stackElement tmpPop4 = stack.back();
            stack.pop_back();
            stackElement tmpPop5 = stack.back();
            stack.pop_back();
            int gotoState = t.action[stack.back().state][t.column1["S"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "S";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = STYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = TERMITYPE;
            tmpPush.ptr->child[0]->token = tmpPop5.token;
            tmpPush.ptr->child[1] = tmpPop4.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2] = tmpPop3.ptr;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            tmpPush.ptr->child[3] = new TreeNode;
            tmpPush.ptr->child[3]->parent = tmpPush.ptr;
            tmpPush.ptr->child[3]->nodetype = TERMITYPE;
            tmpPush.ptr->child[3]->token = tmpPop2.token;
            tmpPush.ptr->child[4] = tmpPop1.ptr;
            tmpPush.ptr->child[4]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 102){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action[stack.back().state][t.column1["S"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "S";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = STYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = TERMITYPE;
            tmpPush.ptr->child[0]->token = tmpPop3.token;
            tmpPush.ptr->child[1] = tmpPop2.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2] = tmpPop1.ptr;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 103){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action[stack.back().state][t.column1["S"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "S";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = STYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = TERMITYPE;
            tmpPush.ptr->child[0]->token  = tmpPop3.token;
            tmpPush.ptr->child[1] = tmpPop2.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2] = new TreeNode;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            tmpPush.ptr->child[2]->nodetype = TERMITYPE;
            tmpPush.ptr->child[2]->token = tmpPop1.token;
            stack.push_back(tmpPush);
        }else if(thisState == 104){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            int gotoState = t.action[stack.back().state][t.column1["S"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "S";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = STYPE;
            tmpPush.ptr->child[0] = tmpPop2.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = new TreeNode;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1]->nodetype = TERMITYPE;
            tmpPush.ptr->child[1]->token = tmpPop1.token;
            stack.push_back(tmpPush);
        }else if(thisState == 105){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            int gotoState = t.action[stack.back().state][t.column1["L"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "L";
            tmpToken.type = Tokenizer::NONE;

            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = LTYPE;
            tmpPush.ptr->child[0] = tmpPop1.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 106){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            int gotoState = t.action[stack.back().state][t.column1["L"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "L";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = LTYPE;
            tmpPush.ptr->child[0] = tmpPop2.ptr;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1] = tmpPop1.ptr;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 100){
            stackElement tmpPop = stack.back();
            root = tmpPop.ptr;
            root->nodetype = MAIN;
            break;
        }else{
            cout<<"***Error, mainStatement"<<endl;
            break;
        }

        avoidEndlessLoop ++;
        if(avoidEndlessLoop >= 100){
            cout<<"***EndlessLoop appears!"<<endl;
            break;
        }
    }

    return root;
}

Parser::TreeNode* Parser::parseAssignStatement(vector<Tokenizer::Token> tokens){
    Table t;
    TreeNode *root = new TreeNode;
    root->nodetype = ASSIGN;
    vector<stackElement> stack;
    int start = 0;
    Tokenizer::Token firstToken;
    firstToken.name = "0";
    firstToken.type = Tokenizer::NONE;
    stack.push_back(stackElement(0, firstToken));
    int avoidEndlessLoop = 0;
    while(1){
        stackElement s = stack.back();
        Tokenizer::Token thisToken = tokens.at(start);
        int thisState;
        if(thisToken.type == Tokenizer::ID || thisToken.type == Tokenizer::INT){
            thisState = t.action3[s.state][t.column4["i"]];
        }else if(thisToken.name == "="){
            Tokenizer::Token simbolToken;
            simbolToken.name = "=";
            simbolToken.type = Tokenizer::SIMBOL;
            stack.push_back(stackElement(t.action3[s.state][t.column4["="]], simbolToken));
            vector<Tokenizer::Token> calculateStatement;
            while(thisToken.name != "#"){
                start = start + 1;
                thisToken = tokens.at(start);
                calculateStatement.push_back(thisToken);
            }
            // calculateStatement.pop_back();
            Tokenizer::Token pushToken ;
            pushToken.name = "a";
            pushToken.type = Tokenizer::INT;

            stackElement tmpPush(t.action3[stack.back().state][t.column4["a"]], pushToken);
            tmpPush.ptr = parseCalculateStatement(calculateStatement);
            stack.push_back(tmpPush);
            continue;
        }else{
            thisState = t.action3[s.state][t.column4[thisToken.name]];
        }
        if(thisState > 0 && thisState < 100){
            // shift in
           stack.push_back(stackElement(thisState, thisToken));
           start = start + 1;
        }else if(thisState == 101){
            stackElement tmpPop1 = stack.back();
            stack.pop_back();
            stackElement tmpPop2 = stack.back();
            stack.pop_back();
            stackElement tmpPop3 = stack.back();
            stack.pop_back();
            int gotoState = t.action3[stack.back().state][t.column4["G"]];
            Tokenizer::Token tmpToken;
            tmpToken.name = "G";
            tmpToken.type = Tokenizer::NONE;
            stackElement tmpPush(gotoState, tmpToken);
            tmpPush.ptr = new TreeNode;
            tmpPush.ptr->nodetype = GTYPE;
            tmpPush.ptr->child[0] = new TreeNode;
            tmpPush.ptr->child[0]->parent = tmpPush.ptr;
            tmpPush.ptr->child[0]->nodetype = Parser::IDTYPE;
            tmpPush.ptr->child[0]->token = tmpPop3.token;
            tmpPush.ptr->child[1] = new TreeNode;
            tmpPush.ptr->child[1]->parent = tmpPush.ptr;
            tmpPush.ptr->child[1]->nodetype = TERMITYPE;
            tmpPush.ptr->child[1]->token = tmpPop2.token;
            tmpPush.ptr->child[2] = tmpPop1.ptr;
            tmpPush.ptr->child[2]->parent = tmpPush.ptr;
            stack.push_back(tmpPush);
        }else if(thisState == 100){
            stackElement tmpPop = stack.back();
            root = tmpPop.ptr;
            root->nodetype = ASSIGN;
            break;
        }else{
            cout<<"***Error, assignStatement"<<endl;
            break;
        }

        avoidEndlessLoop ++;
        if(avoidEndlessLoop >= 100){
            cout<<"***EndlessLoop appears!"<<endl;
            break;
        }
    }

    return root;
}

void Parser::testParseBoolStatement(){
    Tokenizer tmpTokenizer;
    tmpTokenizer.getSourceCode("(5>3)&&(a<b)||!(6)#");
    TreeNode* r = parseBoolStatement(tmpTokenizer.getAllTokens());
    cout<<r->nodetype<<endl;
    cout<<r->child[1]->child[0]->child[0]->child[0]->token.name<<endl;
//            Abstract Syntax Tree -BOOL
//                --------B-------
//           -----A--           ----B---
//        ---B---   &&         --O---    ---B---
//        ( -B-  )           --B--  ||   !   --B--
//          5>3              (-B- )         ( B )
//                            a>b             6
}

void Parser::testCalculateStatement(){
    Tokenizer tmpTokenizer;
    tmpTokenizer.getSourceCode("(3+5*2+6*(3+7)*2+3*3)#");
    TreeNode* r = parseCalculateStatement(tmpTokenizer.getAllTokens());
    cout<<r->nodetype<<" "<<ETYPE<<" "<<STATEMENTTYPE<<endl;
    cout<<r->child[1]->nodetype<<" "<<ETYPE<<endl;
    cout<<r->child[0]->nodetype<<" "<<TERMITYPE<<endl;
    cout<<r->child[1]->child[0]->nodetype<<" "<<ETYPE<<endl;
    cout<<r->child[1]->child[0]->child[0]->token.name<<endl;
    cout<<r->child[1]->child[2]->nodetype<<" "<<ETYPE<<endl;
    cout<<r->child[1]->child[2]->child[0]->nodetype<<" "<<ETYPE<<endl;
    cout<<r->child[1]->child[0]->child[0]->child[0]->child[0]->token.name<<" "<<ETYPE<<endl;
    cout<<r->child[1]->child[2]->child[0]->child[0]->token.name<<endl;
}

void Parser::testAssignStatment(){
    Tokenizer tmpTokenizer;
    tmpTokenizer.getSourceCode("p = (3+5*2+6*(3+7)*2+3*3)#");
    TreeNode* r = parseAssignStatement(tmpTokenizer.getAllTokens());
}

void Parser::testMainStatement(){
    Tokenizer tmpTokenizer;
    tmpTokenizer.getSourceCode("if((5>3)&&(a<b)||!(6)){p=(3+5*2+6*(3+7)*2+3*3);}else{c=c+1;while(5<3){t=3+3;}}");
    TreeNode* r = parseMainStatement(tmpTokenizer.getAllTokens());
    cout<<r->child[1]->nodetype<<" "<<BOOLTYPE<<endl;
    cout<<r->child[2]->nodetype<<" "<<STYPE<<endl;
}

void Parser::test(){
    Tokenizer tmpTokenizer;
    tmpTokenizer.getSourceCode("if((5>3)&&(a<b)||!(6)){c=(3+5*2+6*(3+7)*2+3*3);}else{c=c+1;while(5<3){c=3+3;}}");
    TreeNode* r = parseMainStatement(tmpTokenizer.getAllTokens());
    printSyntaxTree(r);
}

void Parser::printSyntaxTree(TreeNode *tree){
    static int indentno = 0;
    indentno += 2;
    if (tree != nullptr){
        for (int i = 0; i < indentno; i++)
            cout << " ";
        switch (tree->nodetype){
        case STYPE:
            cout << "S" << endl;
            break;
        case MAIN:
            cout<< "MAIN"<<endl;
        case LTYPE:
            cout << "L" << endl;
            break;
        case BOOLTYPE:
            cout << "BOOL" << endl;
            break;
        case STATEMENTTYPE:
            cout << "STATEMENT" << endl;
            break;
        case BTYPE:
            cout << "B" << endl;
            break;
        case ATYPE:
            cout << "A" << endl;
            break;
        case OTYPE:
            cout << "O" << endl;
            break;
        case ETYPE:
            cout << "E" << endl;
            break;
        case TERMITYPE:
            cout << "TERMITYPE " << tree->token.name << endl;
            break;
        }
        printSyntaxTree(tree->child[0]);
        printSyntaxTree(tree->child[1]);
        printSyntaxTree(tree->child[2]);
        printSyntaxTree(tree->child[3]);
        printSyntaxTree(tree->child[4]);
    }
    indentno -= 2;

}

