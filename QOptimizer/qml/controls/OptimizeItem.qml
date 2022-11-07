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
            property bool _activationNeedsConnect: true;
            id: toggleButton
            manualSwitchMode: true
            width: 50
            height: root.indent == 0? 26 : 24
            anchors.top: parent.top
            anchors.right: parent.right

            onActivating: {
                console.log('onActivating', model.identifier);
                //root.activateOptimize(model.identifier);

                if ( _activationNeedsConnect) {
                    _activationNeedsConnect = false;
                    model.activeChanged.connect(onActiveChanged)
                }

                delayedButtonAction.performActivation = true
                delayedButtonAction.start()
                // TODO autoCancelAction.start();
            }

            onDeactivating: {
                console.log('onDeactivating', model.identifier);
                //root.deactivateOptimize(model.identifier);

                delayedButtonAction.performActivation = false
                delayedButtonAction.start()
            }

            function onActiveChanged() {
                console.log('onActivationChanged response');
                autoCancelAction.stop();
                finishSwitch()
            }

            Timer {
                property bool performActivation

                id: delayedButtonAction
                interval: 55
                running: false
                repeat: false
                onTriggered: {
                    if (performActivation) {
                        model.activate();
                    } else {
                        model.deactivate();
                    }
                }
            }

            Timer {
                id: autoCancelAction
                interval: 1800
                running: false
                repeat: false
                onTriggered: {
                    toggleButton.finishSwitch(true);
                }
            }
        }
    }

    onModelChanged: {
        name.text = model.name;
        description.text = model.description;
        toggleButton._activationNeedsConnect = true;
        toggleButton.state = model.isActive() ? "on" : "off";
    }
}
