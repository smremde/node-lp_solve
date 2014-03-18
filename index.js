/* jslint node: true */
'use strict';

var lp_solve = require('bindings')('lp_solve');
var Row = require('./Row.js');
var LinearProgram = require('./LinearProgram.js');

module.exports = {
	Row: Row,
	LinearProgram: LinearProgram,
	version: lp_solve.getVersion()
};
