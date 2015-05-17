import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    id: loadWindow

    width: parent.width
    height: parent.height

    color: "transparent"
    opacity: 0
    visible: opacity > 0

    property int curPlayers: 0
    property int curColor: 0
//    property int host: 0
//    property int client: 0

    onCurPlayersChanged: {
        one.checked = curPlayers == 0
        two.checked = curPlayers == 1
        if (curPlayers == 1) {
            colorRow.enabled = false
            curColor = 0
        } else {
            colorRow.enabled = true
        }
    }

    onCurColorChanged: {
        white.checked = curColor == 0
        black.checked = curColor == 1
    }

    function hide() {
        loadWindow.opacity = 0
    }

    function show() {
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
                        id: one
                        text: "One"
                        checked: true
                        exclusiveGroup: players
                        onClicked: {
                            curPlayers = 0
                        }
                    }
                    RadioButton {
                        id: two
                        text: "Two"
                        exclusiveGroup: players
                        onClicked: {
                            curPlayers = 1
                        }
                    }
                }

                Row {
                    id: colorRow
                    spacing: 10
                    Text { text: qsTr("Play as") }

//                    enabled: false

                    ExclusiveGroup { id: color }
                    RadioButton {
                        id: white
                        text: "White"
                        checked: true
                        exclusiveGroup: color
                        onClicked: {
                            curColor = 0
                        }
                    }
                    RadioButton {
                        id: black
                        text: "Black"
                        exclusiveGroup: color
                        onClicked: {
                            curColor = 1
                        }
                    }
                }

                Button {
                    text: "Start"
                    onClicked: callback()
                }

                Button {
                    text: "Host"
                    onClicked: host()
                }

                Button {
                    text: "Client"
                    onClicked: client()
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
