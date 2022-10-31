#ifndef FRAMECOMPONENT_H
#define FRAMECOMPONENT_H

#include <QObject>
#include <QAbstractListModel>
#include <QModelIndex>

#include "frames.h"
#include "dataobjectmodel.h"

/**
 * @brief The FrameComponent class is objectified version of the frames JSON file
 *
 * This includes the version information and other highest-level information contained in the
 * Frames.json file.
 */
class FrameComponent : public Frames
{
    Q_OBJECT

    Q_PROPERTY(DataObjectModel* selectedFrames READ selectedFrames NOTIFY selectedFramesChanged)
    Q_PROPERTY(QString frames_id_param_name READ frames_id_param_name NOTIFY frames_id_param_name_changed)

public:
    FrameComponent(QObject *parent = nullptr);

    /**
     * @brief singleton type provider function (callback)
     *
     * This is used for registering `FrameComponent` as a Singleton Type
     **/
    static QObject *framecomponent_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
    {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        if (_frameCompSingleton == nullptr) {
            _frameCompSingleton = new FrameComponent(engine);
        }

        return _frameCompSingleton;
    }

    /**
     * @brief Singleton instance of the Frame Component
     */
    static FrameComponent *frameComponentSingleton() { return _frameCompSingleton; }

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

    /**
     * @brief Changes `_selectedFrames` to track parent frame group (if it exists)
     */
    Q_INVOKABLE bool gotoParentFrame();

//protected:
    // Singleton pointer
    // Note: Isn't it a bad practice to place singleton as mutable public member?
    static FrameComponent *_frameCompSingleton;

signals:
     void selectedFramesChanged();
     void frames_id_param_name_changed();

private:
//    /**
//     * @brief List of `Frames`, which can contain other Frames in it's subgroup
//     */
    // QList<Frames*> _frames;

    /**
     * @brief DataObjectModel containing the frame list that user selected to view
     */
    DataObjectModel* _selectedFrames = new DataObjectModel(this);

    int _schema_version{0};
    QString _frames_id_param_name;
};

#endif // FRAMECOMPONENT_H
