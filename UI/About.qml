import QtQuick 2.0

Rectangle
{
    id: about

    function show() {
        about.opacity = 1
    }

    function hide() {
        about.opacity = 0
    }

    // Прозрачный задний фон
    color: "transparent"
    // Полностью прозрачен по умолчанию
    opacity: 0

    width: parent.width
    height: parent.height

    // Видимым элемент будет считаться если выполняется условие
    // opacity > 0
    visible: opacity > 0

    // Дочерний элемент, создающий полупрозрачный фон
    Rectangle {
        anchors.fill: parent
        opacity: 0.5
        color: "gray"
    }

    // Дочерний элемент создающий который является диалогом
    // "О программе..."
    Rectangle
    {
        id: dialog

        width: 360
        height: 230

        x: parent.width / 2 - dialog.width / 2;
        y: parent.height / 2 - dialog.height / 2;
        z: 10

        border.color: "gray"

        Text {
            text: "4 Toddler"
            font.bold: true
            font.pixelSize: 22

            // Выравнивание элемента по центру
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Behavior on opacity {
        NumberAnimation { duration: 100 }
    }

    MouseArea
    {
        // Элемент полностью заполняет родительский элемент
        anchors.fill: parent;

        // При клике в любом месте прячем окно
        onClicked: hide();
    }
}
