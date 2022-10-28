#ifndef FRAMECOMPONENT_H
#define FRAMECOMPONENT_H

#include <QObject>
#include <qqml.h>

#include "frames.h"

/**
 * @brief The FrameComponent class is objectified version of the frames JSON file
 *
 * This includes the version information and other highest-level information contained in the
 * Frames.json file.
 */
class FrameComponent : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QList<Frames*>* selectedFrames READ selectedFrames NOTIFY selectedFramesChanged)
    Q_PROPERTY(QString frames_id_param_name READ frames_id_param_name NOTIFY frames_id_param_name_changed)

    // Make this class available in QML
    QML_ELEMENT

public:
    FrameComponent(QObject *parent = nullptr);

    /**
     * @brief Parse provided JsonDocument data struct
     *
     * Schema is defined in `frames.schema.json`
     */
    bool parseJson(const QJsonDocument &json);

    void print_info() const;

    /**
     * @brief Getter for the List of Frames to display
     */
    //QList<Frames*> const *selectedFrames() { return _selectedFrames; }

//    void setSelectedFrames(QList<Frames*> const *frames);

    QString frames_id_param_name() const { return _frames_id_param_name; }

    /**
     * @brief QML invokable function to process when user selects a frame
     */
    //Q_INVOKABLE bool selectFrame(const Frames *frame);

signals:
     //void selectedFramesChanged();
     void frames_id_param_name_changed();

private:
    /**
     * @brief List of `Frames`, which can contain other Frames in it's subgroup
     */
    QList<Frames*> _frames;

    /**
     * @brief Pointer to the frame list that user selected to view
     */
    QList<Frames*> const *_selectedFrames;

    int _schema_version{0};
    QString _frames_id_param_name;
};

#endif // FRAMECOMPONENT_H
