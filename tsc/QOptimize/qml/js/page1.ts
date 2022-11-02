

function countModelListItems(modelList: Array<any>) {
    var count = modelList.length;
    for (var x in modelList) {
        count+= modelList[x].childItems.length;
    }
    return count;
}

function fillOptimizeItemList(wbemObj: WbemObject, optimizeItemList: Qt.Repeater) {
    var type = tagTypeFrombemObj(wbemObj);
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

function fillDetailItemList(wbemObj: WbemObject, detailItemList: Qt.Repeater) {
    var skipFields = ['Type', 'DisplayName'];
    var fields = Object.keys(wbemObj).filter((i: string) => {
        return skipFields.indexOf(i) < 0;
    });
    console.log(fields);
    detailItemList.model = fields.length;
    
    var idx = 0;
    for (var k in wbemObj) {
        if (skipFields.indexOf(k) >= 0) {
            continue;
        }
        detailItemList.itemAt(idx).model = {
            name: k,
            info: wbemObj[k]
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

function tagTypeFrombemObj(wbemObj: WbemObject) {
    var type = wbemObj.Type;
    return type.substr(0, type.indexOf('_'));
}