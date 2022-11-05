"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var folda = "/media/sf_ShareRD/developer/QOptimizer/QOptimizer/qml/";
var fs = require("fs");
function processFile(someFile) {
    fs.readFile(someFile, 'utf8', function (err, data) {
        if (err) {
            console.error(err);
            return;
        }
        var changed = false;
        if (data.indexOf("///.import") >= 0) {
            data = data.replace(/\/\/\/\.import/g, '.import');
            changed = true;
        }
        if (data.indexOf("///.pragma") >= 0) {
            data = data.replace(/\/\/\/\.pragma/g, '.pragma');
            changed = true;
        }
        if (!changed) {
            return;
        }
        console.log("processing...", someFile);
        fs.writeFile(someFile, data, 'utf8', function (err) {
            if (err) {
                console.error(err);
                return;
            }
        });
    });
}
var watch = require("watch");
watch.createMonitor(folda, function (monitor) {
    console.log("Qt TSC Monitor active...");
    monitor.on("created", function (f, stat) {
        // Handle new files
        console.log("create", f);
    });
    monitor.on("changed", function (f, curr, prev) {
        // Handle file changes
        console.log("changed", f);
        processFile(f);
    });
    monitor.on("removed", function (f, stat) {
        // Handle removed files
        console.log("rem", f);
    });
    //monitor.stop(); // Stop watching
});
