import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: addFeedDialog
    visible: true
    title: "Add Feed"
    property int margin: 11
    width: mainLayout.implicitWidth + 2 * margin
    height: mainLayout.implicitHeight + 2 * margin
    minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
    minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: margin

        GroupBox {
            id: gridBox
            title: "Feed's properties"
            Layout.fillWidth: true

            GridLayout {
                id: gridLayout
                rows: 3
                flow: GridLayout.TopToBottom
                anchors.fill: parent

                Label { text: "Feed URL:" }
                Label { text: "Directory for storing:" }
                Label { text: "Prefix for file name:" }

                TextField {
                    id: feedUrl
                }
                TextField {
                    id: feedDir
                }
                TextField {
                    id: feedPrefix
                }
            }
        }

        RowLayout {
            anchors.right: parent.right
            anchors.top: gridBox.bottom
            Button {
                id: ok
                text: "OK"
            }
            Button {
                id: cancel
                text: "Cancel"
            }
        }
    }
}
