#ifndef FRAMES_H
#define FRAMES_H

#include <QList>
#include <QJsonDocument>
#include <QObject>
#include <QVariantList>
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

class Frames : public QObject
{
    Q_OBJECT

    // Basic properties
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(int frame_id READ getFrameid NOTIFY frameidChanged)

    // Optional properties
    Q_PROPERTY(QString image_url READ getImageurl NOTIFY imageurlChanged)
    Q_PROPERTY(QString description READ getDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString manufacturer READ getManufacturer NOTIFY manufacturerChanged)
    Q_PROPERTY(QString product_url READ getProducturl NOTIFY producturlChanged)

    // Make this class available in QML
    QML_ELEMENT

public:
    Frames();

    /**
     * @brief Parse a single airframe object in the JsonDocument
     *
     * Schema is defined in `frames.schema.json/#/$defs/frame`
     */
    bool parseJson(const QJsonObject &json);

    void print_info() const;

    QString getName() { return _name; }
    int getFrameid() { return _frame_id; }
    QString getImageurl() { return _imageUrl; }
    QString getDescription() { return _description; }
    QString getManufacturer() { return _manufacturer; }
    QString getProducturl() { return _productUrl; }

signals:
    void nameChanged();
    void frameidChanged();
    void imageurlChanged();
    void descriptionChanged();
    void manufacturerChanged();
    void producturlChanged();

private:
    // Required properties
    FrameType _type{FrameType::FrameUndefined};
    QString _name;

    // Required for `FrameType::FrameGroup`
    QList<Frames*> _subgroups;
    int _frame_id{FRAME_ID_UNDEFINED};

    // Non-required properties
    QString _description;
    QString _imageEnum;
    QString _imageUrl; // this gets set by default via imageEnum, but can be overwritten by image-url in JSON
    QString _manufacturer;
    QString _productUrl;

    friend class Frames_Root;
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

    Q_PROPERTY(QList<Frames*>* selectedFrames READ selectedFrames WRITE setSelectedFrames NOTIFY selectedFramesChanged)
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
    QList<Frames*> const *selectedFrames() { return _selectedFrames; }

    void setSelectedFrames(QList<Frames*> const *frames);

    QString frames_id_param_name() const { return _frames_id_param_name; }

    /**
     * @brief QML invokable function to process when user selects a frame
     */
    Q_INVOKABLE bool selectFrame(const Frames *frame);

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
    QList<Frames*> const *_selectedFrames;

    int _schema_version{0};
    QString _frames_id_param_name;
};

#endif // FRAMES_H
