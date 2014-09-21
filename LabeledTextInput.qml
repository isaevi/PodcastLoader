import QtQuick 2.3
import QtQuick.Layouts 1.1

FocusScope {
    id: labeledTextInput
    width: 100
    height: input.height + 12

    property alias title: label.text
    property alias input: input.text

    RowLayout  {
        id: row
        anchors.fill: parent

        spacing: 4

        Text {
            id: label
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            color: "lightsteelblue"
            border.color: "gray"
            Layout.fillWidth: true
            anchors.verticalCenter: parent.verticalCenter
            height: input.height + 8

            TextInput {
                id: input
                width: parent.width-8
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                focus: true
                clip: true
            }
        }
    }
}
