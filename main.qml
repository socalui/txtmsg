import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import CHMessage 1.0


Window {
    visible: true
    width: 480
    height: 800
    title: qsTr("Hello World")

    Message {

    }

    Column {
        anchors.fill: parent
        Repeater {
            model:20
            Message {
                // stuff goes here?
            }
        }
    }













}
