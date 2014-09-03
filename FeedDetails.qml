import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

FocusScope {
    property alias titleInput: titleInput
    property alias prefixInput: prefixInput
    property alias dirInput: dirInput
    property alias urlInput: urlInput
    signal applyClicked()
    signal canceled()

    Keys.onReturnPressed: applyClicked()
    Keys.onEscapePressed: canceled()

    Grid {
        id: gridDetails
        rows: 4
        anchors.fill: parent
        spacing: 4
        anchors.margins: 4
        Row {
            id: titleRow
            LabeledTextInput {
               id: titleInput
               text: qsTr("Title:")
               width: gridDetails.width/2 + 30
               focus: true
               KeyNavigation.right: prefixInput
               KeyNavigation.tab: prefixInput
               KeyNavigation.down: urlInput
            }
            Rectangle {
                width: 10
                height: titleInput.height
                opacity: 0
            }
            LabeledTextInput {
               id: prefixInput
               text: qsTr("Prefix:")
               width: gridDetails.width/2 - 40
               KeyNavigation.left: titleInput
               KeyNavigation.tab: urlInput
               KeyNavigation.down: urlInput
            }
        }
        LabeledTextInput {
           id: urlInput
           text: qsTr("Url:")
           width: parent.width

           KeyNavigation.up: titleRow
           KeyNavigation.down: dirInput
           KeyNavigation.tab: dirInput
        }
        LabeledTextInput {
           id: dirInput
           text: qsTr("Dir:")
           width: parent.width
           KeyNavigation.up: urlInput
           KeyNavigation.down: applyBtn
           KeyNavigation.tab: applyBtn
        }

        RowLayout {
            width: parent.width
            Button {
                id: applyBtn
                Layout.alignment: "AlignRight"
                text: qsTr("Apply")
                onClicked: {
                    applyClicked()

                }
                KeyNavigation.up: dirInput
                KeyNavigation.tab: cancelBtn
                KeyNavigation.left: cancelBtn
            }
            Button {
                id: cancelBtn
                Layout.alignment: "AlignLeft"
                text: qsTr("Cancel")
                onClicked: {
                    canceled()
                }
                KeyNavigation.up: dirInput
                KeyNavigation.tab: titleRow
                KeyNavigation.right: applyBtn
            }
        }
    }
}
