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
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {

    function showObject(obj) {
        title.text = obj.DisplayName;
        if (obj.Type.indexOf("HEADER") > 0) {
            todo.text = "TODO: show list of items\n TODO: show optimizations on/off .. ( 0)"
        } else if (obj.Type.indexOf("ITEM") > 0) {
            todo.text = "TODO: show list of items"
        } else {
            todo.text = ""
        }

        var list = optimizeManager.query();
        console.log("list.lenght", list.length);
        list[0].activate();
    }

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }


    Rectangle {
        anchors.fill: parent
        color: myPalette.base
    }

    Item {
        id: innerArea
        anchors.fill: parent
        anchors.margins: 18

        Column {
            x:0
            y:4
            spacing: 2

            Label {
                id: title
                //font.bold: true
                width: parent.width
                //height: 80
                font.pixelSize: 26
            }


            Label {
                id: todo

            }
        }
    }

}
