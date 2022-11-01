import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: root
    height: 58
    width: 400

    property var model;
    property int indent: 0

    SystemPalette {
        id: myPalette
        colorGroup: SystemPalette.Active
    }
    MouseArea {
        id: control
        anchors.fill: parent
        hoverEnabled: true
        Rectangle {
            id: background
            anchors.fill: parent
        }

        onEntered: {
            background.color = myPalette.alternateBase
        }
        onExited: {
            background.color = 'transparent'
        }
    }


    Item {
        anchors.fill: parent
        anchors.topMargin: 8
        anchors.rightMargin: 8
        anchors.bottomMargin: 8
        anchors.leftMargin: 8 + root.indent * 24

      /*  Rectangle {
            color: '#aaaaaa'
            anchors.fill: toggleButton
        }*/

        Label {
            id: name
            x: 0
            y: 0
            height: parent.height / 2
            font.pixelSize: height * 0.65
        }
        Label {
            id: description
            x: 0
            y: parent.height / 2 - 2
            height: parent.height / 2
            font.pixelSize: height * 0.65
            color: myPalette.shadow
        }
        ToggleButton {
            id: toggleButton
            width: 50
            height: 26
            anchors.top: parent.top
            anchors.right: parent.right
        }
    }



    onModelChanged: {
        name.text = model.name;
        description.text = model.description;

    }
}
