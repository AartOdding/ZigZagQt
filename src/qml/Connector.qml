import QtQuick 2.12



Rectangle
{
    width: 12;
    height: 24;
    z: -1
    color: mouseArea.containsMouse ? "#009900" : "transparent"

    border.color: "#009900"
    border.width: 3

    MouseArea
    {
        id: mouseArea;
        hoverEnabled: true;
        anchors.fill: parent;
        onClicked: network.selectConnector(parent);
    }
}
