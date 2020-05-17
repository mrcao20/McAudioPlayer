#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#else
#endif

#include <McBoot/McIocBoot.h>

int main(int argc, char *argv[])
{
    return McIocBoot::run(argc, argv, QUrl(QStringLiteral("qrc:/main.qml")));
}
