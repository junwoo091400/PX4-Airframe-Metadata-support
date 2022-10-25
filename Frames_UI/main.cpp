#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QFile>
#include <QJsonDocument>

#include "frames.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    // Frames testing code
    QString framesJsonFilePath = QString(":/frames.json");

    QFile file;
    file.setFileName(framesJsonFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString json_data = file.readAll();
    file.close();

    QJsonDocument _jsonMetadata;
    _jsonMetadata = QJsonDocument::fromJson(json_data.toUtf8());

    Frames_Root _frames;
    _frames.parseJson(_jsonMetadata);

    // Print out the info
    _frames.print_info();


    // Load the Application GUI
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQmlComponent component(&engine, url);
    QObject *object = component.create();

    QObject *rect = object->findChild<QObject*>("rect");
    if (rect) { rect->setProperty("margin", 10); }

//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
