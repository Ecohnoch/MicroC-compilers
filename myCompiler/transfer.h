#ifndef TRANSFER_H
#define TRANSFER_H
#include <QObject>
#include <vector>
#include "token_parser.h"
#include "grammar_parser.h"
class transfer: public QObject
{
    Q_OBJECT
public:
    transfer();

signals:
    void doReadTokens();
    void doParser();
public slots:
    void getSourcecode(QString sourcecode);
    void getParserFlow();
    QString parserToJSON();
    QString tokensToJSON();
private:
    token_parser tokenFlow;
    grammar_parser parserFlow;

};

#endif // TRANSFER_H
