#ifndef FRAMES_H
#define FRAMES_H

#include <QList>
#include <QJsonDocument>

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
class Frames_Root
{
public:
    Frames_Root();

    /**
     * @brief Parse provided JsonDocument data struct
     *
     * Schema is defined in `frames.schema.json`
     */
    bool parseJson(const QJsonDocument &json);

    void print_info() const;

private:
    /**
     * @brief List of `Frames`, which can contain other Frames in it's subgroup
     */
    QList<Frames*> _frames;

    int _schema_version{0};
    QString _frames_id_param_name;
};

#endif // FRAMES_H
