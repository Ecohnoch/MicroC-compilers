#ifndef PARSER_H
#define PARSER_H
#include "tokenizer.h"
#include <map>
class Table{
public:
    Table(){
        initColumn1(column1);
        initColumn2(column2);
        initColumn3(column3);
        initColumn4(column4);
    }

    void initColumn1(map<string, int> &c1);
    void initColumn2(map<string, int> &c2);
    void initColumn3(map<string, int> &c3);
    void initColumn4(map<string, int> &c4);
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
    /* 9 */ {  2,  -1,  3,  4,105,  5, -1, -1, 105,  9, 14},
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
    // 100: G' -> G
    // 101: G  —> i = s
    int action3[5][5]=
    /* 0 */  {{  2, -1, -1, -1, 1},
    /* 1 */   { -1,-1, -1,100, -1},
    /* 2 */   { -1, 3, -1, -1, -1},
    /* 3 */   { -1, -1, 4, -1, -1},
    /* 4 */   { -1, -1, -1,101,-1}};
    map<string, int> column4;
};

class Parser
{
public:
    Parser();
    enum NodeType{
        NANA,
        MAIN,
        STYPE,
        LTYPE,
        BOOLTYPE,
        STATEMENTTYPE,
        BTYPE,
        ATYPE,
        OTYPE,
        ETYPE,
        TERMITYPE,
        ASSIGN,
        GTYPE,
        ROPTYPE,
        IDTYPE,
        BOOLSIMBOOLTYPE
    };
    class TreeNode{
    public:
        Tokenizer::Token token;
        TreeNode *child[5];
        TreeNode *parent;
        NodeType nodetype;
        TreeNode(){
            nodetype = NANA;
            child[0] = child[1] = child[2] = child[3] = child[4] = nullptr;
            parent = nullptr;
        }
    };
    class stackElement{
    public:
        int state;
        Tokenizer::Token token;
        stackElement(int s, Tokenizer::Token t):state(s), token(t){}
        TreeNode* ptr;
        void set(int s, Tokenizer::Token t){
            state = s;
            token = t;
        }
    };
    void test();
    void testParseBoolStatement();
    void testCalculateStatement();
    void testAssignStatment();
    void testMainStatement();

    TreeNode* parseBoolStatement(vector<Tokenizer::Token>);
    TreeNode* parseCalculateStatement(vector<Tokenizer::Token>);
    TreeNode* parseMainStatement(vector<Tokenizer::Token>);
    TreeNode* parseAssignStatement(vector<Tokenizer::Token>);
    void printSyntaxTree(TreeNode *tree);
private:
    Tokenizer tokener;
    string sourceCode;
    vector<Tokenizer::Token> tokens;
    void getSourceCode(string s);
    void getTokens();

};

#endif // PARSER_H
