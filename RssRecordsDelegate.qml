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
    property color textColor : rssRecordsDelegate.ListView.isCurrentItem ? "white" : "black"

    signal launchDownloading()

    MouseArea {
        anchors.fill: rssRecordsDelegate
        onClicked: {
            rssRecordsDelegate.ListView.view.currentIndex = index
            //selectionChanged()
        }
    }

    FocusScope {
        id: rssContent
        anchors {
            fill: parent
            rightMargin: 10
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
                    anchors.topMargin: 5
                }
            }
            Item{
                id: progressInfo
                width: 40
                //color: "yellow"
                Layout.row: 0
                Layout.rowSpan: 2
                Layout.column: 1
                Layout.fillHeight: true
                Layout.alignment: "AlignRight"

                BusyIndicator {
                    id: progressIndicator
                    anchors.fill: parent
                    visible: status == RecordInfo.Downloading
                }
                Text {
                    text: status == RecordInfo.Downloaded? "saved" : (downloadPercent == 0? "" : downloadPercent + "%")
                    anchors.centerIn: parent
                }
            }
            Item {
                width: 40
                Layout.row: 0
                Layout.rowSpan: 2
                Layout.column: 2
                Layout.fillHeight: true
                Layout.alignment: "AlignRight"
                Image {
                    id: downloadButton
                    source: "img/download_media.png"
                    fillMode: Image.PreserveAspectFit
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
                    color: textColor
                }

                Label {
                    id: dateText
                    text: date
                    color: textColor
                    font { family: "Helvetica"; pixelSize: 10; bold: false }
                }

                Item { width: 30 }
                Label {
                    text: "Size:"
                    color: textColor
                }
                Label {
                    text: (length/1024/1024).toFixed(2) + "(MB)"
                    color: textColor
                    font { family: "Helvetica"; pixelSize: 10; bold: false }
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
