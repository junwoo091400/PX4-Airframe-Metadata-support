import QtQuick 2.15

// Qml definition of a single Frame/group view
// It will display the `Frames*` object

Rectangle {
    id: frameView
    property var frame // Frame* pointer we are referencing to
    property bool selected: false // Defines whether this frame is selected by the user (if it is an End node)

    width: _boxWidth; height: _boxHeight
    color: selected ? "red" : "lightgreen"

    // Name
    Text {
        id: frameName
        font.pointSize: _defaultFontPointSize
        text: frame.name
    }

    // Image
    Rectangle {
        anchors {
            top: frameName.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        Image {
            id: frameImage
            source: frame.image_url
            anchors {
                margins: 5
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            fillMode: Image.PreserveAspectFit
        }
    }
}
