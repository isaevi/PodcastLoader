import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import com.podcaster.data 1.0

Window {
    id: root
    visible: true

    property bool modalMode: list.expandedItem !== null;

    width: 800
    height: 480
    title: "Podcast Loader"

    property real defaultSpacing: 10
    property int bottomPanelsHeigh: 30
    function showBusyIndicator(show){
        rssList.visible = !show;
        fetchingRecorsIndicator.visible = show;
    }

    Desaturate {
        id: colorize
        source: ShaderEffectSource {
            sourceItem: mainFrame
            hideSource: blurEffect.visible;
        }
        desaturation: 0

        anchors.fill: mainFrame;
    }

    FastBlur {
        id: blurEffect
        source: ShaderEffectSource {
            sourceItem: colorize
            hideSource: true;
        }

        radius: 0
        anchors.fill: mainFrame;
        visible: false
    }

    Item {
        id: mainFrame
        anchors.fill: parent
        Grid {
            id: grid
            columns: 2
            rows: 2
            width: parent.width
            height: parent.height


            Connections {
                target: rssManager
                onStartQueringRecords: showBusyIndicator(true)
                onEndQueringRecords: showBusyIndicator(false)
            }

            ListView {
                id: list
                focus: true

                KeyNavigation.down: addFeedBtn
                KeyNavigation.tab: addFeedBtn
                KeyNavigation.backtab: addFeedBtn

                property Item expandedItem;
                interactive: expandedItem === null;
                width: 240
                height: parent.height  - bottomPanelsHeigh
                clip: true
                model: config.feeds
                delegate: FeedItemDelegate {
                    onResetFeed: config.resetFeedAt(list.currentIndex)
                    onSelectionChanged: {
                        if(list.currentIndex > -1)
                        {
                            rssManager.setActiveFeed(config.feedAt(list.currentIndex))
                        }
                    }
                }
                highlight: Rectangle { color: "steelblue" }
                highlightMoveVelocity: 9999999

                onCountChanged: deleteFeedBtn.enabled = list.currentIndex !== -1
            }
            FocusScope {
                width: parent.width - list.width
                height: parent.height  - bottomPanelsHeigh

                ListView {
                    id: rssList
                    anchors.fill: parent
                    clip: true

                    model: rssManager.rssRecords
                    delegate: RssRecordsDelegate {
                        onLaunchDownloading: {
                            if(rssList.currentIndex > -1)
                            {
                                downloader.addRecordForDownloading(rssManager.rssAt(rssList.currentIndex))
                            }
                        }
                    }
                }

                BusyIndicator {
                    id: fetchingRecorsIndicator
                    anchors.fill: parent
                    visible: false
                }
            }

            RowLayout {
                id: leftBottomPanel
                height: bottomPanelsHeigh
                width: 240
                Button {
                    id: addFeedBtn

                    KeyNavigation.backtab: list
                    KeyNavigation.up: list
                    KeyNavigation.tab: deleteFeedBtn

                    text: "Add Feed"
                    Layout.alignment: "AlignRight"
                    onClicked: {
                        config.addStubFeed()
                        list.currentIndex = list.count - 1
                        list.expandedItem = list.currentItem
                    }
                }
                Button {
                    id: deleteFeedBtn

                    KeyNavigation.tab: list
                    KeyNavigation.backtab: addFeedBtn
                    KeyNavigation.up: list

                    text: "Remove Feed"
                    Layout.alignment: "AlignLeft"
                    enabled: list.currentIndex != -1
                    onClicked: {
                        config.removeAt(list.currentIndex)
                    }
                }
            }

            RowLayout {
                id: rightBottomPanel
                width: parent.width - list.width
                height: bottomPanelsHeigh
                Button {
                    id: downloadAllRecords
                    text: "Download all"
                    Layout.alignment: "AlignRight"
                    onClicked: {
                        for(var i = 0; i < rssList.count; ++i)
                            downloader.addRecordForDownloading(rssManager.rssAt(i))
                    }
                }
            }
        }

        states: [
            State {
                when: root.modalMode
                name: "deactivated"
                PropertyChanges {
                    target: mainFrame
                    enabled: false
                }

                PropertyChanges {
                    target: blurEffect
                    visible: true
                    radius: 24
                }

                PropertyChanges {
                    target: colorize
                    desaturation: 0.8
                }
            }
        ]

        transitions: [
            Transition {
                NumberAnimation {
                    targets: [blurEffect, colorize];
                    properties: "radius, desaturation";
                    duration: 200
                }
            }
        ]
    }

    Item {
        id: modalContainer
        anchors.fill: parent
    }
}
