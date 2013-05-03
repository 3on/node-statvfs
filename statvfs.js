var addon = require('./build/Release/statvfs');

module.exports = function(path) { 
    console.log(addon.test(path));
}