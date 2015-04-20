import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import com.bsu.chessGA 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 400
    height: 400
    visible: true

    Wrapper {
        id: api
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"))
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit()
            }
        }
    }

    Grid {
        id: qml_grid_chessGrid
        columns: 8
        spacing: 0
        width: parent.width * 0.9
        height: parent.height * 0.9
        x: parent.width / 2 - width / 2
        y: parent.width / 2 - height / 2
        rows: 8

        // 64 ChessBoard tiles - from top left to buttom right
        Repeater {
            id: blocks
            model: 64
            Rectangle {
                width: parent.parent.width / 8 * 0.9
                height: parent.parent.height / 8 * 0.9
                color: ((Math.floor(index / 8) % 2) === 0)
                        ?
                    (index % 2  === 1 ? "#D18B47" : "#FFCE9E") // light brown &
                        :
                    (index % 2  === 0 ? "#D18B47" : "#FFCE9E") // dark brown
                function getIndex() { return index }
                ChessPiece {
                    source: setIndex(parent.getIndex())
                }
            }
         }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }

    Row {
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        spacing: 4

        WindowButton {
            id: about
            source: "qrc:/Buttons/Images/Buttons/info.png"
            function callback() { aboutWindow.show() }
        }

        WindowButton {
            id: exit
            source: "qrc:/Buttons/Images/Buttons/close.png"
            function callback() { api.close() }
        }
    }

    About {
        id: aboutWindow
    }

}
