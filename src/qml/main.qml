import QtQuick 2.12
import QtQuick.Window 2.12


Window {
    id: window
    visible: true
    width: 1200
    height: 800
    title: qsTr("Hello World")

    NetworkView
    {
        id: network;
    }
}
