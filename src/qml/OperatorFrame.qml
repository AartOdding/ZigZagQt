import QtQuick 2.0


Rectangle {

    width: 200
    height: 160
    color: "transparent"
    border.color: "#000000"
    border.width: 3


    MouseArea {
        anchors.fill: parent
        drag.target: parent
    }


    Connector
    {
        id: inCon1

        x: -width + border.width
        y: 100
    }

    Connector
    {
        id: outCon1

        x: parent.width - border.width
        y: 50
    }

    Connector
    {
        id: outCon2

        x: parent.width - border.width
        y: 100
    }

    Cable {
        id: cable1
        x: outCon1.x
        y: outCon1.y
    }

}
