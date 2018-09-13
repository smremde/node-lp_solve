const lp_solveFactory = require('bindings');
const Row = require('./Row.js');

const lp_solve = lp_solveFactory('lp_solve');

class LinearProgram {
  constructor() {
    this.Columns = { };
    this.lprec = new lp_solve.make_lp(0, 0);
    this.Constraints = [];
    this.ObjectiveFunc = new Row();
    this.decisionVariableCount = 0;
    this.modelNames = true;
    this.localConstraints = true;
    this.createModel = true;
  }

  setOutputFile(fname) {
    const str = typeof fname !== 'undefined' ? String(fname) : '';

    if (!this.lprec.set_outputfile(str)) {
      throw new Error(`error writing to file '${str}'`);
    }

    return this;
  }

  addColumn(name, isInteger, isBinary) {
    if (name === undefined) {
      name = `unamed_${id}`;
    }

    var id = this.Columns[name] = ++this.decisionVariableCount;

    if (this.createModel) {
      this.lprec.add_column(null);

      if (this.modelNames) {
        this.lprec.set_col_name(id, name);
      }

      if (isInteger === true) {
        this.lprec.set_int(id, true);
      }

      if (isBinary === true) {
        this.lprec.set_binary(id, true);
      }
    }

    return name;
  }

  addConstraint(row, constraint, constant, name) {
    const rowId = [];
    const rowValues = [];
    const raw = row.raw;

    for (const k in raw) {
      if (k !== 'constant') {
        rowValues.push(raw[k]);
        rowId.push(this.Columns[k]);
      } else {
        constant -= raw[k];
      }
    }

    const constrainttype = LinearProgram.ConstraintTypes[constraint];

    if (this.localConstraints) {
      this.Constraints.push({
        name, row: row.ToText(), constraint, constant
      });
    }

    if (this.createModel) {
      if (!this.lprec.add_constraintex(rowId.length, rowValues, rowId, constrainttype, constant)) return false;
      if (this.modelNames) {
        this.lprec.set_row_name(this.lprec.get_Nrows(), name || 'unamed row');
      }
      return true;
    }
  }

  setObjective(row, minimize) {
    const rowId = [];
    const rowValues = [];
    const raw = row.raw;

    for (const k in raw) {
      if (k !== 'constant') {
        rowValues.push(raw[k]);
        rowId.push(this.Columns[k]);
      } else {
        this.adjustObjective = raw[k];
      }
    }

    if (minimize === undefined) minimize = true;

    this.ObjectiveFunc = { minimize, row };

    return this.lprec.set_obj_fnex(rowValues.length, rowValues, rowId) &&
              ((minimize || false) ? this.lprec.set_minim() : this.lprec.set_maxim());
  }

  solve() {
    const res = this.lprec.solve();

    if (res === 0 || res == 1 || res == 9) { this.solutionVariables = this.getSolutionVariables(); }

    return { code: res, description: LinearProgram.SolveResult[res] };
  }

  // sets the amount of information to be reported by solve
  setVerbose(verb = 4) {
    const ret = { verbosity: verb };

    switch (verb) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6: this.lprec.set_verbose(verb);
        break;
      default: ret.errorMsg = 'Argument outside of allowed range {0, 1, 2, ..., 6}';
        break;
    }
    return ret;
  }

  solveAsync(callback) {
    const that = this;
    // semaphore.take(function() {
    that.lprec.solve_async((err, res) => {
      // semaphore.leave();
      if (res === 0 || res == 1 || res == 9) { that.solutionVariables = that.getSolutionVariables(); }

      callback({ code: res, description: LinearProgram.SolveResult[res] });
    });
    // });
  }

  getObjectiveValue() {
    return this.lprec.get_objective() + (this.adjustObjective || 0);
  }

  getSolutionVariables() {
    const ret = [];
    if (!this.lprec.get_variables(ret)) { return null; }
    return ret;
  }

  calculate(row) {
    let val = 0;
    const raw = row.raw;
    for (const k in raw) {
      val += this.get(k) * raw[k];
    }
    return val;
  }

  get(variable) {
    if (variable == 'constant') return 1;
    return this.solutionVariables ? this.solutionVariables[this.Columns[variable] - 1] : null;
  }

  dumpProgram() {
    let ret = `${this.ObjectiveFunc.minimize ? 'minimize' : 'maximize'}:${this.ObjectiveFunc.row.ToText()};\n`;
    for (const v in this.Constraints) {
      const c = this.Constraints[v];
      ret += `${(c.name ? (`${c.name}: `) : '') + c.row} ${LinearProgram.ConstraintText[c.constraint]} ${c.constant};\n`;
    }
    return ret;
  }
}

LinearProgram.ConstraintTypes = {
  LE: 1, EQ: 3, GE: 2, '<=': 1, '=': 3, '>=': 2
};
LinearProgram.ConstraintText = { LE: '<=', EQ: '=', GE: '>=' };

LinearProgram.SolveResult = {
  '-5': 'UNKNOWNERROR',
  '-4': 'DATAIGNORED',
  '-3': 'NOBFP',
  '-2': 'NOMEMORY',
  '-1': 'NOTRUN',
  0: 'OPTIMAL',
  1: 'SUBOPTIMAL',
  2: 'INFEASIBLE',
  3: 'UNBOUNDED',
  4: 'DEGENERATE',
  5: 'NUMFAILURE',
  6: 'USERABORT',
  7: 'TIMEOUT',
  8: 'RUNNING',
  9: 'PRESOLVED'
};

module.exports = LinearProgram;
