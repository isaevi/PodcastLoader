import QtQuick 2.0
import com.podcaster.data 1.0
import QtQuick.Layouts 1.1

FocusScope {
    id: delegate
    width: parent.width
    height: heightOfVisiblePart
    clip: true

    signal resetFeed()
    signal selectionChanged()
    property bool expanded: delegate === ListView.view.expandedItem

    MouseArea {
        anchors.fill: delegate
        onClicked: {
            delegate.ListView.view.currentIndex = index
            selectionChanged()
            //window.currentFeed = feed
        }
    }
    property int heightOfVisiblePart : 60
    property int heightOfDetailsPart : 110
    property int buttonsRightMargin : 5

    function initDetails() {
        feedDetails.titleInput.input.text = title;
        feedDetails.prefixInput.input.text = prefix;
        feedDetails.dirInput.input.text =  dir;
        feedDetails.urlInput.input.text = url;
    }

    function updateFeed() {
        title = feedDetails.titleInput.input.text;
        prefix = feedDetails.prefixInput.input.text;
        dir = feedDetails.dirInput.input.text;
        url = feedDetails.urlInput.input.text;
    }

    ColumnLayout {
        id: content
        width: parent.width
        height: parent.height

        Item {
            id: commonView
            height: heightOfVisiblePart
            //width: parent.width
            //anchors.top: parent.top
            anchors{
                top: parent.top
                //fill: parent
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
                        if(delegate.ListView.view.expandedItem === delegate)
                            delegate.ListView.view.expandedItem = null;
                        else {
                            delegate.ListView.view.expandedItem = delegate;
                            delegate.ListView.view.currentIndex = index
                            selectionChanged()
                        }
                        initDetails()
                    }
                }
            }
        }

        Item {
            id: detailsView
            height: heightOfDetailsPart
            anchors{
                left: parent.left
                right: parent.right
                top: commonView.bottom
                bottom: parent.bottom; bottomMargin: 2
            }

            FeedDetails {
                enabled: false;
                focus: true
                //width: parent.width
                anchors.fill: parent
                id: feedDetails
                onApplyClicked: {
                    if(delegate.ListView.view.expandedItem === delegate)
                    {
                        updateFeed()
                        delegate.ListView.view.expandedItem = null;
                    }
                }
                onCanceled: {
                    if(delegate.ListView.view.expandedItem === delegate)
                    {
                        delegate.ListView.view.expandedItem = null;
                        resetFeed()
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "expanded"
            when: delegate.expanded

            PropertyChanges {
                target: feedDetails
                enabled: true
            }

            PropertyChanges {
                target: settingsButton
                visible: false
            }

            PropertyChanges {
                target: content
                height: heightOfVisiblePart + heightOfDetailsPart
            }

            ParentChange {
                target: content
                parent: modalContainer
                x: modalContainer.width/4; y: modalContainer.height/4;
                width: modalContainer.width/2; height: modalContainer.height/2
            }
        }
    ]

    transitions: [
        Transition {
            ParallelAnimation {
                //PropertyAction { target: delegate; property: 'clip'; value: true }
                ParentAnimation {
                    via: modalContainer
                    NumberAnimation { properties: "x,y, width, height"; duration: 200; easing.type: Easing.InOutCubic }
                }
                NumberAnimation {
                    duration: 150;
                    properties: "height,width,anchors.rightMargin,anchors.topMargin,opacity"
                }

                //PropertyAction { target: delegate; property: 'clip'; value: false }
            }
        }
    ]

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
