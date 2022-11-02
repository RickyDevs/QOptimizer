import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2


Item {
    id: root
    height: 38
    width: 400

    property var model;

    Label {
        id: name
        anchors.verticalCenter: parent.verticalCenter
        x: 6
    }
    Label {
        id: info
        anchors.verticalCenter: parent.verticalCenter
        x: 100
    }

    onModelChanged: {
        name.text = model.name;
        info.text = model.info;

    }
}
