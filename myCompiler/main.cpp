#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "token_parser.h"
#include "robotfile.h"

int tokens::idNum = 0;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<RobotFile>("File", 1, 0, "File", &RobotFile::qmlSingleton);
    qmlRegisterType<token_parser>("TokenParser", 1, 0, "TokenParser");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
