var st = require('./build/Release/statvfs');
var util = require('util');

var log = function() {
    var args = Array.prototype.slice.call(arguments);

    args.forEach(function(arg){
        console.log(util.inspect(arg, { showHidden: false, depth: null, colors: true }));
    });
}

log(st('/'));
