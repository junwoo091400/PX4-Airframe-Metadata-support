#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QFile>
#include <QJsonDocument>

#include "frames.h"
#include "framecomponent.h"

void parseJson(FrameComponent *frames)
{
    // Frames testing code
    QString framesJsonFilePath = QString(":/frames.json");

    QFile file;
    file.setFileName(framesJsonFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString json_data = file.readAll();
    file.close();

    QJsonDocument _jsonMetadata;
    _jsonMetadata = QJsonDocument::fromJson(json_data.toUtf8());

    frames->parseJson(_jsonMetadata);
}


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    // Load the Application GUI
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQmlComponent component(&engine, url);
    QObject *object = component.create();

    // Find the FrameComponent object from the QML engine
    FrameComponent *frames = object->findChild<FrameComponent*>("frameComponent");

    if (frames != nullptr) {
        parseJson(frames);
        frames->print_info();
    }

//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
