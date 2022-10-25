#ifndef FRAMES_H
#define FRAMES_H

#include <QList>
#include <QJsonDocument>
#include <QObject>
#include <qqml.h>

/**
 * @brief The Frames class defining either a group or a final frame object
 *
 * Class properties follow the schema defined in the `frames.schema.json`.
 */

enum class FrameType {
    FrameUndefined = 0,     // Undefined
    FrameGroup = 1,         // Group: has valid `_subgroup` QList
    FrameEndNode = 2        // End-mode
};

static constexpr int FRAME_ID_UNDEFINED = -1;

class Frames
{
public:
    Frames();

    /**
     * @brief Parse a single airframe object in the JsonDocument
     *
     * Schema is defined in `frames.schema.json/#/$defs/frame`
     */
    bool parseJson(const QJsonObject &json);

    void print_info() const;

private:
    // Required properties
    FrameType _type{FrameType::FrameUndefined};
    QString _name;

    // Required for `FrameType::FrameGroup`
    QList<Frames*> _subgroups;
    int _frame_id{FRAME_ID_UNDEFINED};

    // Non-required properties
    QString _description;
    QString _imageUrl;
    QString _manufacturer;
    QString _productUrl;
};


/**
 * @brief The Frames_Root class defining the root level frames definition of the JSON
 *
 * This includes the version information and other highest-level information contained in the
 * Frames.json file.
 */
class Frames_Root : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<Frames*>* selectedFrames READ selectedFrames NOTIFY selectedFramesChanged)
    Q_PROPERTY(QString frames_id_param_name READ frames_id_param_name NOTIFY frames_id_param_name_changed)

    // Make this class available in QML
    QML_ELEMENT

public:
    Frames_Root(QObject *parent = nullptr);

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
    QList<Frames*>* selectedFrames() const { return _selectedFrames; }

    QString frames_id_param_name() const { return _frames_id_param_name; }

signals:
     void selectedFramesChanged();
     void frames_id_param_name_changed();

private:
    /**
     * @brief List of `Frames`, which can contain other Frames in it's subgroup
     */
    QList<Frames*> _frames;

    /**
     * @brief Pointer to the frame list that user selected to view
     */
    QList<Frames*>* _selectedFrames;

    int _schema_version{0};
    QString _frames_id_param_name;
};

#endif // FRAMES_H
