import QtQuick 2.2
import QtQuick.Controls 1.2

Item {
    id: button1
    state: "off"
    width: 66
    height: 32
    property string backgroundColorOn: ''
    property bool manualSwitchMode: false
    property bool lockedMode: false

    signal activating;
    signal deactivating;

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    function finishSwitch(cancel) {
        if (!manualSwitchMode) {
            return;
        }
        if (cancel === undefined) {
            cancel = false;
        }

        if (button1.state === 'deactivating') {
            button1.state = cancel? 'on': 'off';
        }
        if (button1.state === 'activating') {
            button1.state = cancel? 'off': 'on';
        }
    }

    Rectangle {
        id: background0
        anchors.fill: parent
        anchors.margins: 1
        border.width: button1.height > 25? 3 : 2.1;
        border.color: myPalette.shadow
        radius: height
        color: 'transparent'
        Item {
            anchors.fill: parent
            anchors.margins: button1.height > 25? 7 : 6;

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
        function switchState() {
            if (lockedMode) {
                return;
            }

            if (button1.manualSwitchMode) {
                if (button1.state === 'on') {
                    button1.state = 'deactivating';
                    deactivating();
                }
                if (button1.state === 'off') {
                    button1.state = 'activating';
                    activating();
                }
            } else {
                button1.state = (button1.state === 'on')? 'off' : 'on';
            }
        }

        id: button1area
        anchors.fill: background0
        onClicked: {
            switchState();
        }
    }

    function getColorOn() {
        var colorOn = backgroundColorOn? backgroundColorOn : myPalette.highlight;
        return colorOn;
    }

    states: [
        State {
            name: "off"
            PropertyChanges { target: background0; color: 'transparent'; border.color: myPalette.shadow }
            PropertyChanges { target: knob; color: myPalette.shadow; x: 0 }
        },
        State {
            name: "activating"
            PropertyChanges { target: background0; color: Qt.lighter(myPalette.shadow, 1.2) ; border.color: Qt.lighter(myPalette.shadow, 1.2) }
            PropertyChanges { target: knob; color: myPalette.base; x: parent.width / 5 } //parent.width - width - 2 }
        },
        State {
            name: "deactivating"
            PropertyChanges { target: background0; color: getColorOn() ; border.color: getColorOn() }
            PropertyChanges { target: knob; color: myPalette.base; x: 4 * parent.width / 5 - width } //2 }
        },
        State {
            name: "on"
            PropertyChanges { target: background0; color: getColorOn() ; border.color: getColorOn(); opacity: lockedMode? 0.7 : 1 }
            PropertyChanges { target: knob; color: myPalette.base; x: parent.width - width }
        }
    ]
}
