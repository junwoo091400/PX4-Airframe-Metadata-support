#ifndef FRAMES_H
#define FRAMES_H

#include <QList>

/**
 * @brief The Frames class defining either a group or a final frame object
 *
 * Class properties follow the schema defined in the `frames.schema.json`.
 */

class Frames
{
public:
    Frames();
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

private:
    QList<Frames> _frames;
};

#endif // FRAMES_H
