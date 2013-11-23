const test = require('tap').test,
  lpsolve = require('../');

test('lp', function (t) {
  t.plan(16);
  t.type(lpsolve, 'object');

  var Row = lpsolve.Row;
  t.type(Row, 'function');

  var lp = new lpsolve.LinearProgram();
  var lp2 = new lpsolve.LinearProgram();
  t.doesNotThrow(function () {lp.setOutputFile('');});
  t.doesNotThrow(function () {lp2.setOutputFile('');});

  t.type(lp, 'object');
  t.type(lp2, 'object');

  var x = lp.addColumn('x');
  var y = lp.addColumn('y');
  var x2 = lp2.addColumn('x', true);
  var y2 = lp2.addColumn('y', true);

  var objective = new Row().Add(x, 1).Add(y, 1);
  var objective2 = new Row().Add(x2, 1).Add(y2, 1);

  lp.setObjective(objective);
  lp2.setObjective(objective2);

  var machineatime = new Row().Add(x, 50).Add(y, 24);
  var machineatime2 = new Row().Add(x2, 50).Add(y2, 24);
  lp.addConstraint(machineatime, 'LE', 2400, 'machine a time');
  lp2.addConstraint(machineatime2, 'LE', 2400, 'machine a time');

  var machinebtime = new Row().Add(x, 30).Add(y, 33);
  var machinebtime2 = new Row().Add(x2, 30).Add(y2, 33);
  lp.addConstraint(machinebtime, 'LE', 2100, 'machine b time');
  lp2.addConstraint(machinebtime2, 'LE', 2100, 'machine b time');

  lp.addConstraint(new Row().Add(x, 1), 'GE', 75 - 30, 'meet demand of x');
  lp.addConstraint(new Row().Add(y, 1), 'GE', 95 - 90, 'meet demand of y');
  lp2.addConstraint(new Row().Add(x2, 1), 'GE', 75 - 30, 'meet demand of x');
  lp2.addConstraint(new Row().Add(y2, 1), 'GE', 95 - 90, 'meet demand of y');

  lp.solve();
  lp2.solve();

  t.equals(lp.getObjectiveValue(), 50);
  t.equals(lp.get(x), 45);
  t.equals(lp.get(y), 5);
  t.equals(lp.calculate(machineatime), 2370);
  t.equals(lp.calculate(machinebtime), 1515);

  t.equals(lp2.getObjectiveValue(), 50);
  t.equals(lp2.get(x2), 45);
  t.equals(lp2.get(y2), 5);
  t.equals(lp2.calculate(machineatime2), 2370);
  t.equals(lp2.calculate(machinebtime2), 1515);
});
