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
        height: 21
        anchors.verticalCenter: parent.verticalCenter
        x: 6
        font.pixelSize: height * 0.65
    }
    Label {
        id: info
        height: 21
        anchors.verticalCenter: parent.verticalCenter
        x: 120
        font.pixelSize: height * 0.65
    }

    onModelChanged: {
        name.text = model.name;
        info.text = model.info;

    }
}
