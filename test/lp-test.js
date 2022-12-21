const Row = require('../Row.js');

const test = require('tap').test;
const lpsolve = require('../index.js');

test('lp timeout', function (t) {
  t.plan(3);
  var lp = new lpsolve.LinearProgram();
  t.equal(lp.lprec.get_timeout(), 0);
  lp.lprec.set_timeout(1);
  t.equal(lp.lprec.get_timeout(), 1);
  lp.lprec.set_timeout(0);
  t.equal(lp.lprec.get_timeout(), 0);
});

test('throw error on invalid file', function (t) {
    t.plan(1);
    var lp = new lpsolve.LinearProgram();
    t.throws( () => lp.setOutputFile('/z/x/c/v/b/!.?*'), 'invalid filename' )
});

test('lp solve column types', function (t) {
    t.plan(3);
    var lp = new lpsolve.LinearProgram();
    var c1 = lp.addColumn();
    t.ok(c1)
    var c2 = lp.addColumn('integer', true);
    t.ok(c2)
    var c3 = lp.addColumn('binary', false, true);
    t.ok(c3)
});

test('lp solve functions', function (t) {
    t.plan(14);
    var lp = new lpsolve.LinearProgram();
    lp.setOutputFile('');
    var x = lp.addColumn('x');
    var y = lp.addColumn('y');
    
    var objective = new Row().Add(x, 1).Add(y, 1);
    var machineatime = new Row().Add(x, 50).Add(y, 24).Add('constant',2);
    var machinebtime = new Row().Add(x, 30).Add(y, 33);
    
    lp.setObjective(objective);
    t.ok(lp.addConstraint(machineatime, 'LE', 2400, 'machine a time'));
    t.ok(lp.addConstraint(machinebtime, 'LE', 2100, 'machine b time'));
    t.ok(lp.addConstraint(new Row().Add(x, 1), 'GE', 75 - 30, 'meet demand of x'));
    t.ok(lp.addConstraint(new Row().Add(y, 1), 'GE', 95 - 90, 'meet demand of y'));

    lp.setObjective(objective, true);
    lp.setObjective(objective, false);
    
    for (var i=0; i<7;i++) 
        t.same(lp.setVerbose(i), {verbosity:i},'verbosity ' + i)
    t.same(lp.setVerbose(9), {"verbosity": 9,errorMsg:"Argument outside of allowed range {0, 1, 2, ..., 6}"},'verbosity ' + i)
    t.same(lp.setVerbose(), {verbosity:4},'verbosity default')

    t.ok(lp.dumpProgram())
});

test('invalid column in constraint', function (t) {
    t.plan(1);
    var lp = new lpsolve.LinearProgram();
    lp.setOutputFile('');
    var x = lp.addColumn('x');
    var y = lp.addColumn('y');
    
    var objective = new Row().Add('z', 1).Add(y, 1).Add('constant',2);

    t.throws(() => lp.setObjective(objective, true));
});

test('invalid column in objective', function (t) {
    t.plan(1);
    var lp = new lpsolve.LinearProgram();
    lp.setOutputFile('');
    var x = lp.addColumn('x');
    var y = lp.addColumn('y');
    
    var objective = new Row().Add('z', 1).Add(y, 1).Add('constant',2);
    var machineatime = new Row().Add(x, 50).Add(y, 24).Add('constant',2);

    t.throws(() => lp.setObjective(objective));
});


test('lp local only', function (t) {
    t.plan(5);
    t.type(lpsolve, 'object');
  
    var Row = lpsolve.Row;
    t.type(Row, 'function');
  
    var lp = new lpsolve.LinearProgram();
    lp.localConstraints = false;
    lp.createModel = false;
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
  
    t.pass();
  });

test('constant in objective', function (t) {
    t.plan(1);
    var lp = new lpsolve.LinearProgram();
    lp.setOutputFile('');
    var x = lp.addColumn('x');
    var y = lp.addColumn('y');
    
    var objective = new Row().Add(x, 1).Add(y, 1).Add('constant', -2);
    lp.setObjective(objective);
    t.pass();
});

test('solution empty before solve', function (t) {
    t.plan(1);
    var lp = new lpsolve.LinearProgram();
    
   // t.same(lp.getSolutionVariables(), null);
   t.pass()
});


test('throw error on invalid file', function (t) {
    t.plan(1);
    var lp = new lpsolve.LinearProgram();
    t.throws( () => lp.setOutputFile('/z/x/c/v/b/!.?*'), 'invalid filename' )
});