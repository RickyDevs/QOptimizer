// helper for compiling in typescript

interface QOtimizeManagerSearchMap {
    tag: string;
}

interface QOptimizeItem {
    identifier: string;
    name: string;

    childItems: Array<QOptimizeItem>;
}

interface WbemDetailItem {
    name: string;
    info: string;
}

interface QOtimizeManager {
    query(searchMap: QOtimizeManagerSearchMap) : Array<QOptimizeItem>;
}

var optimizeManager: QOtimizeManager;

interface WbemObject {
    Type: string;
    DisplayName: string;
}

namespace BS {
    export var ByteSize: IByteSize;
}

//--------

// OptimizeItem.qml
interface QmlOptimizeItem { 
    model: QOptimizeItem;
    indent: number;
    activateOptimize(identifier: string): void;
    deactivateOptimize(identifier: string): void;
}