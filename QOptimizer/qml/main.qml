/****************************************************************************
**
** QOptimizer
** Copyright (C) 2022 by RickyDevs
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

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
    width: 780
    height: 600
    minimumWidth: 560
    minimumHeight: 320

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
        //var x = ;
        //console.log(x, Models.mainModelData);

        mainPage.model = program.createModel('MainModel');
    }
}
