

declare namespace Qt {
    export interface ListModel {
        append(dict: Object): void;
        clear(): void;
        get(index: number): Object;
        insert(index: number, dict:Object): void;
        move(from: number, to: number, n: number): void;
        remove(index: number, count?: number): void;
        set(index: number, dict: Object): void;
        setProperty(index: number, property: string, value: any): void;
        count: number;
        // sync()
    }

    export interface Repeater {
        model: number | ListModel;
        itemAt(index: number): Object | any
    }

    export interface Component {
        createObject(parent: Object, objectItem: Object): void;
    }

    export interface Point {
        x: number;
        y: number;
    }

    export interface Vector2d {
        x: number;
        y: number;

        plus(other: Vector2d): Vector2d;
        minus(other: Vector2d): Vector2d;
        times(factor: number): Vector2d;
        fuzzyEquals(other: Vector2d, epsilon?: number): boolean;
    }

    export interface MouseEvent {
        x: number;
        y: number;

        button: number;
    }

    export interface IncludeResult {
        status: number;
    }

    export function include(file: string): IncludeResult;
    export function point(x: number, y: number): Point;
        
    export function vector2d(x: number, y: number): Vector2d;

    export function isQtObject(obj: any): boolean;
    export function createQmlObject(qml: string, parent: any, filepath: string): any;

    export var application: Object;
}