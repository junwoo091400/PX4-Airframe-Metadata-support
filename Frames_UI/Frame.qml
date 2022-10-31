import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

// Qml definition of a single Frame/group view
// It will display the `Frames*` object

Rectangle {
    id: frameView
    property var frame // Frame* pointer we are referencing to
    property bool selected: false // Defines whether this frame is selected by the user (if it is an End node)
    width: _boxWidth; height: _boxHeight
    color: frame.isEndNode ? "#00000000" : "#20000000" // Transparent if End-node

    // Main Column
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Name
        Rectangle {
            id: frameNameBackground
            color: "#00000000" // Transparent
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.1

            Text {
                id: frameName
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: _defaultFontPointSize * 1.5
                text: frame.name
            }
        }

        // Everything below the name
        Rectangle {
            color: selected ? "yellow" : "lightgreen"
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.9

            ColumnLayout {
                id: frameColumnLayout
                spacing: 0
                anchors.fill: parent

                // Image
                Rectangle {
                    color: "#20FFFFFF" // Tinted semi-trasnparent bright background
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height * 0.7

                    Image {
                        id: frameImage
                        anchors.fill: parent
                        anchors.margins: _boxSpacing // Have some margins for image
                        source: frame.image_url
                        fillMode: Image.PreserveAspectFit
                    }
                }

                // Description
                Rectangle {
                    color: "#20FFFFFF" // Tinted semi-trasnparent bright background
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height * 0.2

                    Text {
                        id: frameDescription
                        anchors.fill: parent
                        anchors.margins: _boxSpacing // Have some margins for description
                        font.pointSize: _defaultFontPointSize
                        wrapMode: Text.WordWrap
                        text: frame.description
                    }
                }

                // Manufacturer
                Rectangle {
                    color: "#20FFFFFF" // Tinted semi-trasnparent bright background
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height * 0.05

                    Text {
                        id: frameManufacturer
                        anchors.fill: parent
//                        anchors.margins: _boxSpacing // Have some margins for description
                        font.pointSize: _defaultFontPointSize
                        wrapMode: Text.WordWrap
                        text: frame.manufacturer
                    }
                }

                // URL
                Rectangle {
                    color: "#20FFFFFF" // Tinted semi-trasnparent bright background
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height * 0.05

                    Label {
                        id: frameUrl
                        anchors.fill: parent
                        font.pointSize: _defaultFontPointSize
                        text: "<a href='" + frame.product_url + "'>" + "link to product</a>"
                        color: "blue"
                        onLinkActivated: {
                            console.log("Trying to open: " + frame.product_url)
                            Qt.openUrlExternally(frame.product_url)
                        }
                    }
                }
            }
        }

    }
}
