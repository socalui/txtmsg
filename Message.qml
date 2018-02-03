import QtQuick 2.0
import CHMessage 1.0

Item {
    width: parent.width
    height: 40

    Rectangle {
        width: parent.width * .8
        height: parent.height

        color: "lightgray"

        Text {
            text: "This is some text"
            anchors.fill: parent
        }
    }


}
