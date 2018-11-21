#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "frameitemlist.h"
#include "framelistmodel.h"
#include "canbuschannel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<FrameListModel>("CANbusExample", 1, 0, "FrameListModel");
    qmlRegisterUncreatableType<FrameItemList>("CANbusExample", 1, 0, "FrameItemList",
        QStringLiteral("FrameItemList should not be created in QML"));

    FrameItemList list;
    CANbusChannel channel(&list);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("framelist"), &list);
    engine.rootContext()->setContextProperty(QStringLiteral("channel"), &channel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
