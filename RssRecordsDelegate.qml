import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import com.podcaster.data 1.0

FocusScope {
    id: rssRecordsDelegate
    height: heightOfVisiblePart
    anchors{
        left : parent.left
        right : parent.right
    }
    clip: true

    property int heightOfVisiblePart: 40
    property color textColor : rssRecordsDelegate.ListView.isCurrentItem ? "royalblue" : "black"
    property bool isDownloaded: downloadPercent == 100
    Gradient {
        id: newRss
        GradientStop { position: 0.0; color: "white" }
        GradientStop { position: 0.5; color: "whitesmoke" }
        GradientStop { position: 1.0; color: "lavender" }
    }
    Gradient {
        id: downloadedRss
        GradientStop { position: 0.0; color: "grey" }
        GradientStop { position: 0.5; color: "whitesmoke" }
        GradientStop { position: 1.0; color: "lavender" }
    }
    property Gradient backGroundGradient: isDownloaded ? downloadedRss : newRss

    signal launchDownloading()

    MouseArea {
        anchors.fill: rssRecordsDelegate
        onClicked: {
            rssRecordsDelegate.ListView.view.currentIndex = index
            //selectionChanged()
        }
    }

    Rectangle {
            id: background
            width: parent.width
            height: parent.height
            gradient: backGroundGradient
        }

    FocusScope {
        id: rssContent
        width: parent.width
        height: parent.height
        anchors{
            topMargin: 5
            bottomMargin: 5
        }

        GridLayout {
            id: commonView
            height: heightOfVisiblePart
            columns: 3
            anchors{
                top: parent.top
                left: parent.left; leftMargin: 15
                right: parent.right
            }

            RowLayout{
                id: firstRow
                Layout.fillWidth: true
                Label {
                    id: titleText
                    text: title
                    color: textColor
                    font { family: "Helvetica"; pixelSize: 12; bold: true }
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                    Layout.alignment: "AlignHCenter"
                }
            }
            Rectangle{
                width: 40
                color: "yellow"
                Layout.row: 0
                Layout.rowSpan: 2
                Layout.column: 1
                Layout.fillHeight: true
                Layout.alignment: "AlignRight"
                Text {
                    text: downloadPercent
                }
            }
            Item{
                width: 40
                //color: "blue"
                Layout.row: 0
                Layout.rowSpan: 2
                Layout.column: 2
                Layout.fillHeight: true
                Layout.alignment: "AlignRight"
                Image {
                    id: downloadButton
                    height: 32; width: 32
                    source: "img/download_media.png"
                    fillMode: Image.PreserveAspectFit
                    //Layout.alignment: "AlignHCenter" | "AlignVCenter"
                    anchors{
                        margins: 4
                        fill: parent
                    }

                    MouseArea {
                        anchors.fill: downloadButton
                        onClicked: {
                            rssRecordsDelegate.ListView.view.currentIndex = index
                            launchDownloading()
                        }
                    }
                }
            }

            RowLayout {
                id: secondRow
                Layout.fillWidth: true
                Label {
                    text: "Date:"
                }

                Label {
                    id: dateText
                    text: date
                    color: textColor
                    font { family: "Helvetica"; pixelSize: 10; bold: false }
//                    anchors {
//                        horizontalCenter: parent.horizontalCenter
//                        verticalCenter: parent.verticalCenter
//                    }
                }

                Item { width: 30 }
                Label {
                    text: "Size:"
                }
                Label {
                    text: (length/1024/1024).toFixed(2) + "(MB)"
                    color: textColor
                    font { family: "Helvetica"; pixelSize: 10; bold: false }
                    width: parent.width - 50
//                    anchors {
//                        horizontalCenter: parent.horizontalCenter
//                        top: titleText.bottom
//                        topMargin: 4
//                    }
                    //Layout.fillWidth: parent
                    //elide: Text.ElideMiddle
                }
            }
        }
    }
    Rectangle {
        width: parent.width;
        height: 1;
        color: "#cccccc"
        anchors.bottom: parent.bottom
        visible: rssRecordsDelegate.ListView.isCurrentItem ? false : true
    }
    Rectangle {
        width: parent.width;
        height: 1;
        color: "white"
        visible: rssRecordsDelegate.ListView.isCurrentItem ? false : true
    }
}
