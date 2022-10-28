#include "frames.h"

#include <QJsonObject>
#include <QJsonArray>

// Frames - Node
Frames::Frames(Frames *parentItem)
    :_parentFrame(parentItem)
{

}

Frames::~Frames()
{
    qDeleteAll(_subgroups);
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

    } else if (type == "group") {
        _type = FrameType::FrameGroup;

    } else if (type == "frame") {
        _type = FrameType::FrameEndNode;

    } else {
        _type = FrameType::FrameUndefined;

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
        Frames *new_frame = new Frames(this);
        QJsonObject frameObject = frameJson.toObject();
        new_frame->parseJson(frameObject);
        _subgroups.append(new_frame);
    }

    return true;
}

void Frames::print_info(QString prefix) const
{
    QString str = "";

    // Required values
    str.append(QString("name: %1, type: %2 | ").arg(_name, QString::number((int)_type)));

    // Non-required values
    if (!_description.isEmpty()) {
        str.append(QString("description: %1 | ").arg(_description));
    }

    if (!_imageUrl.isEmpty()) {
        str.append(QString("image URL: %1 | ").arg(_imageUrl));
    }

    if (!_manufacturer.isEmpty()) {
        str.append(QString("manufacturer: %1 | ").arg(_manufacturer));
    }

    if (!_productUrl.isEmpty()) {
        str.append(QString("Product URL: %1").arg(_productUrl));
    }

    qDebug() << prefix + str;

    // Print out subgroups info
    if (!_subgroups.isEmpty()) {
        qDebug() << prefix + QString("Subgroups size: %1").arg(QString::number(_subgroups.length()));

        // Recursively call subgroup frame's print_info
        for (const auto &frame : _subgroups) {
            // Enlongate the prefix with "--"
            frame->print_info(prefix.append("--"));
        }
    }
}
