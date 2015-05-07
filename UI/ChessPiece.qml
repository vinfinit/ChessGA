import QtQuick 2.0

Image {
    id: chessPiece
    width: parent.width * 0.7
    height: parent.height * 0.7
    x: parent.width / 2 - width / 2
    y: parent.width / 2 - height / 2

    function updateIcon(type, color) {
        return "qrc:/ChessPieces/Images/ChessPieces/" + type + "_" + color + ".svg"
    }
}

