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

import "controls"
import "page1"

Item {

    property alias model: treeView.model

    MainTreeView {
        id: treeView
        width: 320
        height: parent.height

        function updateControls(itemIndex) {
            var obj = treeView.model.data(itemIndex, 258);
            //console.log(obj);
            panelView.showObject(obj)
            expand(itemIndex)
            treeView.model.checkForPendingUpdates(itemIndex);
        }

        onClicked: {
            updateControls(index)
        }

        Keys.onReturnPressed: {
            if (treeView.currentIndex.valid) {
                updateControls(treeView.currentIndex)
            }
        }
    }

    MainPanelView {
        id: panelView
        anchors.fill: parent
        anchors.leftMargin: treeView.width
    }
}

