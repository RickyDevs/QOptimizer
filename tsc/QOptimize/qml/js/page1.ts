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

///.import "bytesize.js" as BS

function countModelListItems(modelList: Array<any>) {
    var count = modelList.length;
    for (var x in modelList) {
        count+= modelList[x].childItems.length;
    }
    return count;
}

function fillOptimizeItemList(wbemObj: WbemObject, optimizeItemList: Qt.Repeater) {
    var type = tagTypeFromWbemObj(wbemObj);
    var modelList = optimizeManager.query({tag: type});
    //console.log("list.lenght", modelList.length);
    optimizeItemList.model = countModelListItems(modelList)
    var idx = 0;
    for (var x in modelList) {
        //console.log(optimizeItemList.itemAt(idx));
        var modelItem = modelList[x];

        optimizeItemList.itemAt(idx).model = modelItem;
        idx++;

        if (modelItem.childItems.length > 0) {
            for (var y in modelItem.childItems) {
                var modelSubItem = modelItem.childItems[y];

                optimizeItemList.itemAt(idx).model = modelSubItem;
                optimizeItemList.itemAt(idx).indent = 1;
                idx++;

            }
        }
    }
}

function findQmlOptimizeItem(identifier: string, optimizeItemList: Qt.Repeater): QmlOptimizeItem {
    for (var idx = 0; idx < optimizeItemList.count; idx++) {
        var item = optimizeItemList.itemAt(idx) as QmlOptimizeItem;
        if (item.model.identifier == identifier) {
            return item;
        }
    }
}

function fillDetailItemList(wbemObj: WbemObject, detailItemList: Qt.Repeater) {
    var skipFields = ['Type', 'DisplayName', 'ByteSizeMask'];
    var fields = Object.keys(wbemObj).filter((i: string) => {
        return skipFields.indexOf(i) < 0;
    });
    console.log(fields);
    detailItemList.model = fields.length;
    
    var idx = 0;
    var byteSizeMask = wbemObj['ByteSizeMask'] || '';

    for (var k in wbemObj) {
        if (skipFields.indexOf(k) >= 0) {
            continue;
        }
        var v = wbemObj[k];
        if (byteSizeMask.indexOf(k + "=") >= 0) {
            if (byteSizeMask.indexOf(k + "=k;") >= 0) {
                v = BS.ByteSize.fromKiloBytes(v).toString();
            } else if  (byteSizeMask.indexOf(k + "=b;") >= 0) {
                v = BS.ByteSize.fromBytes(v).toString();
            }
        }

        detailItemList.itemAt(idx).model = {
            name: k,
            info: v
        }
        idx++;
    }
}

function isWbemHeaderType(wbemObj: WbemObject) {
    return wbemObj.Type.indexOf("HEADER") > 0;
}

function isWbemItemType(wbemObj: WbemObject) {
    return wbemObj.Type.indexOf("ITEM") > 0;
}

function tagTypeFromWbemObj(wbemObj: WbemObject) {
    var type = wbemObj.Type;
    return type.substr(0, type.indexOf('_'));
}