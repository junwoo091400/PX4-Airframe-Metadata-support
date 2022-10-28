#include "framecomponent.h"

#include <QJsonObject>
#include <QJsonArray>

FrameComponent::FrameComponent(QObject *parent)
{
    // Do nothing
}

bool FrameComponent::parseJson(const QJsonDocument &json)
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

    // for now, set the selected frames as frames itself!
    setSelectedFrames(&_frames);

    return true;
}

void FrameComponent::print_info() const
{
    QString str = "";

    // Required values
    str.append(QString("Schema ver: %1 | Frames ID Param name: %2 | ").arg(QString::number(_schema_version), _frames_id_param_name));
    str.append(QString("Framegroups size: %1").arg(QString::number(_frames.length())));

    qDebug() << str;

    // Print out frames info
    if (!_frames.isEmpty()) {
        for (const auto &frame : _frames) {
            // Indent for each different frame categories
            frame->print_info("L-");
        }
    }
}

void FrameComponent::setSelectedFrames(QList<Frames*>* frames)
{
    _selectedFrames = frames;
    emit selectedFramesChanged();
}

bool FrameComponent::selectFrame(Frames *frame)
{
    // Show available options in the selected frame group
    if (!frame->_subgroups.isEmpty()) {
        _selectedFrames = &frame->_subgroups;
    }

    // User selected a final frame with no subgroups
    // TODO: Process final selection
    return true;
}
