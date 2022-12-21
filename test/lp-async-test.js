const Row = require('../Row.js');

const test = require('tap').test;
const lpsolve = require('../index.js');

var lps = [];
var count = 10;
var batches = 10;

test('lp async', { timeout: 10000000 }, function (t) {
    t.plan(batches * count * 2);

    var Row = lpsolve.Row;

    var objective = new Row().Add('x', 1).Add('y', 1);
    var machineatime = new Row().Add('x', 50).Add('y', 24);
    var machinebtime = new Row().Add('x', 30).Add('y', 33);

    for (var i = 0; i < count * batches; i++) {
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

    for (let batch = 0; batch < batches; batch++) {
        setTimeout(function () {
            for (let i = 0; i < count; i++) {
                let lp = lps[i + batch * count]
                lp.solveAsync(function (res) {
                    t.equal(res.code, 0);
                    t.equal(lp.getObjectiveValue(), 50);
                });
            }
        }, 0);
    };
});

test('lp async solve', function (t) {
    t.plan(count * batches);
    for (let i = 0; i < count * batches; i++) {
        t.ok(lps[i].solutionVariables);
    }
    t.end();
});
