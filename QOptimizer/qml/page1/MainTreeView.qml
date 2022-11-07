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

TreeView {
    id: treeView

    //width: flickableItem.contentWidth
    //height: flickableItem.contentHeight + 2
    alternatingRowColors: false

    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    headerVisible: false

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }


    Component {
        id: treeStyle
        TreeViewStyle {
            frame: Item {}
            backgroundColor: myPalette.alternateBase
        }
    }

    style: treeStyle

    rowDelegate: Component {
        Item {
            height: 50

//            function bgColor() {
//                if (styleData.pressed)
//                    return 'red';//myPalette.dark
//                if (styleData.hasActiveFocus)
//                    return myPalette.dark;
//                return 'blue'
//            }
//            Rectangle {
//                anchors.fill: parent
//                color: bgColor()

//            }
        }
    }

    TableViewColumn {
        //role: "query"
        role: "object"
        width: parent.width

        delegate: Component {
            Item {
//                implicitHeight: 130
                function getIcon(image) {
                    var ico = styleData.value.DisplayIcon;
                    if (image) {
                        return String.fromCharCode(0xED51); // TODO
                    }
                    if (!ico || ico.indexOf("charcode:") !== 0) {
                        return String.fromCharCode(0xED51); // TODO
                    }
                    var charcode = parseInt(ico.substr(9));
                    return String.fromCharCode(charcode);
                }

                Rectangle {
                    //anchors.fill: parent
                    x: -parent.x
                    width: treeView.width
                    height: parent.height

                    color: styleData.selected? myPalette.mid : myPalette.alternateBase
                }
                Text {
                    id: icon
                    x: 0
                    y: (parent.height - height)* 0.6
                    //anchors.verticalCenter: parent.verticalCenter
                    text: getIcon(false)
                    //font.pixelSize: Math.floor(parent.height * 0.36)
                    font.pointSize: 13
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    x: 30
                    //font.pixelSize: Math.floor(parent.height * 0.28)
                    text: styleData.value.DisplayName
                    font.pointSize: 11
                }
            }
        }
    }

}
