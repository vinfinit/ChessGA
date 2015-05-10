import QtQuick 2.0

Image
{
  id: button
  width: 20
  height: 20

  // Область, обрабатывающая "мышиные" сообщения
  MouseArea
  {
    anchors.fill: parent

    id: mouseArea

    onClicked: callback()
  }

  states : [
      State {
          // Произвольное название
          name: "hovered"
          // Указание на то, когда элемент переходит в это состояние
          // в данном случае когда нажата левая кнопка мыши
          when: mouseArea.pressed
          // Какие свойства будут изменяться в этом состоянии
          // в данном случае это будет прозрачность
          PropertyChanges { target: button; opacity: 1;}
      },
      State {
          name: "normal"
          // В это состояние элемент будет переходить
          // когда левая кнопка мыши не нажата
          when: mouseArea.pressed == false
          PropertyChanges { target: button; opacity: 0.7; }
      }]
  Behavior on opacity {
      // Анимация с шагом в 100 миллисекунд
      // Раз в 100 миллисекунд прозрачность будет изменяться
      // на 0,1
      NumberAnimation { duration: 100 }
    }
}
