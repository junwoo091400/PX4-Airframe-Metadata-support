import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import FrameComponent 1.0

Window {
    id: mainPage
    visible: true
    title: qsTr("Main Page")
    width: 1000; height: 1000

    // Properties
    property real _defaultFontPointSize: 10
    property real _defaultFontPixelWidth: 10
    property real _defaultFontPixelHeight: 10
    property real _boxWidth: _defaultFontPixelWidth * 20
    property real _boxHeight: _defaultFontPixelHeight * 15
    property real _boxSpacing: _defaultFontPixelWidth

    // Module that has objectified json data
    FrameComponent {
        id: frameComponent
        objectName: "frameComponent"
    }

    // Background Color
    Rectangle {
        anchors.fill: parent
        objectName: "rect"
        color: "lightblue"
    }

    Text {
        id: framesParamName
        text: frameComponent.frames_id_param_name
    }

    Button {
        id: gotoParentButton
        anchors.left: framesParamName.right

        text: "Go to parent"
        onClicked: {
            frameComponent.gotoParentFrame();
        }
    }

    // Frames collage view
    Flow {
        id: framesCollageView
        width: parent.width
        anchors.top: framesParamName.bottom
        spacing: _boxSpacing

        Repeater {
            id: framesRepeater
            model: frameComponent.selectedFrames

//            onModelChanged: {
//                framesAnimation.running = true
//                console.log('onModelChanged called!')
//            }

//            Connections {
//                target: frameComponent
//                function onSelectedFramesChanged() {
//                    framesAnimation.running = true
//                    console.log('onModelChanged called!')
//                }
//            }

            Frame {
                id: frameId
                frame: modelData

                NumberAnimation {
                    id: framesAnimation
                    target: frameId
                    property: "x"
                    duration: 1000
                    to: 0; from: framesCollageView.width
                    easing.type: Easing.InOutQuad
                }

                Component.onCompleted: {
                    framesAnimation.running = true
                    console.log('Component.onCompleted called!')
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        frameComponent.selectFrame(modelData)
                    }
                }
            }
        }

    }
}
