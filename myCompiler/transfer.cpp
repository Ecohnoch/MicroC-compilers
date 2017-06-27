#include "transfer.h"

transfer::transfer()
{

}

void transfer::getSourcecode(QString sourcecode){
    string ans = sourcecode.toStdString();
    tokenFlow.input = ans;
}

QString transfer::tokensToJSON(){
    string x = tokenFlow.input;
    tokenFlow.parser(x);
    string thisAns;
    thisAns += "{";
    for(int i = 0; i < tokenFlow.ans.size(); ++i){
        thisAns += "\"";
        thisAns += to_string(i) + "";
        thisAns += "\":{";
        thisAns += "\"token_name\":\"" + tokenFlow.ans.at(i).token_name + "\",";
        thisAns += "\"token_num\" :";
        thisAns += to_string(tokenFlow.ans.at(i).token_num);
        thisAns += "}";
        if(i != tokenFlow.ans.size() - 1){
            thisAns += ",";
        }
    }
    thisAns += "}";
    return QString::fromStdString(thisAns);
}

void transfer::getParserFlow(){
    parserFlow.outputControlAction.clear();
    parserFlow.outputControlInstruction.clear();
    parserFlow.outputControlSimbols.clear();
    parserFlow.outputControlZhan.clear();

    vector<tokens> getControl = parserFlow.getControlStatement(tokenFlow.ans);
    for(auto item: getControl){
        cout<<item.token_name<<endl;
    }
    parserFlow.parserControlStatement(getControl);
}

QString transfer::parserToJSON(){
    string ans = "{";
    for(int i = 0; i < parserFlow.outputControlSimbols.size(); ++i){
        ans += "\"";
        ans += to_string(i) + "\":{";
        ans += "\"stack\":";
        ans += "\"";
        ans += parserFlow.outputControlZhan.at(i);
        ans += "\",";
        ans += "\"restStr\":";
        ans += "\"";
        ans += parserFlow.outputControlSimbols.at(i);
        ans += "\",";
        ans += "\"action\":";
        ans += "\"";
        ans += to_string(parserFlow.outputControlAction.at(i));
        ans += "\",";
        ans += "\"info\":";
        ans += "\"";
        ans += parserFlow.outputControlInstruction.at(i);
        ans += "\"}";
        if(i != parserFlow.outputControlSimbols.size() - 1){
            ans += ",";
        }
    }
    ans += "}";
    cout<<ans<<endl;
    return QString::fromStdString(ans);
}
