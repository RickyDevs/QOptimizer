import QtQuick 2.2
import QtQuick.Controls 1.2

Item {
    id: button1
    state: "off"
    width: 72
    height: 38
    property string backgroundColorOn: ''

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    Rectangle {
        id: background0
        anchors.fill: parent
        anchors.margins: 6
        border.width: 3
        border.color: myPalette.shadow
        radius: height
        color: 'transparent'
        Item {
            anchors.fill: parent
            anchors.margins: 7

            Rectangle {
                id: knob
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                width: height
                radius: height
                color: myPalette.button
            }
        }


    }


    MouseArea {
        id: button1area
        anchors.fill: background0
        onClicked: parent.state = (parent.state == "on") ? "off" : "on"
    }

    function getColorOn() {
        return backgroundColorOn? backgroundColorOn : myPalette.highlight;
    }

    states: [
        State {
            name: "off"
            PropertyChanges { target: background0; color: 'transparent'; border.color: myPalette.shadow }
            PropertyChanges { target: knob; color: myPalette.shadow; x: 0 }
        },
        State {
            name: "on"
            PropertyChanges { target: background0; color: getColorOn() ; border.color: getColorOn() }
            PropertyChanges { target: knob; color: myPalette.base; x: parent.width - width }
        }
    ]
}
