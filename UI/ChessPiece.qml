import QtQuick 2.0

Image {
    id: chessPiece
    width: parent.width * 0.7
    height: parent.height * 0.7
    x: parent.width / 2 - width / 2
    y: parent.width / 2 - height / 2

    source: "qrc:/ChessPieces/Images/ChessPieces/bishop_black.svg"

    property int index: 0

    function show() {
        chessPiece.opacity = 0
    }

    function hide() {
        chessPiece.opacity = 0
    }

    function setIndex(i) {
        if (i === 24)
            return "qrc:/ChessPieces/Images/ChessPieces/bishop_white.svg"
        return "qrc:/ChessPieces/Images/ChessPieces/bishop_black.svg"
    }

    function updateIcon(type, color) {
        return "qrc:/ChessPieces/Images/ChessPieces/" + type + "_" + color + ".svg"
    }
}

