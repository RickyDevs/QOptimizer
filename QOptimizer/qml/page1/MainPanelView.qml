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
import "../controls"
import "../js/page1.js" as Page1JS

Item {

    function showObject(obj) {
        title.text = obj.DisplayName;
        if (Page1JS.isWbemHeaderType(obj)) {
            detailsItemList.model = 0;
            Page1JS.fillOptimizeItemList(obj, optimizeItemList)
        } else if (Page1JS.isWbemItemType(obj)) {
            optimizeItemList.model = 0;
            var leftTextLength = Page1JS.fillDetailItemList(obj, detailsItemList)
            console.log(leftTextLength)
            if (leftTextLength > 120) {
                Page1JS.adjustInfoLeftMargin(Math.ceil(leftTextLength /32) * 32, detailsItemList)
            }
        }
    }

    SystemPalette {
        id: myPalette;
        colorGroup: SystemPalette.Active
    }


    Rectangle {
        anchors.fill: parent
        color: myPalette.base
    }

    Item {
        id: innerArea
        anchors.fill: parent
        anchors.margins: 18

        Item {
            id: header
            x:0
            y:4
            height: 32
           // spacing: 2

            Label {
                id: title
                //font.bold: true
                width: parent.width
                //height: 80
                font.pixelSize: 26
            }
        }

        ScrollView {

//            Rectangle {
//                anchors.fill: parent
//                border.color: 'red'
//                border.width: 1
//            }

            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.topMargin: 6

            Column {
                y: 0
                x: 0
                Repeater {
                    id: optimizeItemList
                    delegate: Component {
                        OptimizeItem {

                        }
                    }
                }
            }
            Column {
                y: 0
                x: 0
                Repeater {
                    id: detailsItemList
                    delegate: Component {
                        DetailItem {

                        }
                    }
                }
            }
        } // ScrollView


    }

}
