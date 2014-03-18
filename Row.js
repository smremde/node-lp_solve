/* jslint node: true */
'use strict';

// class to hold factor:attribute pairs
function Row(clone) {
	this.raw = {};

	if (clone) {
		if (clone.raw) clone = clone.raw;
		for (var k in clone)
			this.raw[k] = clone[k];
	}
}

// adds a row or a variable:factor to this row
Row.prototype.Add = function(b, c) {
	var a = this.raw;
	if (c === undefined) {
		if (b.raw !== undefined) b = b.raw;
		for (var k in b) {
			a[k] = (a[k] || 0) + b[k];
		}
	} else {
		a[b] = (a[b] || 0) + c;
	}
	return this;
};

// subtract a row or variable:factor to this row
Row.prototype.Subtract = function(b, c) {
	var a = this.raw;
	if (c === undefined) {
		if (b.raw !== undefined) b = b.raw;
		for (var k in b) {
			a[k] = (a[k] || 0) - b[k];
		}
	} else {
		a[b] = (a[b] || 0) - c;
	}
	return this;
};

// multiplies all the factors by a fixed value
Row.prototype.Multiply = function(v) {
	var a = this.raw;
	if (v === 0) {
		this.raw = {};
	} else {
		for (var k in a) {
			a[k] = a[k] * v;
		}
	}

	return this;
};

// converts an object of vairable:factor to an equation for LP Solve
Row.prototype.ToText  = function() {
	var a = this.raw;
	var ret = "";
	for (var k in a) {
		var v = a[k];
		if (v === 0)
			continue;
		if (v < 0) {
			ret += " -";
			v = -v;
		} else {
			ret += " +";
		}
		if (k === 'constant') {
			ret += v;
		} else {
			ret += v + " " + k;
		}
	}
	return (ret === "") ? "0" : ret;
};


module.exports = Row;