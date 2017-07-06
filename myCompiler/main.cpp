#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "analyzer.h"
#include "transfer.h"
#include "robotfile.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    qmlRegisterSingletonType<RobotFile>("File", 1, 0, "File", &RobotFile::qmlSingleton);
    qmlRegisterType<transfer>("Transfer", 1, 0, "Transfer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
//    Analyzer a;
//    a.test();
}
