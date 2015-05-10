import QtQuick 2.0

Rectangle
{
    id: about

    function show(label) {
        about.opacity = 1;
        text.text = label;
    }

    function hide() {
        about.opacity = 0
    }

    // Прозрачный задний фон
    color: "transparent"
    // Полностью прозрачен по умолчанию
    opacity: 0

    // Ширина и высота устанавливаются равными
    // ширине и высоте родительского элемента
    // в данном случае это элемент с id: canvas
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

        // Ширина и высота являются фиксированными
        width: parent.width * 0.8
        height: parent.height * 0.8

        // Координаты верхнего левого угла вычисляются
        // исходя из размеров самого диалога и родителя
        // так, чтобы окно располагалось в центре
        x: parent.width / 2 - dialog.width / 2;
        y: parent.height / 2 - dialog.height / 2;
        // Задаем z индекс таким, чтобы он был
        // больше z тех элементов, которые должны остаться
        // за диалоговым окном
        z: 10

        border.color: "gray"

        Text {
            id: text
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

    MouseArea {
        // Элемент полностью заполняет родительский элемент
        anchors.fill: parent;

        // При клике в любом месте прячем окно
        onClicked: hide();
    }
}
