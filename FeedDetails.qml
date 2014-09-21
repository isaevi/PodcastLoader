import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

FocusScope {
    property var currentFeed: null

    signal updated()
    signal requestedNew(string title, url url, string dir, string prefix)
    signal canceled()

    function initControls(feed) {
        currentFeed = feed;
        if(currentFeed !== null) {
            titleLabel.text = feed.title;
            titleInput.input = feed.title;
            dirInput.input = feed.dir;
            urlInput.input = feed.url;
            prefixInput.input = feed.prefix;
        }
        else {
            titleLabel.text = "*** New Feed ***"
            titleInput.input = "Please, enter the title";
            dirInput.input = "";
            urlInput.input = "";
            prefixInput.input = "";
        }

    }

    function updateFeed() {
        if(currentFeed !== null) {
            currentFeed.title = titleInput.input;
            currentFeed.prefix = prefixInput.input;
            currentFeed.dir = dirInput.input;
            currentFeed.url = urlInput.input;
            updated()
        }
        else
            requestedNew(titleInput.input, urlInput.input, dirInput.input, prefixInput.input)
    }

    Keys.onReturnPressed: applyClicked()
    Keys.onEscapePressed: canceled()

    Column {
        anchors.fill: parent
        spacing: 4
        anchors.margins: 4

        RowLayout {
            width: parent.width
            Label {
                id: titleLabel
                font.bold: true
                width: parent.width
                Layout.alignment: "AlignHCenter"
            }
        }
        Grid {
            id: gridDetails
            rows: 4
            width: parent.width
            Row {
                id: titleRow
                LabeledTextInput {
                    id: titleInput
                    title: qsTr("Title:")
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
                    title: qsTr("Prefix:")
                    width: gridDetails.width/2 - 40
                    KeyNavigation.left: titleInput
                    KeyNavigation.tab: urlInput
                    KeyNavigation.down: urlInput
                }
            }
            LabeledTextInput {
                id: urlInput
                title: qsTr("Url:")
                width: parent.width

                KeyNavigation.up: titleRow
                KeyNavigation.down: dirInput
                KeyNavigation.tab: dirInput
            }
            LabeledTextInput {
                id: dirInput
                title: qsTr("Dir:")
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
                        updateFeed()
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
}
