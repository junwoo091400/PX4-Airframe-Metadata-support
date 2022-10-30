#ifndef FRAMES_H
#define FRAMES_H

#include <QList>
#include <QJsonDocument>
#include <QObject>
#include <QVariantList>

/**
 * @brief The Frames class defining a single frame (could be a group)
 *
 * Class properties follow the Frame schema defined in the `frames.schema.json`.
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

public:
    /**
     * @brief Constructor
     *
     * Note: This had to be added, since the `Frames` class needs to be compatible
     * to `QObject` in a sense of data handling at the `DataObjectModel` level.
     *
     * @param parent Generic QObject parent item needed to store this in `DataObjectModel`
     * @param parent_frame Parent Frame Group that this frame belongs to
     */
    Frames(QObject* parent, Frames* parent_frame);
    ~Frames();

    /**
     * @brief Parse a single airframe object in the JsonDocument
     *
     * Schema is defined in `frames.schema.json/#/$defs/frame`
     */
    bool parseJson(const QJsonObject &json);

    void print_info(QString prefix = "") const;

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
    // Parent Frames node
    Frames *_parentFrame{nullptr};

    // Required properties
    FrameType _type{FrameType::FrameUndefined};
    QString _name;
    int _frame_id{FRAME_ID_UNDEFINED};

    // Subgroup that holds many different sub-frames
    QList<Frames*> _subgroups;

    // Non-required properties
    QString _description;
    QString _imageEnum;
    QString _imageUrl; // this gets set by default via imageEnum, but can be overwritten by image-url in JSON
    QString _manufacturer;
    QString _productUrl;

    friend class FrameComponent;
};

#endif // FRAMES_H
