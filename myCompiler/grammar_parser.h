#ifndef GRAMMAR_PARSER_H
#define GRAMMAR_PARSER_H
#include "token_parser.h"
class basicElement{
public:
    basicElement(int s, string sim): state(s), simbol(sim){}
    int state;
    string simbol;
    void set(int s, string sim){state = s; simbol = sim;}
    void show(){cout<<"state: "<<state<<" simbol:"<<simbol<<endl;}
};

class Table{
public:
    Table(){
        initColumn1(column1);
        initColumn2(column2);
        initColumn3(column3);
    }

    void initColumn1(map<string, int> &c1);
    void initColumn2(map<string, int> &c2);
    void initColumn3(map<string, int> &c3);

    // 100  S' -> S
    // 101  S  -> if e S else S
    // 102  S  -> while e S
    // 103  S  -> {L}
    // 104  S  -> a;
    // 105  L  -> S
    // 106  L  -> SL

    int action[20][11]=
    /* 0 */{{   2, -1,  3,  4, -1,  5, -1, -1, -1,  1, -1},
    /* 1 */ {  -1, -1, -1, -1, -1, -1, -1, -1,100, -1, -1},
    /* 2 */ {  -1, -1, -1, -1, -1, -1, -1,  6, -1, -1, -1},
    /* 3 */ {  -1, -1, -1, -1, -1, -1, -1,  7, -1, -1, -1},
    /* 4 */ {   2, -1,  3,  4, -1,  5, -1, -1, -1,  9,  8},
    /* 5 */ {  -1, -1, -1, -1, -1, -1, 10, -1, -1, -1, -1},
    /* 6 */ {   2, -1,  3,  4, -1,  5, -1, -1, -1, 11, -1},
    /* 7 */ {   2, -1,  3,  4, -1,  5, -1, -1, -1, 12, -1},
    /* 8 */ {  -1, -1, -1, -1, 13, -1, -1, -1, -1, -1, -1},
    /* 9 */ {  2, -1, 3, 4,105, 5, -1, -1, 105,  9, 14},
    /* 10*/ {  104,104, 104, 104,104, 104, -1, -1,104, -1, -1},
    /* 11*/ {  -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 12*/ {  102,102, 102, 102, 102, 102, -1, -1,102, -1, -1},
    /* 13*/ {  103,103, 103, 103,103, 103, -1, -1,103, -1, -1},
    /* 14*/ {  106,106, 106, 106,106, 106, -1, -1, 106, -1, -1},
    /* 15*/ {   2, -1,  3,  4, -1,  5, -1, -1, -1, 16, -1},
    /* 16*/ {  101,101, 101, 101,101, 101, -1, -1,101, -1, -1}};
    map<string, int> column1;

    // 100 : S'  ->  E
    // 101 : E   ->  E + E
    // 102 : E   ->  E * E
    // 103 : E   ->  (E)
    // 104 : E   ->  i
    int action1[10][7]=
    /* 0 */  {{  3, -1, -1,  2, -1, -1,  1},
    /* 1 */   { -1,  4,  5, -1, -1,100, -1},
    /* 2 */   {  3, -1, -1,  2, -1, -1,  6},
    /* 3 */   { -1,104,104, -1,104,104, -1},
    /* 4 */   {  3, -1, -1,  2, -1, -1,  7},
    /* 5 */   {  3, -1, -1,  2, -1, -1,  8},
    /* 6 */   { -1,  4,  5, -1,  9, -1, -1},
    /* 7 */   { -1,101,  5, -1,101,101, -1},
    /* 8 */   { -1,102,102, -1,102,102, -1},
    /* 9 */   { -1,103,103, -1,103,103, -1}};
    map<string, int> column2;


    // 100: S'  ->  B
    // 101: B   ->  i
    // 102: B   ->  i rop i
    // 103: B   ->  (B)
    // 104: B   ->  !B
    // 105: A   ->  B&&
    // 106: B   ->  AB
    // 107: O   ->  B||
    // 108: B   ->  OB
    int action2[16][11]=
    /* 0 */  {{  1, -1,  4, -1,  5, -1, -1, -1, 13,  7,  8},
    /* 1 */   {  1,  2, -1,101, -1,101,101,101, -1, -1, -1},
    /* 2 */   {  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* 3 */   { -1, -1, -1,102, -1,102,102,102, -1, -1, -1},
    /* 4 */   {  1, -1,  4, -1,  5, -1, -1, -1, 11,  7,  8},
    /* 5 */   {  1, -1,  4, -1,  5, -1, -1, -1,  6,  7,  8},
    /* 6 */   { -1, -1, -1,104, -1,  9, 10,104, -1, -1, -1},
    /* 7 */   {  1, -1,  4, -1,  5, -1, -1, -1, 14,  7,  8},
    /* 8 */   {  1, -1,  4, -1,  5, -1, -1, -1, 15,  7,  8},
    /* 9 */   {105, -1,105, -1,105, -1, -1, -1, -1, -1, -1},
    /*10 */   {107, -1,107, -1,107, -1, -1, -1, -1, -1, -1},
    /*11 */   { -1, -1, -1, 12, -1,  9, 10, -1, -1, -1, -1},
    /*12 */   { -1, -1, -1,103, -1,103,103,103, -1, -1, -1},
    /*13 */   { -1, -1, -1, -1, -1,  9, 10,100, -1, -1, -1},
    /*14 */   { -1, -1, -1,106, -1,  9, 10,106, -1, -1, -1},
    /*15 */   { -1, -1, -1,108, -1,  9, 10,108, -1, -1, -1}};
    map<string, int> column3;
};

class grammar_parser{
public:
    grammar_parser();

    void test();
    vector<tokens> test1();
    vector<tokens> test2();
    vector<tokens> test3();
    vector<tokens> testControlStatement();
    void parserControlStatement(vector<tokens> testStr);
    void parserCalculateStatement(vector<tokens> testStr);
    void parserBoolStatement(vector<tokens> testStr);

    vector<tokens> getControlStatement(vector<tokens> tokenFlow);
    vector<tokens> getCalculateStatement(vector<tokens> tokenFlow);
    vector<tokens> getBoolStatement(vector<tokens> tokenFlow);
    vector<string> outputControlZhan;
    vector<string> outputControlSimbols;
    vector<int>    outputControlAction;
    vector<string> outputControlInstruction;
};

#endif // GRAMMAR_PARSER_H
