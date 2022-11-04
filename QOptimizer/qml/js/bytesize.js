function ByteSize(bytes) {
    this.bytes = bytes;
    this.decimal = {
        bytesInKiloByte: 1000,
        bytesInMegaByte: 1000000,
        bytesInGigaByte: 1000000000,
        bytesInTeraByte: 1000000000000,
        bytesInPetaByte: 1000000000000000,
    };
    this.binary = {};
}
ByteSize.fromBytes = function (bytes) {
    //console.log('from bytes', bytes);
    return new ByteSize(bytes);
};
ByteSize.fromKiloBytes = function (bytes) {
    //console.log('from k bytes', bytes);
    return new ByteSize(bytes * 1000);
};
ByteSize.prototype.toString = function (format) {
    if (format === undefined) {
        format = 2;
    }
    var output = function (value, symbol) {
        return value.toFixed(format) + ' ' + symbol;
    };
    var test = {
        KiloBytes: this.bytes / this.decimal.bytesInKiloByte,
        MegaBytes: this.bytes / this.decimal.bytesInMegaByte,
        GigaBytes: this.bytes / this.decimal.bytesInGigaByte,
        TeraBytes: this.bytes / this.decimal.bytesInTeraByte,
        PetaBytes: this.bytes / this.decimal.bytesInPetaByte,
    };
    // Absolute value is used to deal with negative values
    if (Math.abs(test.PetaBytes) >= 1) {
        return output(test.PetaBytes, 'PB');
    }
    if (Math.abs(test.TeraBytes) >= 1) {
        return output(test.TeraBytes, 'TB');
    }
    if (Math.abs(test.GigaBytes) >= 1) {
        return output(test.GigaBytes, 'GB');
    }
    if (Math.abs(test.MegaBytes) >= 1) {
        return output(test.MegaBytes, 'MB');
    }
    if (Math.abs(test.KiloBytes) >= 1) {
        return output(test.KiloBytes, 'KB');
    }
    return output(test.PetaBytes, 'B');
};
