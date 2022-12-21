const Row = require('../Row.js');

const test = require('tap').test;
const lpsolve = require('../index.js');

test('lp', function (t) {
    t.plan(9);
    t.type(lpsolve, 'object');
  
    var Row = lpsolve.Row;
    t.type(Row, 'function');
  
    var lp = new lpsolve.LinearProgram();
    t.doesNotThrow(function () {lp.setOutputFile('');});
  
    t.type(lp, 'object');
  
    var x = lp.addColumn('x');
    var y = lp.addColumn('y');
  
    var objective = new Row().Add(x, 1).Add(y, 1);
  
    lp.setObjective(objective);
  
    var machineatime = new Row().Add(x, 50).Add(y, 24);
    lp.addConstraint(machineatime, 'LE', 2400, 'machine a time');
  
    var machinebtime = new Row().Add(x, 30).Add(y, 33);
    lp.addConstraint(machinebtime, 'LE', 2100, 'machine b time');
  
    lp.addConstraint(new Row().Add(x, 1), 'GE', 75 - 30, 'meet demand of x');
    lp.addConstraint(new Row().Add(y, 1), 'GE', 95 - 90, 'meet demand of y');
  
    lp.solve();
  
    t.equal(lp.getObjectiveValue(), 50);
    t.equal(lp.get(x), 45);
    t.equal(lp.get(y), 5);
    t.equal(lp.calculate(machineatime), 2370);
    t.equal(lp.calculate(machinebtime), 1515);
  });
  
  test('ilp', function (t) {
    t.plan(10);
    t.type(lpsolve, 'object');
  
    var Row = lpsolve.Row;
    t.type(Row, 'function');
  
    var lp2 = new lpsolve.LinearProgram();
  
    t.doesNotThrow(function () {lp2.setOutputFile('');});
  
    t.type(lp2, 'object');
  
    var x2 = lp2.addColumn('x', true);
    var y2 = lp2.addColumn('y', true);
  
    var objective2 = new Row().Add(x2, 1).Add(y2, 1);
  
    lp2.setObjective(objective2);
  
    var machineatime2 = new Row().Add(x2, 25).Add(y2, 12);
    lp2.addConstraint(machineatime2, 'LE', 2450, 'machine a time');
  
    var machinebtime2 = new Row().Add(x2, 15).Add(y2, 10);
    lp2.addConstraint(machinebtime2, 'LE', 2100, 'machine b time');
  
    lp2.addConstraint(new Row().Add(x2, 1), 'GE', 75 - 30, 'meet demand of x');
    lp2.addConstraint(new Row().Add(y2, 1), 'GE', 95 - 90, 'meet demand of y');
  
    lp2.solve();
  
    t.equal(lp2.getObjectiveValue(), 50);
    t.equal(lp2.get(x2), 45);
    t.equal(lp2.get(y2), 5);
    t.equal(lp2.calculate(machineatime2), 1185);
    t.equal(lp2.calculate(machinebtime2), 725);
    t.same(lp2.getSolutionVariables(), [45, 5]);
  
  });