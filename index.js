const lp_solveFactory = require('bindings');
const Row = require('./Row.js');
const LinearProgram = require('./LinearProgram.js');

const lp_solve = lp_solveFactory('lp_solve');

module.exports = {
  Row,
  LinearProgram,
  lp_solve,
  version: lp_solve.lp_solve_version()
};
