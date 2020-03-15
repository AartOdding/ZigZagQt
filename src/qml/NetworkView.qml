import QtQuick 2.0
import QtQuick.Controls 2.12


Item
{
    id: networkView
    anchors.fill: parent

    function selectConnector(connector)
    {
        console.log(connector)
    }

    Flickable
    {
        id: viewport
        anchors.fill: parent
        contentWidth: contents.width
        contentHeight: contents.height
        contentX: contents.width / 2 - width / 2;
        contentY: contents.height / 2 - height / 2;

        Rectangle
        {
            id: contents
            scale: zoomSlider.zoom;
            width: 10000
            height: 10000

            OperatorFrame
            {
                id: op1
                x: 5000
                y: 5000
            }

            OperatorFrame
            {
                id: op2
                x: 5300
                y: 5300
            }

            Cable
            {
                x: 5100
                y: 5100
            }
        }

        MouseArea {
            z: -1;
            anchors.fill: parent;
            propagateComposedEvents: true
            onClicked: mouse.accepted = false
            onDoubleClicked: operatorCreationDialog.visible = true
        }
    }


    Slider {
        id: zoomSlider
        from: -3
        to: 3
        value: 0
        orientation: Qt.Vertical
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 20
        anchors.rightMargin: 10
        property real zoom: Math.pow(2, value);
    }

    OperatorCreationDialog
    {
        id: operatorCreationDialog
        visible: false
        anchors.centerIn: parent;
        width: 0.7 * parent.width;
        height: 0.7 * parent.height;
    }

    MouseArea {
        z: -2;
        anchors.fill: parent;
        propagateComposedEvents: true
        onClicked:
        {
            console.log("clicked outer");
            mouse.accepted = false
        }
    }

}
