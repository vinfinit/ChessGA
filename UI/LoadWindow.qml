import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    id: loadWindow

    width: parent.width
    height: parent.height

    color: "transparent"
    opacity: 0
    visible: opacity > 0

    function hide() {
        loadWindow.opacity = 0
    }

    function show() {
        console.log("heoolllsd")
        loadWindow.opacity = 1
    }

    Rectangle {
        anchors.fill: parent
        opacity: 0.5
        color: "gray"
    }

    Rectangle {
        id: dialog

        width: parent.width * 0.8
        height: parent.height * 0.8

        x: parent.width / 2 - dialog.width / 2;
        y: parent.height / 2 - dialog.height / 2;
        z: 100

        border.color: "gray"

        MouseArea {
            anchors.fill: parent;
        }

        GroupBox {
            id: box
            x: parent.width / 2 - box.width / 2;
            y: parent.height / 2 - box.height / 2;

            Column {
                spacing: 10

                Row {
                    spacing: 10
                    Text { text: qsTr("Play mode") }

                    ExclusiveGroup { id: players }
                    RadioButton {
                        text: "One"
                        checked: true
                        exclusiveGroup: players
                    }
                    RadioButton {
                        text: "Two"
                        exclusiveGroup: players
                    }
                }

                Row {
                    spacing: 10
                    Text { text: qsTr("Play as") }

                    enabled: false

                    ExclusiveGroup { id: color }
                    RadioButton {
                        text: "White"
                        checked: true
                        exclusiveGroup: color
                    }
                    RadioButton {
                        text: "Black"
                        exclusiveGroup: color
                    }
                }

                Button {
                    text: "Start"
                    onClicked: callback()
                }
            }
        }
    }

    Behavior on opacity {
        NumberAnimation { duration: 100 }
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: hide();
    }
}
