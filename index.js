/* jslint node: true */
'use strict';

var lp_solve = require('bindings')('lp_solve');
var Row = require('./Row.js');
var LinearProgram = require('./LinearProgram.js');

module.exports = {
	Row: Row,
	LinearProgram: LinearProgram,
	lp_solve: lp_solve,
	version: lp_solve.lp_solve_version()
};
