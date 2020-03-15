import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12


Dialog
{
    modal: true

    background: Rectangle {
        anchors.fill: parent
        border.width: 0
        radius: 25
    }


    ListView {
        id: list
        x: 20;
        y: 100;
        width: 500;
        height: 500;
        clip: true
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 0
        currentIndex: 0
        focus: true
        model: availableOperatorPackages

        delegate: Rectangle {

            height: 45
            width: parent.width
            color: "transparent"

            Rectangle {
                height: 45;
                width: innerText.contentWidth + 20
                color: "lightgray"
                visible: index == list.currentIndex
                radius: 6
            }

            Text {
                id: innerText
                text: display;
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
                font.pointSize: hoverHandler.hovered  ? 16 : 12
                color: index == "black"
                clip: false
            }

            TapHandler {
                onTapped: list.currentIndex = index
            }

            HoverHandler {
                id: hoverHandler
            }
        }

    }

}
