import QtQuick 2.0


ListModel
{
    ListElement
    {
        name: "Control";
        operators:
        [
            ListElement
            {
                name: "Increasing Value"
            },
            ListElement
            {
                name: "Sine Wave"
            },
            ListElement
            {
                name: "Noise Wave"
            }
        ]
    }
    ListElement
    {
        name: "Texture";
        operators:
        [
            ListElement
            {
                name: "Sine Wave"
            },
            ListElement
            {
                name: "Square Wave"
            },
            ListElement
            {
                name: "Sawtooth Wave"
            }
        ]
    }
    ListElement
    {
        name: "Mesh"
        operators:
        [
            ListElement
            {
                name: "Transform"
            },
            ListElement
            {
                name: "Noise Displace"
            },
            ListElement
            {
                name: "Clip"
            }
        ]
    }
    ListElement { name: "PointCloud"; operators: [] }
    ListElement { name: "Audio"; operators: [] }
}
