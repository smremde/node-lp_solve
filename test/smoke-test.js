const test = require('tap').test;
const lpSolve = require('../index.js');

test('native addon smoke test', (t) => {
  t.plan(5);

  const lp = new lpSolve.LinearProgram();
  const x = lp.addColumn('x');
  const y = lp.addColumn('y');

  const objective = new lpSolve.Row().Add(x, 1).Add(y, 1);
  lp.setObjective(objective);

  lp.addConstraint(new lpSolve.Row().Add(x, 50).Add(y, 24), 'LE', 2400, 'machine a time');
  lp.addConstraint(new lpSolve.Row().Add(x, 30).Add(y, 33), 'LE', 2100, 'machine b time');
  lp.addConstraint(new lpSolve.Row().Add(x, 1), 'GE', 45, 'meet demand of x');
  lp.addConstraint(new lpSolve.Row().Add(y, 1), 'GE', 5, 'meet demand of y');

  const result = lp.solve();

  t.equal(result.code, 0, `solve should be optimal, got ${result.description}`);
  t.equal(result.description, 'OPTIMAL');
  t.equal(lp.getObjectiveValue(), 50);
  t.equal(lp.get(x), 45);
  t.equal(lp.get(y), 5);
});
