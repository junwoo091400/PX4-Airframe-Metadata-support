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
    // Register QmlTypes
    qmlRegisterSingletonType<FrameComponent>("Junwoo.framecomp", 1, 0, "FrameComponent", FrameComponent::framecomponent_singletontype_provider);

    // Load the Application GUI
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQmlComponent component(&engine, url);
    QObject *object = component.create();

    // Get the singleton and initialize FrameComponent via JSON
    FrameComponent *frameCompSingleton = FrameComponent::frameComponentSingleton();
    qDebug() << frameCompSingleton;

    if (frameCompSingleton != nullptr) {
            parseJson(frameCompSingleton);
            frameCompSingleton->print_info();

    } else {
        qDebug() << "frameComponent object not found!!";
    }

//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
