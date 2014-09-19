import QtQuick 2.0
import com.podcaster.data 1.0
import QtQuick.Layouts 1.1

FocusScope {
    id: delegate
    width: parent.width
    height: heightOfVisiblePart
    clip: true

    signal resetFeed()
    signal selectionChanged(int new_index)
    signal showConfigurationFor(int index)
    property bool expanded: delegate === ListView.view.expandedItem

    MouseArea {
        anchors.fill: delegate
        onClicked: {
            selectionChanged(index)
        }
    }
    property int heightOfVisiblePart : 60
    property int heightOfDetailsPart : 110
    property int buttonsRightMargin : 5

    ColumnLayout {
        id: content
        anchors {
            fill: parent
            rightMargin: 10
        }

        Item {
            id: commonView
            height: heightOfVisiblePart
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }

            Text {
                id: titleText
                text: title
                color: delegate.ListView.isCurrentItem ? "white" : "black"
                font { family: "Helvetica"; pixelSize: 12; bold: true }
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
            }
            Text {
                text: url
                color: delegate.ListView.isCurrentItem ? "white" : "black"
                font { family: "Helvetica"; pixelSize: 10; bold: true }
                width: parent.width - 50
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    top: titleText.bottom
                    topMargin: 4
                }
                elide: Text.ElideMiddle
            }

            Image {
                id: settingsButton
                visible: !isAggregateStub
                height: 20; width: 20
                source: "img/settings.png"
                fillMode: Image.PreserveAspectFit
                anchors{
                    right: parent.right;
                    top: parent.top
                    rightMargin: buttonsRightMargin
                    topMargin: 20
                }

                MouseArea {
                    anchors.fill: settingsButton
                    onClicked: {
                        showConfigurationFor(index)
                    }
                }
            }
        }
    }

    Rectangle {
        width: delegate.width;
        height: 1;
        color: "#cccccc"
        anchors.bottom: delegate.bottom
        visible: delegate.ListView.isCurrentItem ? false : true
    }
    Rectangle {
        width: delegate.width;
        height: 1;
        color: "white"
        visible: delegate.ListView.isCurrentItem ? false : true
    }
}
