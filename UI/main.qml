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
        id: wrapper
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
                color: refresh(true)

                function refresh(flag) {
                    if (flag) {
                        return ((Math.floor(getIndex() / 8) % 2) === 0)
                            ?
                        (getIndex() % 2  === 1 ? "#D18B47" : "#FFCE9E") // light brown &
                            :
                        (getIndex() % 2  === 0 ? "#D18B47" : "#FFCE9E") // dark brown
                    } else {
                        for (var i = 0; i < 64; i++)
                            blocks.itemAt(i).color = blocks.itemAt(i).refresh(true);
                    }
                }

                function moveColor(list) {
                    console.log("int moveColor: ", list[0]);
                    list.forEach(function(item) {
                        blocks.itemAt(item).color = "#555"
                    })
                }

                function getIndex() { return index }
                function updateCell(type, color) {
                    console.log("in updateCell", index, " curPiece", wrapper.pos, type, color);
                    children[0].source = children[0].updateIcon(type, color);
                }


                ChessPiece {
                    source: (function() {
                        wrapper.pos = parent.getIndex();
                        return updateIcon(wrapper.type, wrapper.color)
                    })()
                }

                MouseArea {
                    anchors.fill: parent;
                    onClicked: (function() {
                        wrapper.pos = parent.getIndex();
                        var moveList = wrapper.moveList;
                        parent.refresh();
                        parent.moveColor(moveList);
                        console.log("onClicked: ", parent.getIndex(), "moveList", moveList);
                    })()
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
            function callback() {
                console.log(blocks.itemAt(0).children[0].source);           // get access to cell of board
                aboutWindow.show();
                blocks.itemAt(wrapper.pos).updateCell(wrapper.type, wrapper.color);           //////////////////////////////////// working string
            }
        }

        WindowButton {
            id: exit
            source: "qrc:/Buttons/Images/Buttons/close.png"
            function callback() { Qt.quit() }
        }
    }

    About {
        id: aboutWindow
    }

}
