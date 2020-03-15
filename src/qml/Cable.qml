import QtQuick 2.12
import QtQuick.Shapes 1.12


Shape {

    antialiasing: true

    function setup(outputConnector, inputConnector) {
        console.log(outputConnector)
    }

    ShapePath {
        strokeWidth: 2
        strokeColor: "black"
        fillColor: "transparent"
        startX: 0
        startY: 0

        PathCubic {
            x: 200; y: 200
            relativeControl1X: 100
            relativeControl1Y: 0
            relativeControl2X: 100
            relativeControl2Y: 200
        }

    }

}
