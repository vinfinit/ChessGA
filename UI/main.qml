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
        property bool flag: false
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
        spacing: 0
        width: parent.height
        height: parent.height
        rows: 8
        columns: 8

        // 64 ChessBoard tiles - from top left to buttom right
        Repeater {
            id: blocks
            model: 64

            Rectangle {
                width: parent.width / 8
                height: parent.height / 8
                color: refresh(true)

                function refresh(flag) {
                    if (flag) {
                        return ((Math.floor(getIndex() / 8) % 2) !== 0)
                            ?
                        (getIndex() % 2  === 1 ? "#D18B47" : "#FFCE9E") // light brown &
                            :
                        (getIndex() % 2  === 0 ? "#D18B47" : "#FFCE9E") // dark brown
                    } else {
                        for (var i = 0; i < 64; i++)
                            blocks.itemAt(i).color = blocks.itemAt(i).refresh(true);
                    }
                }

                function repaint() {
                    for(var i = 0; i < 64; i++) {
                        wrapper.pos = i;
                        blocks.itemAt(i).updateCell(wrapper.type, wrapper.color);
                    }
                }

                function moveColor(list) {
                    list.forEach(function(item) {
                        blocks.itemAt(item).color = "#555";
                    });
                    wrapper.flag = true;
                }

                function attackColor(list) {
                    list.forEach(function(item) {
                        blocks.itemAt(item).color = "#500";
                    });
                    wrapper.flag = true;
                }

                function checkColor(pos) {
                    console.log("check color");
                    blocks.itemAt(pos).color = "#404"
                }

                function getIndex() { return index }
                function updateCell() { children[0].source = children[0].callback() }

                ChessPiece {
                    source: callback();

                    function callback() {
                        wrapper.pos = parent.getIndex();
                        return updateIcon(wrapper.type, wrapper.color)
                    }
                }

                MouseArea {
                    anchors.fill: parent;
                    onClicked: (function() {
                        var moveList, attackList;

                        if (!wrapper.flag) {
                            wrapper.pos = parent.getIndex();
                            wrapper.moveFrom = parent.getIndex();
                            moveList = wrapper.moveList;
                            attackList = wrapper.attackList;
                        } else {
                            wrapper.moveTo = parent.getIndex();
                            wrapper.flag = false;
                        }
                        parent.refresh();

                        if (wrapper.check !== -1) parent.checkColor(wrapper.check)

                        if (moveList || attackList) {
                            parent.moveColor(moveList);
                            parent.attackColor(attackList);
                        }
                        console.log("onClicked: ", parent.getIndex(), "moveList", moveList);
                        console.log("onClicked: ", parent.getIndex(), "attackList", attackList);
                        parent.repaint();
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
                var tmp, res = wrapper.res;
                if (res == 0) tmp = "None";
                if (res == 1) tmp = "Draw";
                if (res == 2) tmp = "Mate"
                aboutWindow.show(tmp);
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
