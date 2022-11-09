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
    width: 940
    height: 600
    minimumWidth: 560
    minimumHeight: 320

    title: qsTr("QOptimizer")

    MessageDialog {
        id: aboutBox

        title: "About QOptimizer"
        text: "QOptimizer " + program.version

        informativeText: "\nBased on Optimizer by ....."
                         + "\n\nBuild on " + program.buildDate
                         + "\n\n2022 Develop by RickyDevs"
                         + "\n\nThe program is provided AS IS with NO WARRANTY OF ANY KIND.\nAll changes performed to the system are user driven and USE BY YOUR ON RISK.\n"

        icon: StandardIcon.Information
    }

    MessageDialog {
        id: todoBox
        title: "About QOptimizer"
        text: "TODO"
        icon: StandardIcon.Information
    }

    ExclusiveGroup {
          id: radioInputGroup
    }

    menuBar: MenuBar {
        Menu {
            title: "&Profiles"
            MenuItem {
                text: "&All";
                checkable: true
                checked: true
                exclusiveGroup: radioInputGroup
                onTriggered: todoBox.open()
            }
            MenuItem {
                text: "&Gamer";
                checkable: true
                exclusiveGroup: radioInputGroup
                onTriggered: todoBox.open()
            }
            MenuItem {
                text: "&Internet/office work";
                checkable: true
                exclusiveGroup: radioInputGroup
                onTriggered: todoBox.open()
            }
            MenuSeparator {}
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
        mainPage.model = program.createModel('MainModel');
    }

}
