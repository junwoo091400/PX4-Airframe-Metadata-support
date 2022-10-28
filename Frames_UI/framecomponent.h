#ifndef FRAMECOMPONENT_H
#define FRAMECOMPONENT_H

#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>

#include "frames.h"
#include "dataobjectmodel.h"

/**
 * @brief The FrameComponent class is objectified version of the frames JSON file
 *
 * This includes the version information and other highest-level information contained in the
 * Frames.json file.
 */
class FrameComponent : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DataObjectModel* selectedFrames READ selectedFrames NOTIFY selectedFramesChanged)
    Q_PROPERTY(QString frames_id_param_name READ frames_id_param_name NOTIFY frames_id_param_name_changed)

    // Make this class available in QML
    QML_NAMED_ELEMENT(FrameComponent)

public:
    FrameComponent();

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
    DataObjectModel* selectedFrames() { return _selectedFrames; }

    /**
     * @brief Setter for the list of frames to display
     */
    void setSelectedFrames(QList<Frames*> frames);

    /**
     * @brief Getter for the parameter name corresponding to the Frame ID
     */
    QString frames_id_param_name() const { return _frames_id_param_name; }

    /**
     * @brief QML invokable function to process when user selects a frame
     *
     * This should update the selectedFrames property to the underlaying layer of frames
     */
    Q_INVOKABLE bool selectFrame(Frames *frame);

signals:
     void selectedFramesChanged();
     void frames_id_param_name_changed();

private:
    /**
     * @brief List of `Frames`, which can contain other Frames in it's subgroup
     */
    QList<Frames*> _frames;

    /**
     * @brief DataObjectModel containing the frame list that user selected to view
     */
    DataObjectModel* _selectedFrames = new DataObjectModel(this);

    int _schema_version{0};
    QString _frames_id_param_name;
};

#endif // FRAMECOMPONENT_H
