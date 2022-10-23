import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1

import "js/models.js" as Models

/*

import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Particles 2.0

*/




ApplicationWindow {
    visible: true
    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 300

    title: qsTr("QOptimizer")

    MessageDialog {
        id: aboutBox
        title: "About QOptimizer"
        text: "This is a basic text editor \nwritten with Qt Quick Controls"
        icon: StandardIcon.Information
    }


    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuItem { text: "Quit"; onTriggered: Qt.quit() }
        }
        Menu {
            title: "&Help"
            MenuItem { text: "About..." ; onTriggered: aboutBox.open() }
        }
    }

    Page1 {
        id: mainPage

        anchors.fill: parent



    }

    Component.onCompleted: {
        var x = program.createModel('MainModel', Models.mainModelData);
        console.log(x, Models.mainModelData);

        mainPage.model = x;
    }
}
