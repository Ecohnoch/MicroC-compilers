#include <iostream>
#include "token_parser.h"
using namespace std;
int tokens::idNum = 0;
int main(){
    token_parser tokens;
    tokens.input = tokens.getInput();
    tokens.parser(tokens.input);
    return 0;
}
