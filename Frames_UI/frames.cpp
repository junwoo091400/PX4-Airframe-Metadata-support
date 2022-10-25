#include "frames.h"

#include <QJsonObject>
#include <QJsonArray>

// Frames - Node
Frames::Frames()
{

}

bool Frames::parseJson(const QJsonObject &json)
{
    // Parse rquired properties

    // Name
    QJsonValue name = json.value("name");
    if (!name.isNull() && name.isString()) {
        _name = name.toString();
    } else {
        qWarning() << "Frames name is not set!" << json;
    }

    // Type
    QString type = json.value("type").toString();
    if (type.isNull()) {
        qWarning() << "Type is undefined for airframe: " << _name;
    } else {
        _name = type;
    }

    // Non-required properties
    QString description = json.value("description").toString();
    if (!description.isNull()) {
        _description = description;
    }

    QString image = json.value("image").toString();
    if (!image.isNull()) {
        _imageUrl = image;
    }

    QString url = json.value("url").toString();
    if (!url.isNull()) {
        _productUrl = url;
    }

    QString manufacturer = json.value("manufacturer").toString();
    if (!manufacturer.isNull()) {
        _manufacturer = manufacturer;
    }

    // If it has a sub-group, parse them and append it to the list recursively
    QJsonArray subgroups = json.value("subgroups").toArray();
    for (const auto &&frameJson : subgroups) {
        Frames *new_frame = new Frames();
        QJsonObject frameObject = frameJson.toObject();
        new_frame->parseJson(frameObject);
        _subgroups.append(new_frame);
    }

    return true;
}

void Frames::print_info() const
{
    QString str = "";

    // Required values
    str.append(QString("name: %1, type: %2\n").arg(_name, QString::number((int)_type)));

    // Non-required values
    if (!_description.isEmpty()) {
        str.append(QString("description: %1\n").arg(_description));
    }

    if (!_imageUrl.isEmpty()) {
        str.append(QString("image URL: %1\n").arg(_imageUrl));
    }

    if (!_manufacturer.isEmpty()) {
        str.append(QString("manufacturer: %1\n").arg(_manufacturer));
    }

    if (!_productUrl.isEmpty()) {
        str.append(QString("Product URL: %1\n").arg(_productUrl));
    }

    qDebug() << str;

    // Print out subgroups info
    if (!_subgroups.isEmpty()) {
        // str.append(QString("Subgroups size: %1\n").arg(QString(_subgroups.length())));
        qDebug() << QString("Subgroups size: %1\n").arg(QString::number(_subgroups.length()));

        // Recursively call subgroup frame's print_info
        for (const auto &frame : _subgroups) {
            frame->print_info();
        }
    }
}

// Frames - Root
Frames_Root::Frames_Root(QObject *parent)
{
    // Do nothing
}


bool Frames_Root::parseJson(const QJsonDocument &json)
{
    QJsonObject obj = json.object();

    // Get Frame ID Parameter
    QJsonValue frameIdJson = obj.value("settings").toObject().value("frame_id_parameter");
    if (!frameIdJson.isNull() && frameIdJson.isString()) {
        _frames_id_param_name = frameIdJson.toString();
        emit frames_id_param_name_changed();
    } else {
        qWarning() << "Frames ID Parameter is not set!";
    }

    // Get Version
    QJsonValue versionJson = obj.value("version");
    if (!versionJson.isNull()) {
        _schema_version = versionJson.toInt();
    } else {
        qWarning() << "Frames ID Parameter is not set!";
    }

    // Get Frames data struct
    QJsonValue framesJson = obj.value("frames_v1");
    QJsonArray framesArray = framesJson.toArray();

    for (const auto &&frameJson : framesArray) {
        Frames *new_frame = new Frames();
        QJsonObject frameObject = frameJson.toObject();
        new_frame->parseJson(frameObject);
        _frames.append(new_frame);
    }

    return true;
}

void Frames_Root::print_info() const
{
    QString str = "";

    // Required values
    str.append(QString("Schema ver: %1, Frames ID Param name: %2\n").arg(QString::number(_schema_version), _frames_id_param_name));
    str.append(QString("Framegroups size: %1\n").arg(QString::number(_frames.length())));

    qDebug() << str;

    // Print out frames info
    if (!_frames.isEmpty()) {
        for (const auto &frame : _frames) {
            frame->print_info();
        }
    }
}
