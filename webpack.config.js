
const path = require('path');

module.exports = {
  entry: {
    timer: './lib/js/src/Timer.js'
  },
  output: {
    path: path.join(__dirname, "bundledOutputs"),
    filename: '[name].js',
  },
};