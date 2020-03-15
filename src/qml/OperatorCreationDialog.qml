import QtQuick 2.12
import QtQuick.Controls 2.14
import QtQuick.Shapes 1.12


Dialog
{
    modal: true

    background: Rectangle
    {
        anchors.fill: parent
        border.width: 0
        radius: 25
    }

    contentItem: SplitView
    {
        anchors.fill: parent
        anchors.margins: 15
        orientation: Qt.Horizontal

        ListView
        {
            id: packageNames

            SplitView.preferredWidth: 180;

            clip: true
            highlightFollowsCurrentItem: true
            highlightMoveDuration: 0
            currentIndex: 0
            focus: true
            model: availableOperatorPackages

            delegate: Rectangle {

                height: 28
                width: parent.width
                color: "transparent"

                Rectangle {
                    height: 25
                    width: innerText.contentWidth + 12
                    anchors.verticalCenter: parent.verticalCenter
                    color: "lightgray"
                    visible: index == packageNames.currentIndex
                    radius: 6
                }

                Text {
                    id: innerText
                    text: display;
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    font.pixelSize: hoverHandler.hovered  ? 17 : 14
                    color: "black"
                    clip: false
                }

                TapHandler {
                    onTapped:
                    {
                        packageNames.currentIndex = index
                        packageContents.model = operatorLibrary.getOperatorPackage(display)
                    }
                }

                HoverHandler {
                    id: hoverHandler
                }
            }

        }

        ListView
        {
            id: packageContents
            clip: true

            delegate: Rectangle
            {
                id: packageDelegate;
                height: 30
                width: txt.contentWidth + 12
                Text
                {
                    x: 10
                    y: 0
                    id: txt
                    text: name
                    font.pixelSize: packageDelegateHoverHandler.hovered  ? 17 : 14
                }

                TapHandler {
                    onTapped:
                    {
                        console.log(name)
                    }
                }

                HoverHandler {
                    id: packageDelegateHoverHandler
                }
            }

        }

    }



}
