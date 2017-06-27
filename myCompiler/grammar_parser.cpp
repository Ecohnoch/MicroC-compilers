#include "grammar_parser.h"
#include <stack>

void Table::initColumn1(map<string, int> &c1){
    c1["if"]    = 0;
    c1["else"]  = 1;
    c1["while"] = 2;
    c1["{"]     = 3;
    c1["}"]     = 4;
    c1["a"]     = 5;
    c1[";"]     = 6;
    c1["e"]     = 7;
    c1["#"]     = 8;
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
    c3["rop"] =  1;
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

grammar_parser::grammar_parser(){

}

void grammar_parser::test(){
//    parserControlStatement(test1());
//    parserCalculateStatement(test2());
//    parserBoolStatement(test3());


    vector<tokens> getControl = getControlStatement(testControlStatement());
    for(auto item : getControl){
        cout<<item.token_name<<" "<<item.token_num<<endl;
    }

    parserControlStatement(getControl);
    for(int i = 0; i < outputControlSimbols.size(); ++i){
        cout<< "ANS: "<<outputControlZhan.at(i)<<"  "<<outputControlSimbols.at(i)<<" "<<outputControlAction.at(i)<<endl;
    }
    cout<<"num: "<< outputControlZhan.size()<<" "<<outputControlSimbols.size()<<" "<<outputControlAction.size()<<" "<<outputControlInstruction.size()<<endl;
}

vector<tokens> grammar_parser::test1(){
    vector<tokens> testStr;
    testStr.push_back(tokens("if"   , 0));
    testStr.push_back(tokens("e", 1));
    testStr.push_back(tokens("{"    , 3));
    testStr.push_back(tokens("while", 2));
    testStr.push_back(tokens("e", 1));
    testStr.push_back(tokens("{"    , 3));
    testStr.push_back(tokens("a"    , 5));
    testStr.push_back(tokens(";"    , 6));
    testStr.push_back(tokens("a"    , 5));
    testStr.push_back(tokens(";"    , 6));
    testStr.push_back(tokens("}"    , 4));
    testStr.push_back(tokens("}"    , 3));
    testStr.push_back(tokens("else" , 1));
    testStr.push_back(tokens("{"    , 3));
    testStr.push_back(tokens("a"    , 5));
    testStr.push_back(tokens(";"    , 6));
    testStr.push_back(tokens("}"    , 3));
    testStr.push_back(tokens("#"    , 8));
    return testStr;
}

vector<tokens> grammar_parser::test2(){
    vector<tokens> testStr;
    testStr.push_back(tokens("("    , 21));
    testStr.push_back(tokens("const", 11));
    testStr.push_back(tokens("+"    , 14));
    testStr.push_back(tokens("const", 22));
    testStr.push_back(tokens("*"    , 15));
    testStr.push_back(tokens("const",  2));
    testStr.push_back(tokens(")"    , 22));
    testStr.push_back(tokens("#"    ,  8));
    return testStr;
}

vector<tokens> grammar_parser::test3(){
    vector<tokens> testStr;
    testStr.push_back(tokens("("     ,21));
    testStr.push_back(tokens("i"     , 1));
    testStr.push_back(tokens("rop"   ,20));
    testStr.push_back(tokens("i"     , 1));
    testStr.push_back(tokens("&&"    ,17));
    testStr.push_back(tokens("i"     , 0));
    testStr.push_back(tokens(")"     ,22));
    testStr.push_back(tokens("||"    ,18));
    testStr.push_back(tokens("i"     , 1));
    testStr.push_back(tokens("#"     , 8));
    return testStr;
}

vector<tokens> grammar_parser::testControlStatement(){
    vector<tokens> testStr;
    testStr.push_back(tokens("if"   , 0));
    testStr.push_back(tokens("("    , 21));
    testStr.push_back(tokens("id"   , 0));
    testStr.push_back(tokens("rop"  , 20));
    testStr.push_back(tokens("id"   , 1));
    testStr.push_back(tokens(")"    , 22));
    testStr.push_back(tokens("{"    , 3));
    testStr.push_back(tokens("id"   , 2));
    testStr.push_back(tokens("rop"  , 20));
    testStr.push_back(tokens("id"   , 3));
    testStr.push_back(tokens(";"    , 6));
    testStr.push_back(tokens("id"   , 3));
    testStr.push_back(tokens("rop"  , 20));
    testStr.push_back(tokens("id"   , 4));
    testStr.push_back(tokens(";"    , 6));
    testStr.push_back(tokens("}"    , 4));
    testStr.push_back(tokens("else" , 1));
    testStr.push_back(tokens("{"    , 3));
    testStr.push_back(tokens("id"   , 2));
    testStr.push_back(tokens("rop"  , 20));
    testStr.push_back(tokens("id"   , 3));
    testStr.push_back(tokens(";"    , 6));
    testStr.push_back(tokens("while", 2));
    testStr.push_back(tokens("("    , 21));
    testStr.push_back(tokens("id"   , 5));
    testStr.push_back(tokens(")"    , 22));
    testStr.push_back(tokens("{"    , 3));
    testStr.push_back(tokens("id"   , 5));
    testStr.push_back(tokens("="    , 16));
    testStr.push_back(tokens("id"   , 2));
    testStr.push_back(tokens("+"    , 14));
    testStr.push_back(tokens("id"   , 3));
    testStr.push_back(tokens(";"    , 6));
    testStr.push_back(tokens("}"    , 4));
    testStr.push_back(tokens("}"    , 4));
    return testStr;
}


void grammar_parser::parserControlStatement(vector<tokens> testStr){
    Table t;
    int start = 0;
    int avoidEndlessLoop = 0;
    vector<basicElement> zhan;
    zhan.push_back(basicElement(0, "0"));
    while(1){
        basicElement b = zhan.back();
        tokens firstElement = testStr.at(start);

        string zhanString = "";
        // zhan
        for(auto item : zhan){
            zhanString = zhanString + item.simbol;
            outputControlZhan.push_back(zhanString);
            cout<< item.state<<" "<<item.simbol<<" ";
        }
        cout<<endl;
        string restString = "";
        for(int i = start; i < testStr.size(); ++i){
            restString = restString + testStr.at(i).token_name;
            cout<< testStr.at(i).token_name<<" ";
        }
        if(restString.size())
            outputControlSimbols.push_back(restString);
        else
            outputControlSimbols.push_back(" ");
        cout<<endl;
        int thisState = t.action[b.state][t.column1[firstElement.token_name]];        // shift-in
        outputControlAction.push_back(thisState);

        if(thisState >= 0 && thisState < 100){
            basicElement tmp(thisState, firstElement.token_name);
            zhan.push_back(tmp);
            start ++;
            outputControlInstruction.push_back("Shift-In!");
            cout<<"Shift-In !"<<endl;
        // reduce
        }else if(thisState > 100){
            basicElement tmp(0, "0");
            switch (thisState) {
            case 101:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action[zhan.back().state][t.column1["S"]], "S");
                outputControlInstruction.push_back("Reduce: S -> if e S else S");
                zhan.push_back(tmp);
                break;
            case 102:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action[zhan.back().state][t.column1["S"]], "S");
                outputControlInstruction.push_back("Reduce: S -> while e S");
                zhan.push_back(tmp);
                break;
            case 103:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action[zhan.back().state][t.column1["S"]], "S");
                outputControlInstruction.push_back("Reduce: S -> {L}");
                zhan.push_back(tmp);
                break;
            case 104:
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action[zhan.back().state][t.column1["S"]], "S");
                outputControlInstruction.push_back("Reduce: S -> a");
                zhan.push_back(tmp);
                break;
            case 105:
                zhan.pop_back();
                tmp.set(t.action[zhan.back().state][t.column1["L"]], "L");
                outputControlInstruction.push_back("Reduce: L -> S");
                zhan.push_back(tmp);
                break;
            case 106:
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action[zhan.back().state][t.column1["L"]], "L");
                outputControlInstruction.push_back("Reduce: L -> SL");
                zhan.push_back(tmp);
                break;
            default:
                cout<<"*** Error, when parse action1. thisState: "<<thisState<<endl;
                break;
            }
        }else if(thisState == 100){
            outputControlInstruction.push_back("SUC!");
            cout<<"SUC"<<endl;
            break;
        }else{
            cout<<"*** Error, when parse action1. thisState: "<<thisState<<endl;
            start ++;
            break;
        }

       avoidEndlessLoop ++;
       if(avoidEndlessLoop >= 550)
           break;
    }
}

void grammar_parser::parserCalculateStatement(vector<tokens> testStr){
    Table t;
    int start = 0;
    int avoidEndlessLoop = 0;
    vector<basicElement> zhan;
    zhan.push_back(basicElement(0, "0"));
    while(1){
        basicElement b = zhan.back();
        tokens firstElement = testStr.at(start);

        // zhan
        for(auto item : zhan){
            cout<< item.state<<" "<<item.simbol<<" ";
        }
        cout<<endl;
        for(int i = start; i < testStr.size(); ++i){
            cout<< testStr.at(i).token_name<<" ";
        }
        cout<<endl;
        int thisState = t.action1[b.state][t.column2[firstElement.token_name]];        // shift-in
        if(thisState >= 0 && thisState < 100){
            basicElement tmp(thisState, firstElement.token_name);
            zhan.push_back(tmp);
            start ++;
            cout<<"Shift-In !"<<endl;
        // reduce
        }else if(thisState > 100){
            basicElement tmp(0, "0");
            switch (thisState) {
            case 101:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action1[zhan.back().state][t.column2["E"]], "E");
                zhan.push_back(tmp);
                break;
            case 102:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action1[zhan.back().state][t.column2["E"]], "E");
                zhan.push_back(tmp);
                break;
            case 103:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action1[zhan.back().state][t.column2["E"]], "E");
                zhan.push_back(tmp);
                break;
            case 104:
                zhan.pop_back();
                tmp.set(t.action1[zhan.back().state][t.column2["E"]], "E");
                zhan.push_back(tmp);
                break;
            default:
                cout<<"*** Error, when parse action2. thisState: "<<thisState<<endl;
                break;
            }
        }else if(thisState == 100){
            cout<<"SUC"<<endl;
            break;
        }else{
            cout<<"*** Error, when parse action2. thisState: "<<thisState<<endl;
            start ++;
            break;
        }

       avoidEndlessLoop ++;
       if(avoidEndlessLoop >= 550)
           break;
    }
}

void grammar_parser::parserBoolStatement(vector<tokens> testStr){
    Table t;
    int start = 0;
    int avoidEndlessLoop = 0;
    vector<basicElement> zhan;
    zhan.push_back(basicElement(0, "0"));
    while(1){
        basicElement b = zhan.back();
        tokens firstElement = testStr.at(start);

        // zhan
        for(auto item : zhan){
            cout<< item.state<<" "<<item.simbol<<" ";
        }
        cout<<endl;
        for(int i = start; i < testStr.size(); ++i){
            cout<< testStr.at(i).token_name<<" ";
        }
        cout<<endl;
        int thisState = t.action2[b.state][t.column3[firstElement.token_name]];        // shift-in
        if(thisState >= 0 && thisState < 100){
            basicElement tmp(thisState, firstElement.token_name);
            zhan.push_back(tmp);
            start ++;
            cout<<"Shift-In !"<<endl;
        // reduce
        }else if(thisState > 100){
            basicElement tmp(0, "0");
            switch (thisState) {
            case 101:
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["B"]], "B");
                zhan.push_back(tmp);
                break;
            case 102:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["B"]], "B");
                zhan.push_back(tmp);
                break;
            case 103:
                zhan.pop_back();
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["B"]], "B");
                zhan.push_back(tmp);
                break;
            case 104:
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["B"]], "B");
                zhan.push_back(tmp);
                break;
            case 105:
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["A"]], "A");
                zhan.push_back(tmp);
                break;
            case 106:
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["B"]], "B");
                zhan.push_back(tmp);
                break;
            case 107:
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["O"]], "O");
                zhan.push_back(tmp);
                break;
            case 108:
                zhan.pop_back();
                zhan.pop_back();
                tmp.set(t.action2[zhan.back().state][t.column3["B"]], "B");
                zhan.push_back(tmp);
                break;
            default:
                cout<<"*** Error, when parse action2. thisState: "<<thisState<<endl;
                break;
            }
        }else if(thisState == 100){
            cout<<"SUC"<<endl;
            break;
        }else{
            cout<<"*** Error, when parse action2. thisState: "<<thisState<<endl;
            start ++;
            break;
        }

       avoidEndlessLoop ++;
       if(avoidEndlessLoop >= 550)
           break;
    }
}

vector<tokens> grammar_parser::getControlStatement(vector<tokens> tokenFlow){
    int start = 0;
    vector<tokens> ans;
    vector<vector<tokens>> es;
    vector<tokens> eachA;
    vector<tokens> eachE;
    while(start < tokenFlow.size()){
        if(tokenFlow.at(start).token_name == "if"){
            ans.push_back(tokens((tokenFlow.at(start).token_name), 0));
            eachE.clear();
            while(tokenFlow.at(start).token_name != "{" && start < tokenFlow.size()){
                eachE.push_back(tokenFlow.at(start));
                start ++;
            }
            start --;
            // the num of e will be 1 or 0, it depends on the eachE!!!
            // just as 1 to replace temporarily!!!
            ans.push_back(tokens("e", 1));
            es.push_back(eachE);
        }else if(tokenFlow.at(start).token_name == "{"){
            ans.push_back(tokens((tokenFlow.at(start).token_name), 3));
        }else if(tokenFlow.at(start).token_name == "}"){
            ans.push_back(tokens((tokenFlow.at(start).token_name), 4));
        }else if(tokenFlow.at(start).token_name == "else"){
            ans.push_back(tokens((tokenFlow.at(start).token_name), 1));
        }else if(tokenFlow.at(start).token_name == "while"){
            ans.push_back(tokens((tokenFlow.at(start).token_name), 2));
            eachE.clear();
            while(tokenFlow.at(start).token_name != "{" && start < tokenFlow.size()){
                eachE.push_back(tokenFlow.at(start));
                start ++;
            }
            start --;
            // the num of e will be 1 or 0, it depends on the eachE!!!
            // just as 1 to replace temporarily!!!
            ans.push_back(tokens("e", 1));
            es.push_back(eachE);
        }else{
            eachA.clear();
            while(tokenFlow.at(start).token_name != ";" && start < tokenFlow.size()){
                eachA.push_back(tokens(tokenFlow.at(start)));
                start ++;
            }
            ans.push_back(tokens("a", 5));
            ans.push_back(tokens(";", 6));
        }
        start ++;
    }
    ans.push_back(tokens("#", 8));
    return ans;
}
