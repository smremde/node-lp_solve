var test = require('tap').test,
  lpsolve = require('../index.js');

test('lp timeout', function (t) {
  t.plan(3);
  var lp = new lpsolve.LinearProgram();
  t.equals(lp.lprec.get_timeout(), 0);
  lp.lprec.set_timeout(1);
  t.equals(lp.lprec.get_timeout(), 1);
  lp.lprec.set_timeout(0);
  t.equals(lp.lprec.get_timeout(), 0);

});

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

  t.equals(lp.getObjectiveValue(), 50);
  t.equals(lp.get(x), 45);
  t.equals(lp.get(y), 5);
  t.equals(lp.calculate(machineatime), 2370);
  t.equals(lp.calculate(machinebtime), 1515);
});

test('ilp', function (t) {
  t.plan(9);
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

  t.equals(lp2.getObjectiveValue(), 50);
  t.equals(lp2.get(x2), 45);
  t.equals(lp2.get(y2), 5);
  t.equals(lp2.calculate(machineatime2), 1185);
  t.equals(lp2.calculate(machinebtime2), 725);

});

var lps = [];
var count = 110;
var batches = 99;

test('lp async', {timeout:10000000}, function (t) {

  t.plan(batches * count * 2);

  var Row = lpsolve.Row;

  var objective = new Row().Add('x', 1).Add('y', 1);
  var machineatime = new Row().Add('x', 50).Add('y', 24);
  var machinebtime = new Row().Add('x', 30).Add('y', 33);

  console.log('setup');

  for (var i=0; i<count * batches; i++) {
    var lp = new lpsolve.LinearProgram();
    lp.setOutputFile('');
    var x = lp.addColumn('x');
    var y = lp.addColumn('y');
    lp.setObjective(objective);
    lp.addConstraint(machineatime, 'LE', 2400, 'machine a time');
    lp.addConstraint(machinebtime, 'LE', 2100, 'machine b time');
    lp.addConstraint(new Row().Add(x, 1), 'GE', 75 - 30, 'meet demand of x');
    lp.addConstraint(new Row().Add(y, 1), 'GE', 95 - 90, 'meet demand of y');
    lps.push(lp);
  }

  console.log('execute');


  for (var batch=0; batch<batches; batch++) {
    (function(batch) {
      setTimeout(function() {
        for (var i=0; i<count; i++) {
          (function (lp) {

              //console.log(lp);
            lp.solveAsync(function (res) {
              //console.log(res);
              t.equals(res.code, 0);
              t.equals(lp.getObjectiveValue(), 50);
            });
          })(lps[i + batch * count]);
        }

      }, 0);
    })(batch);
  };

  console.log('done');

});

test('lp async solve', function (t) {
  t.plan(count * batches);
  for (var i=0; i<count * batches; i++) {
    t.ok(lps[i].solutionVariables);
  }
  t.end();
});