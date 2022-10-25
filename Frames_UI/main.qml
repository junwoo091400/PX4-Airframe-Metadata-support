import QtQuick 2.15
import QtQuick.Window 2.15

import frames_root 1.0

Window {
    id: mainPage
    visible: true
    title: qsTr("Main Page")
    width: 1500; height: 1000

    // Properties
    property real _defaultFontPointSize: 10
    property real _defaultFontPixelWidth: 10
    property real _defaultFontPixelHeight: 10
    property real _boxWidth: _defaultFontPixelWidth * 20
    property real _boxHeight: _defaultFontPixelHeight * 15
    property real _boxSpacing: _defaultFontPixelWidth

    // Module that has objectified json data
    Frames_Root {
        id: framesRoot
        objectName: "framesRoot"
    }

    // Background Color
    Rectangle {
        anchors.fill: parent
        objectName: "rect"
        color: "lightblue"
    }

    Text {
        id: framesParamName
        text: framesRoot.frames_id_param_name
    }

    // Frames collage view
    Flow {
        id: framesCollageView
        width: parent.width
        anchors.top: framesParamName.bottom
        spacing: _boxSpacing

        Repeater {
            id: framesRepeater
            model: framesRoot.selectedFrames

            // Single Frame/group view
            Rectangle {
                id: frameSingleView
                width: _boxWidth; height: _boxHeight
                color: "lightgreen"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // TODO: Add clicked event/signal
                    }
                }

                // Name
                Text {
                    id: frameName
                    font.pointSize: _defaultFontPointSize
                    text: "Frame Name no.1"
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
                        source: "images/Airship.svg"
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
        }

    }
}
