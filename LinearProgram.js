/* jslint node: true */
'use strict';

var lp_solve = require('bindings')('lp_solve').LinearProgram;
var Row = require('./Row.js');

function LinearProgram() {
	this.Columns = { };
	this.lp_solve = new lp_solve();
	this.Constraints = [];
	this.ObjectiveFunc = new Row();
}

LinearProgram.prototype.setOutputFile = function(fname) {
	var str = typeof fname !== 'undefined' ? String(fname) : '';

	if (!this.lp_solve.setOutputFile(str)) {
		throw new Error('error writing to file \'' + str + '\'');
	}

	return this;
};

LinearProgram.prototype.addColumn = function(name, isInteger, isBinary) {

	var id = this.Columns[name] = Object.keys(this.Columns).length + 1;

	if (name === undefined) {
		name = "unamed_" + id;
	}

	this.lp_solve.addColumn(name, id);

	if (isInteger === true) {
		this.lp_solve.setColumnInteger(id, true);
	}

	if (isBinary === true) {
		this.lp_solve.setColumnBinary(id, true);
	}

	return name;
};

LinearProgram.ConstraintTypes = {'LE':1,'EQ':3,'GE':2};
LinearProgram.ConstraintText = {'LE':'<=','EQ':'=','GE':'>='};

LinearProgram.prototype.addConstraint = function(row, constraint, constant, name) {
	var rowId = [];
	var rowValues = [];
	var raw = row.raw;

	for (var k in raw) {
		if (k !== 'constant') {
			rowValues.push(raw[k]);
			rowId.push(this.Columns[k]);
		} else {
			constant -= raw[k];
		}
	}

	var constrainttype = LinearProgram.ConstraintTypes[constraint];

	this.Constraints.push({ name: name, row: row.ToText(), constraint: constraint, constant: constant });

	return this.lp_solve.addConstraint(name, rowId, rowValues, constrainttype, constant);
};

LinearProgram.prototype.setObjective = function(row, minimize) {
	var rowId = [];
	var rowValues = [];
	var raw = row.raw;

	for (var k in raw) {
		if (k !== 'constant') {
			rowValues.push(raw[k]);
			rowId.push(this.Columns[k]);
		} else {
			this.adjustObjective = raw[k];
		}
	}

	if (minimize === undefined) minimize = true;

	this.ObjectiveFunc = { minimize: minimize, row: row };

	return this.lp_solve.setObjective(minimize, rowId, rowValues);
};

LinearProgram.SolveResult = {
	'-5': 'UNKNOWNERROR',
	'-4': 'DATAIGNORED',
	'-3': 'NOBFP',
	'-2': 'NOMEMORY',
	'-1': 'NOTRUN',
	'0': 'OPTIMAL',
	'1': 'SUBOPTIMAL',
	'2': 'INFEASIBLE',
	'3': 'UNBOUNDED',
	'4': 'DEGENERATE',
	'5': 'NUMFAILURE',
	'6': 'USERABORT',
	'7': 'TIMEOUT',
	'8': 'RUNNING',
	'9': 'PRESOLVED'
};

LinearProgram.prototype.solve = function() {
	var res = this.lp_solve.solve();

	if (res === 0 || res == 1 || res == 9)
		this.solutionVariables = this.getSolutionVariables();

	return { code: res, description: LinearProgram.SolveResult[res] };
};

LinearProgram.prototype.getObjectiveValue = function() {
	return this.lp_solve.getObjectiveValue() + (this.adjustObjective || 0);
};

LinearProgram.prototype.getSolutionVariables = function() {
	return this.lp_solve.getSolutionVariables();
};

LinearProgram.prototype.calculate = function(row) {
	var val = 0;
	var raw = row.raw;
	for (var k in raw) {
		val += this.get(k) * raw[k];
	}
	return val;
};

LinearProgram.prototype.get = function(variable) {
	if (variable == 'constant') return 1;
	return this.solutionVariables[this.Columns[variable] - 1];
};

LinearProgram.prototype.dumpProgram = function() {
	var ret = (this.ObjectiveFunc.minimize ? 'minimize' : 'maximize') + ':' + this.ObjectiveFunc.row.ToText() + ';\n';
	for (var v in this.Constraints) {
		var c = this.Constraints[v];
		ret += (c.name ? (c.name + ': '): '') + c.row + ' ' + LinearProgram.ConstraintText[c.constraint] + ' ' + c.constant + ';\n';
	}
	return ret;
};

module.exports = LinearProgram;
