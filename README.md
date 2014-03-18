node-lp_solve
============

A NodeJS module for createing and solving simple Linear Programs using lp_solve.

Example:

```javascript

// solve http://people.brunel.ac.uk/~mastjjb/jeb/or/morelp.html

var lpsolve = require('lp_solve');
var Row = lpsolve.Row;

var lp = new lpsolve.LinearProgram();

var x = lp.addColumn('x'); // lp.addColumn('x', true) for integer variable
var y = lp.addColumn('y'); // lp.addColumn('y', false, true) for binary variable


var objective = new Row().Add(x, 1).Add(y, 1);

lp.setObjective(objective);

var machineatime = new Row().Add(x, 50).Add(y, 24);
lp.addConstraint(machineatime, 'LE', 2400, 'machine a time')

var machinebtime = new Row().Add(x, 30).Add(y, 33);
lp.addConstraint(machinebtime, 'LE', 2100, 'machine b time')

lp.addConstraint(new Row().Add(x, 1), 'GE', 75 - 30, 'meet demand of x')
lp.addConstraint(new Row().Add(y, 1), 'GE', 95 - 90, 'meet demand of y')

console.log(lp.dumpProgram());
console.log(lp.solve());
console.log('objective =', lp.getObjectiveValue())
console.log('x =', lp.get(x));
console.log('y =', lp.get(y));
console.log('machineatime =', lp.calculate(machineatime));
console.log('machinebtime =', lp.calculate(machinebtime));

```

Output

```
minimize: +1 x +1 y
subject to
machine a time:  +50 x +24 y <= 2400
machine b time:  +30 x +33 y <= 2100
meet demand of x:  +1 x >= 45
meet demand of y:  +1 y >= 5

Model name:  '' - run #1
Objective:   Minimize(R0)

SUBMITTED
Model size:        4 constraints,       2 variables,            6 non-zeros.
Sets:                                   0 GUB,                  0 SOS.

Using DUAL simplex for phase 1 and PRIMAL simplex for phase 2.
The primal and dual simplex pricing strategy set to 'Devex'.


Optimal solution                  50 after          2 iter.

Excellent numeric accuracy ||*|| = 0

 MEMO: lp_solve version 5.5.2.0 for 64 bit OS, with 64 bit REAL variables.
      In the total iteration count 2, 0 (0.0%) were bound flips.
      There were 0 refactorizations, 0 triggered by time and 0 by density.
       ... on average 2.0 major pivots per refactorization.
      The largest [LUSOL v2.2.1.0] fact(B) had 5 NZ entries, 1.0x largest basis.
      The constraint matrix inf-norm is 50, with a dynamic range of 50.
      Time to load data was 0.001 seconds, presolve used 0.004 seconds,
       ... 0.003 seconds in simplex solver, in total 0.008 seconds.

{ code: 0, description: 'OPTIMAL' }
objective = 50
x = 45
y = 5
machineatime = 2370
machinebtime = 1515
```
