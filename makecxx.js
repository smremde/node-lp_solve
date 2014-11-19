var c = require('change-case');
var _ = require('underscore');

var inp = [
"lprec * __WINAPI make_lp(int rows, int columns);",
"MYBOOL __WINAPI resize_lp(lprec *lp, int rows, int columns);",
"int __WINAPI get_status(lprec *lp);",
"char * __WINAPI get_statustext(lprec *lp, int statuscode);",
"MYBOOL __WINAPI is_obj_in_basis(lprec *lp);",
"void __WINAPI set_obj_in_basis(lprec *lp, MYBOOL obj_in_basis);",
"/* Create and initialise a lprec structure defaults */",
"lprec * __WINAPI copy_lp(lprec *lp);",
"MYBOOL __WINAPI dualize_lp(lprec *lp);",
"STATIC MYBOOL memopt_lp(lprec *lp, int rowextra, int colextra, int nzextra);",
"/* Copy or dualize the lp */",
"void __WINAPI delete_lp(lprec *lp);",
"void __WINAPI free_lp(lprec **plp);",
"/* Remove problem from memory */",
"MYBOOL __WINAPI set_lp_name(lprec *lp, char *lpname);",
"char * __WINAPI get_lp_name(lprec *lp);",
"/* Set and get the problem name */",
"MYBOOL __WINAPI has_BFP(lprec *lp);",
"MYBOOL __WINAPI is_nativeBFP(lprec *lp);",
"MYBOOL __WINAPI set_BFP(lprec *lp, char *filename);",
"/* Set basis factorization engine */",
"lprec * __WINAPI read_XLI(char *xliname, char *modelname, char *dataname, char *options, int verbose);",
"MYBOOL __WINAPI write_XLI(lprec *lp, char *filename, char *options, MYBOOL results);",
"MYBOOL __WINAPI has_XLI(lprec *lp);",
"MYBOOL __WINAPI is_nativeXLI(lprec *lp);",
"MYBOOL __WINAPI set_XLI(lprec *lp, char *filename);",
"/* Set external language interface */",
"MYBOOL __WINAPI set_obj(lprec *lp, int colnr, REAL value);",
"MYBOOL __WINAPI set_obj_fn(lprec *lp, REAL *row);",
"MYBOOL __WINAPI set_obj_fnex(lprec *lp, int count, REAL *row, int *colno);",
"/* set the objective function (Row 0) of the matrix */",
"MYBOOL __WINAPI str_set_obj_fn(lprec *lp, char *row_string);",
"/* The same, but with string input */",
"void __WINAPI set_sense(lprec *lp, MYBOOL maximize);",
"void __WINAPI set_maxim(lprec *lp);",
"void __WINAPI set_minim(lprec *lp);",
"MYBOOL __WINAPI is_maxim(lprec *lp);",
"/* Set optimization direction for the objective function */",
"MYBOOL __WINAPI add_constraint(lprec *lp, REAL *row, int constr_type, REAL rh);",
"MYBOOL __WINAPI add_constraintex(lprec *lp, int count, REAL *row, int *colno, int constr_type, REAL rh);",
"MYBOOL __WINAPI set_add_rowmode(lprec *lp, MYBOOL turnon);",
"MYBOOL __WINAPI is_add_rowmode(lprec *lp);",
"/* Add a constraint to the problem, row is the constraint row, rh is the right hand side,",
"constr_type is the type of constraint (LE (<=), GE(>=), EQ(=)) */",
"MYBOOL __WINAPI str_add_constraint(lprec *lp, char *row_string, int constr_type, REAL rh);",
"/* The same, but with string input */",
"MYBOOL __WINAPI set_row(lprec *lp, int rownr, REAL *row);",
"MYBOOL __WINAPI set_rowex(lprec *lp, int rownr, int count, REAL *row, int *colno);",
"MYBOOL __WINAPI get_row(lprec *lp, int rownr, REAL *row);",
"int __WINAPI get_rowex(lprec *lp, int rownr, REAL *row, int *colno);",
"/* Fill row with the row row_nr from the problem */",
"MYBOOL __WINAPI del_constraint(lprec *lp, int rownr);",
"STATIC MYBOOL del_constraintex(lprec *lp, LLrec *rowmap);",
"/* Remove constrain nr del_row from the problem */",
"MYBOOL __WINAPI add_lag_con(lprec *lp, REAL *row, int con_type, REAL rhs);",
"/* add a Lagrangian constraint of form Row' x contype Rhs */",
"MYBOOL __WINAPI str_add_lag_con(lprec *lp, char *row_string, int con_type, REAL rhs);",
"/* The same, but with string input */",
"void __WINAPI set_lag_trace(lprec *lp, MYBOOL lag_trace);",
"MYBOOL __WINAPI is_lag_trace(lprec *lp);",
"/* Set debugging/tracing mode of the Lagrangean solver */",
"MYBOOL __WINAPI set_constr_type(lprec *lp, int rownr, int con_type);",
"int __WINAPI get_constr_type(lprec *lp, int rownr);",
"REAL __WINAPI get_constr_value(lprec *lp, int rownr, int count, REAL *primsolution, int *nzindex);",
"MYBOOL __WINAPI is_constr_type(lprec *lp, int rownr, int mask);",
"STATIC char *get_str_constr_type(lprec *lp, int con_type);",
"STATIC int get_constr_class(lprec *lp, int rownr);",
"STATIC char *get_str_constr_class(lprec *lp, int con_class);",
"/* Set the type of constraint in row Row (LE, GE, EQ) */",
"MYBOOL __WINAPI set_rh(lprec *lp, int rownr, REAL value);",
"REAL __WINAPI get_rh(lprec *lp, int rownr);",
"/* Set and get the right hand side of a constraint row */",
"MYBOOL __WINAPI set_rh_range(lprec *lp, int rownr, REAL deltavalue);",
"REAL __WINAPI get_rh_range(lprec *lp, int rownr);",
"/* Set the RHS range; i.e. the lower and upper bounds of a constraint row */",
"void __WINAPI set_rh_vec(lprec *lp, REAL *rh);",
"/* Set the right hand side vector */",
"MYBOOL __WINAPI str_set_rh_vec(lprec *lp, char *rh_string);",
"/* The same, but with string input */",
"MYBOOL __WINAPI add_column(lprec *lp, REAL *column);",
"MYBOOL __WINAPI add_columnex(lprec *lp, int count, REAL *column, int *rowno);",
"MYBOOL __WINAPI str_add_column(lprec *lp, char *col_string);",
"/* Add a column to the problem */",
"MYBOOL __WINAPI set_column(lprec *lp, int colnr, REAL *column);",
"MYBOOL __WINAPI set_columnex(lprec *lp, int colnr, int count, REAL *column, int *rowno);",
"/* Overwrite existing column data */",
"int __WINAPI column_in_lp(lprec *lp, REAL *column);",
"/* Returns the column index if column is already present in lp, otherwise 0.",
"(Does not look at bounds and types, only looks at matrix values */",
	"int __WINAPI get_columnex(lprec *lp, int colnr, REAL *column, int *nzrow);",
	"MYBOOL __WINAPI get_column(lprec *lp, int colnr, REAL *column);",
	"/* Fill column with the column col_nr from the problem */",
	"MYBOOL __WINAPI del_column(lprec *lp, int colnr);",
	"STATIC MYBOOL del_columnex(lprec *lp, LLrec *colmap);",
	"/* Delete a column */",
	"MYBOOL __WINAPI set_mat(lprec *lp, int rownr, int colnr, REAL value);",
	"/* Fill in element (Row,Column) of the matrix",
	"Row in [0..Rows] and Column in [1..Columns] */",
	"REAL __WINAPI get_mat(lprec *lp, int rownr, int colnr);",
	"REAL __WINAPI get_mat_byindex(lprec *lp, int matindex, MYBOOL isrow, MYBOOL adjustsign);",
	"int __WINAPI get_nonzeros(lprec *lp);",
	"/* get a single element from the matrix */  /* Name changed from \"mat_elm\" by KE */",
	"void __WINAPI set_bounds_tighter(lprec *lp, MYBOOL tighten);",
	"MYBOOL get_bounds(lprec *lp, int column, REAL *lower, REAL *upper);",
	"MYBOOL __WINAPI get_bounds_tighter(lprec *lp);",
	"MYBOOL __WINAPI set_upbo(lprec *lp, int colnr, REAL value);",
	"REAL __WINAPI get_upbo(lprec *lp, int colnr);",
	"MYBOOL __WINAPI set_lowbo(lprec *lp, int colnr, REAL value);",
	"REAL __WINAPI get_lowbo(lprec *lp, int colnr);",
	"MYBOOL __WINAPI set_bounds(lprec *lp, int colnr, REAL lower, REAL upper);",
	"MYBOOL __WINAPI set_unbounded(lprec *lp, int colnr);",
	"MYBOOL __WINAPI is_unbounded(lprec *lp, int colnr);",
	"/* Set the upper and lower bounds of a variable */",
	"MYBOOL __WINAPI set_int(lprec *lp, int colnr, MYBOOL must_be_int);",
	"MYBOOL __WINAPI is_int(lprec *lp, int colnr);",
	"MYBOOL __WINAPI set_binary(lprec *lp, int colnr, MYBOOL must_be_bin);",
	"MYBOOL __WINAPI is_binary(lprec *lp, int colnr);",
	"MYBOOL __WINAPI set_semicont(lprec *lp, int colnr, MYBOOL must_be_sc);",
	"MYBOOL __WINAPI is_semicont(lprec *lp, int colnr);",
	"MYBOOL __WINAPI is_negative(lprec *lp, int colnr);",
	"MYBOOL __WINAPI set_var_weights(lprec *lp, REAL *weights);",
	"int __WINAPI get_var_priority(lprec *lp, int colnr);",
	"/* Set the type of variable */",
	"MYBOOL __WINAPI set_pseudocosts(lprec *lp, REAL *clower, REAL *cupper, int *updatelimit);",
	"MYBOOL __WINAPI get_pseudocosts(lprec *lp, REAL *clower, REAL *cupper, int *updatelimit);",
	"/* Set initial values for, or get computed pseudocost vectors;",
	"note that setting of pseudocosts can only happen in response to a",
	"call-back function optionally requesting this */",
	"int  __WINAPI add_SOS(lprec *lp, char *name, int sostype, int priority, int count, int *sosvars, REAL *weights);",
	"MYBOOL __WINAPI is_SOS_var(lprec *lp, int colnr);",
	"/* Add SOS constraints */",
	"MYBOOL __WINAPI set_row_name(lprec *lp, int rownr, char *new_name);",
	"char * __WINAPI get_row_name(lprec *lp, int rownr);",
	"char * __WINAPI get_origrow_name(lprec *lp, int rownr);",
	"/* Set/Get the name of a constraint row */   /* Get added by KE */",
	"MYBOOL __WINAPI set_col_name(lprec *lp, int colnr, char *new_name);",
	"char * __WINAPI get_col_name(lprec *lp, int colnr);",
	"char * __WINAPI get_origcol_name(lprec *lp, int colnr);",
	"/* Set/Get the name of a variable column */  /* Get added by KE */",
	"void __WINAPI unscale(lprec *lp);",
	"/* Undo previous scaling of the problem */",
	"void __WINAPI set_preferdual(lprec *lp, MYBOOL dodual);",
	"void __WINAPI set_simplextype(lprec *lp, int simplextype);",
	"int __WINAPI get_simplextype(lprec *lp);",
	"/* Set/Get if lp_solve should prefer the dual simplex over the primal -- added by KE */",
	"void __WINAPI default_basis(lprec *lp);",
	"void __WINAPI set_basiscrash(lprec *lp, int mode);",
	"int __WINAPI get_basiscrash(lprec *lp);",
	"int __WINAPI set_basisvar(lprec *lp, int basisPos, int enteringCol);",
	"MYBOOL __WINAPI set_basis(lprec *lp, int *bascolumn, MYBOOL nonbasic);",
	"MYBOOL __WINAPI get_basis(lprec *lp, int *bascolumn, MYBOOL nonbasic);",
	"void __WINAPI reset_basis(lprec *lp);",
	"/* Set/Get basis for a re-solved system */  /* Added by KE */",
	"MYBOOL __WINAPI guess_basis(lprec *lp, REAL *guessvector, int *basisvector);",
	"MYBOOL __WINAPI is_feasible(lprec *lp, REAL *values, REAL threshold);",
	"/* returns TRUE if the vector in values is a feasible solution to the lp */",
	"int __WINAPI solve(lprec *lp);",
	"/* Solve the problem */",
	"REAL __WINAPI time_elapsed(lprec *lp);",
	"/* Return the number of seconds since start of solution process */",
	"void __WINAPI put_bb_nodefunc(lprec *lp, lphandleint_intfunc newnode, void *bbnodehandle);",
	"void __WINAPI put_bb_branchfunc(lprec *lp, lphandleint_intfunc newbranch, void *bbbranchhandle);",
	"/* Allow the user to override B&B node and branching decisions */",
	"void __WINAPI put_abortfunc(lprec *lp, lphandle_intfunc newctrlc, void *ctrlchandle);",
	"/* Allow the user to define an interruption callback function */",
	"void __WINAPI put_logfunc(lprec *lp, lphandlestr_func newlog, void *loghandle);",
	"/* Allow the user to define a logging function */",
	"void __WINAPI put_msgfunc(lprec *lp, lphandleint_func newmsg, void *msghandle, int mask);",
	"/* Allow the user to define an event-driven message/reporting */",
	"MYBOOL __WINAPI get_primal_solution(lprec *lp, REAL *pv);",
	"MYBOOL __WINAPI get_ptr_primal_solution(lprec *lp, REAL **pv);",
	"MYBOOL __WINAPI get_dual_solution(lprec *lp, REAL *rc);",
	"MYBOOL __WINAPI get_ptr_dual_solution(lprec *lp, REAL **rc);",
	"MYBOOL __WINAPI get_lambda(lprec *lp, REAL *lambda);",
	"MYBOOL __WINAPI get_ptr_lambda(lprec *lp, REAL **lambda);",
	"/* Get the primal, dual/reduced costs and Lambda vectors */",
	"/* Read an MPS file */",
	"lprec * __WINAPI read_MPS(char *filename, int options);",
	"lprec * __WINAPI read_mps(FILE *filename, int options);",
	"lprec * __WINAPI read_freeMPS(char *filename, int options);",
	"lprec * __WINAPI read_freemps(FILE *filename, int options);",
	"/* Write a MPS file to output */",
	"MYBOOL __WINAPI write_mps(lprec *lp, char *filename);",
	"MYBOOL __WINAPI write_MPS(lprec *lp, FILE *output);",
	"MYBOOL __WINAPI write_freemps(lprec *lp, char *filename);",
	"MYBOOL __WINAPI write_freeMPS(lprec *lp, FILE *output);",
	"MYBOOL __WINAPI write_lp(lprec *lp, char *filename);",
	"MYBOOL __WINAPI write_LP(lprec *lp, FILE *output);",
	"/* Write a LP file to output */",
	"MYBOOL __WINAPI LP_readhandle(lprec **lp, FILE *filename, int verbose, char *lp_name);",
	"lprec * __WINAPI read_lp(FILE *filename, int verbose, char *lp_name);",
	"lprec * __WINAPI read_LP(char *filename, int verbose, char *lp_name);",
	"/* Old-style lp format file parser */",
	"MYBOOL __WINAPI write_basis(lprec *lp, char *filename);",
	"MYBOOL __WINAPI read_basis(lprec *lp, char *filename, char *info);",
	"/* Read and write basis from/to file in CPLEX BAS format */",
	"MYBOOL __WINAPI write_params(lprec *lp, char *filename, char *options);",
	"MYBOOL __WINAPI read_params(lprec *lp, char *filename, char *options);",
	"void __WINAPI reset_params(lprec *lp);",
	"/* Read and write parameter file */",
	"void __WINAPI print_lp(lprec *lp);",
	"void __WINAPI print_tableau(lprec *lp);",
	"/* Print the current problem, only useful in very small (test) problems */",
	"void __WINAPI print_objective(lprec *lp);",
	"void __WINAPI print_solution(lprec *lp, int columns);",
	"void __WINAPI print_constraints(lprec *lp, int columns);",
	"/* Print the solution to stdout */",
	"void __WINAPI print_duals(lprec *lp);",
	"/* Print the dual variables of the solution */",
	"void __WINAPI print_scales(lprec *lp);",
	"/* If scaling is used, print the scaling factors */",
	"void __WINAPI print_str(lprec *lp, char *str);",
	"void __WINAPI set_outputstream(lprec *lp, FILE *stream);",
	"MYBOOL __WINAPI set_outputfile(lprec *lp, char *filename);",
	"void __WINAPI set_verbose(lprec *lp, int verbose);",
	"int __WINAPI get_verbose(lprec *lp);",
	"void __WINAPI set_timeout(lprec *lp, long sectimeout);",
	"long __WINAPI get_timeout(lprec *lp);",
	"void __WINAPI set_print_sol(lprec *lp, int print_sol);",
	"int __WINAPI get_print_sol(lprec *lp);",
	"void __WINAPI set_debug(lprec *lp, MYBOOL debug);",
	"MYBOOL __WINAPI is_debug(lprec *lp);",
	"void __WINAPI set_trace(lprec *lp, MYBOOL trace);",
	"MYBOOL __WINAPI is_trace(lprec *lp);",
	"MYBOOL __WINAPI print_debugdump(lprec *lp, char *filename);",
	"void __WINAPI set_anti_degen(lprec *lp, int anti_degen);",
	"int __WINAPI get_anti_degen(lprec *lp);",
	"MYBOOL __WINAPI is_anti_degen(lprec *lp, int testmask);",
	"void __WINAPI set_presolve(lprec *lp, int presolvemode, int maxloops);",
	"int __WINAPI get_presolve(lprec *lp);",
	"int __WINAPI get_presolveloops(lprec *lp);",
	"MYBOOL __WINAPI is_presolve(lprec *lp, int testmask);",
	"int __WINAPI get_orig_index(lprec *lp, int lp_index);",
	"int __WINAPI get_lp_index(lprec *lp, int orig_index);",
	"void __WINAPI set_maxpivot(lprec *lp, int max_num_inv);",
	"int __WINAPI get_maxpivot(lprec *lp);",
	"void __WINAPI set_obj_bound(lprec *lp, REAL obj_bound);",
	"REAL __WINAPI get_obj_bound(lprec *lp);",
	"void __WINAPI set_mip_gap(lprec *lp, MYBOOL absolute, REAL mip_gap);",
	"REAL __WINAPI get_mip_gap(lprec *lp, MYBOOL absolute);",
	"void __WINAPI set_bb_rule(lprec *lp, int bb_rule);",
	"int __WINAPI get_bb_rule(lprec *lp);",
	"MYBOOL __WINAPI set_var_branch(lprec *lp, int colnr, int branch_mode);",
	"int __WINAPI get_var_branch(lprec *lp, int colnr);",
	"MYBOOL __WINAPI is_infinite(lprec *lp, REAL value);",
	"void __WINAPI set_infinite(lprec *lp, REAL infinite);",
	"REAL __WINAPI get_infinite(lprec *lp);",
	"void __WINAPI set_epsint(lprec *lp, REAL epsint);",
	"REAL __WINAPI get_epsint(lprec *lp);",
	"void __WINAPI set_epsb(lprec *lp, REAL epsb);",
	"REAL __WINAPI get_epsb(lprec *lp);",
	"void __WINAPI set_epsd(lprec *lp, REAL epsd);",
	"REAL __WINAPI get_epsd(lprec *lp);",
	"void __WINAPI set_epsel(lprec *lp, REAL epsel);",
	"REAL __WINAPI get_epsel(lprec *lp);",
	"MYBOOL __WINAPI set_epslevel(lprec *lp, int epslevel);",
	"void __WINAPI set_scaling(lprec *lp, int scalemode);",
	"int __WINAPI get_scaling(lprec *lp);",
	"MYBOOL __WINAPI is_scalemode(lprec *lp, int testmask);",
	"MYBOOL __WINAPI is_scaletype(lprec *lp, int scaletype);",
	"MYBOOL __WINAPI is_integerscaling(lprec *lp);",
	"void __WINAPI set_scalelimit(lprec *lp, REAL scalelimit);",
	"REAL __WINAPI get_scalelimit(lprec *lp);",
	"void __WINAPI set_improve(lprec *lp, int improve);",
	"int __WINAPI get_improve(lprec *lp);",
	"void __WINAPI set_pivoting(lprec *lp, int piv_rule);",
	"int __WINAPI get_pivoting(lprec *lp);",
	"MYBOOL __WINAPI set_partialprice(lprec *lp, int blockcount, int *blockstart, MYBOOL isrow);",
	"void __WINAPI get_partialprice(lprec *lp, int *blockcount, int *blockstart, MYBOOL isrow);",
	"MYBOOL __WINAPI set_multiprice(lprec *lp, int multiblockdiv);",
	"int __WINAPI get_multiprice(lprec *lp, MYBOOL getabssize);",
	"MYBOOL __WINAPI is_use_names(lprec *lp, MYBOOL isrow);",
	"void __WINAPI set_use_names(lprec *lp, MYBOOL isrow, MYBOOL use_names);",
	"int __WINAPI get_nameindex(lprec *lp, char *varname, MYBOOL isrow);",
	"MYBOOL __WINAPI is_piv_mode(lprec *lp, int testmask);",
	"MYBOOL __WINAPI is_piv_rule(lprec *lp, int rule);",
	"void __WINAPI set_break_at_first(lprec *lp, MYBOOL break_at_first);",
	"MYBOOL __WINAPI is_break_at_first(lprec *lp);",
	"void __WINAPI set_bb_floorfirst(lprec *lp, int bb_floorfirst);",
	"int __WINAPI get_bb_floorfirst(lprec *lp);",
	"void __WINAPI set_bb_depthlimit(lprec *lp, int bb_maxlevel);",
	"int __WINAPI get_bb_depthlimit(lprec *lp);",
	"void __WINAPI set_break_at_value(lprec *lp, REAL break_at_value);",
	"REAL __WINAPI get_break_at_value(lprec *lp);",
	"void __WINAPI set_negrange(lprec *lp, REAL negrange);",
	"REAL __WINAPI get_negrange(lprec *lp);",
	"void __WINAPI set_epsperturb(lprec *lp, REAL epsperturb);",
	"REAL __WINAPI get_epsperturb(lprec *lp);",
	"void __WINAPI set_epspivot(lprec *lp, REAL epspivot);",
	"REAL __WINAPI get_epspivot(lprec *lp);",
	"int __WINAPI get_max_level(lprec *lp);",
	"COUNTER __WINAPI get_total_nodes(lprec *lp);",
	"COUNTER __WINAPI get_total_iter(lprec *lp);",
	"REAL __WINAPI get_objective(lprec *lp);",
	"REAL __WINAPI get_working_objective(lprec *lp);",
	"REAL __WINAPI get_var_primalresult(lprec *lp, int index);",
	"REAL __WINAPI get_var_dualresult(lprec *lp, int index);",
	"MYBOOL __WINAPI get_variables(lprec *lp, REAL *var);",
	"MYBOOL __WINAPI get_ptr_variables(lprec *lp, REAL **var);",
	"MYBOOL __WINAPI get_constraints(lprec *lp, REAL *constr);",
	"MYBOOL __WINAPI get_ptr_constraints(lprec *lp, REAL **constr);",
	"MYBOOL __WINAPI get_sensitivity_rhs(lprec *lp, REAL *duals, REAL *dualsfrom, REAL *dualstill);",
	"MYBOOL __WINAPI get_ptr_sensitivity_rhs(lprec *lp, REAL **duals, REAL **dualsfrom, REAL **dualstill);",
	"MYBOOL __WINAPI get_sensitivity_obj(lprec *lp, REAL *objfrom, REAL *objtill);",
	"MYBOOL __WINAPI get_sensitivity_objex(lprec *lp, REAL *objfrom, REAL *objtill, REAL *objfromvalue, REAL *objtillvalue);",
	"MYBOOL __WINAPI get_ptr_sensitivity_obj(lprec *lp, REAL **objfrom, REAL **objtill);",
	"MYBOOL __WINAPI get_ptr_sensitivity_objex(lprec *lp, REAL **objfrom, REAL **objtill, REAL **objfromvalue, REAL **objtillvalue);",
	"void __WINAPI set_solutionlimit(lprec *lp, int limit);",
	"int __WINAPI get_solutionlimit(lprec *lp);",
	"int __WINAPI get_solutioncount(lprec *lp);",
	"int __WINAPI get_Norig_rows(lprec *lp);",
	"int __WINAPI get_Nrows(lprec *lp);",
	"int __WINAPI get_Lrows(lprec *lp);",
	"int __WINAPI get_Norig_columns(lprec *lp);",
	"int __WINAPI get_Ncolumns(lprec *lp);",
	"typedef int (__WINAPI read_modeldata_func)(void *userhandle, char *buf, int max_size);",
	"typedef int (__WINAPI write_modeldata_func)(void *userhandle, char *buf);",
	"MYBOOL __WINAPI MPS_readex(lprec **newlp, void *userhandle, read_modeldata_func read_modeldata, int typeMPS, int options);",
	"/* #if defined develop */",
	"lprec * __WINAPI read_lpex(void *userhandle, read_modeldata_func read_modeldata, int verbose, char *lp_name);",
	"MYBOOL __WINAPI write_lpex(lprec *lp, void *userhandle, write_modeldata_func write_modeldata);",
	"lprec * __WINAPI read_mpsex(void *userhandle, read_modeldata_func read_modeldata, int options);",
	"lprec * __WINAPI read_freempsex(void *userhandle, read_modeldata_func read_modeldata, int options);",
	"MYBOOL __WINAPI MPS_writefileex(lprec *lp, int typeMPS, void *userhandle, write_modeldata_func write_modeldata);"];




	var typemap = {
		"MYBOOL": {
			c: "MYBOOL",
			v8name: "Boolean",
			assert: "#->IsBoolean()",
			ret: "NanReturnValue(Boolean::New(ret == 1));",
			fromv8: "MYBOOL #name# = (MYBOOL)(#arg#->BooleanValue());"
		},
		"int": {
			v8name: "Number",
			c: "int",
			assert: "#->IsNumber()",
			ret: "NanReturnValue(Number::New(ret));",
			fromv8: "int #name# = (int)(#arg#->Int32Value());"
		},
		"void": {
		},
		"REAL": {
			v8name: "Number",
			c: "REAL",
			assert: "#->IsNumber()",
			ret: "NanReturnValue(Number::New(ret));"  ,
			fromv8: "REAL #name# = (REAL)(#arg#->NumberValue());"
		},
		"REAL *": {
			v8name: "Array of Numbers or NULL",
			c: "REAL *",
			assert: "#->IsArray() || #->IsNull()",
			fromv8: "REAL* #name#;\n\
	if (#arg#->IsArray()) { \n\
		Handle<Array> #name#_handle = Handle<Array>::Cast(#arg#); \n\
		int #name#_n = #name#_handle->Length(); \n\
		#name# = new REAL[#name#_n]; \n\
		for (int i = 0; i < #name#_n; i++) \n\
			#name#[i] = #name#_handle->Get(i)->NumberValue();\n\
	}",
			fromv8cleanup: "if (#arg#->IsArray()) { \n\
	delete #name#;\n\
}"
		},
	"int *": {
			v8name: "Array of Numbers or NULL",
			c: "REAL *",
			assert: "#->IsArray() || #->IsNull()",
			fromv8: "int* #name#; \n \
	if (#arg#->IsArray()) { \n\
		Handle<Array> #name#_handle = Handle<Array>::Cast(#arg#); \n\
		int #name#_n = #name#_handle->Length(); \n\
		#name# = new int[#name#_n]; \n\
		for (int i = 0; i < #name#_n; i++) \n\
			#name#[i] = #name#_handle->Get(i)->Int32Value();\n\
	}",
			fromv8cleanup: "if (#arg#->IsArray()) { \n\
	delete #name#;\n\
}"
		},
		"FILE *": {
			v8name: "String",
			assert: "#->IsString()" ,
			c: "FILE *",
			fromv8: "String::Utf8Value str_#name#(#arg#);\nFILE *#name# = fopen(*str_#name#);",
			fromv8cleanup: "fclose(#name#);"
		},
		"char *": {
			v8name: "String",
			c: "char *",
			assert: "#->IsString()",
			ret: "NanReturnValue(String::New(ret));" ,
			fromv8: "String::Utf8Value str_#name#(#arg#);\nchar* #name# = *str_#name#;"
		},
		"lprec *": {
			c: "lprec *",
			ret: "Local<Object> instance = constructor->NewInstance();\n\
LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);\n\
retobj->lp = ret;\n\
NanReturnValue(instance);" ,
		}


	};

//#define a_string(a) assert(a->IsString());
//#define a_real(a) assert(a->IsNumber());
//#define a_int(a) assert(a->IsNumber());
//#define a_bool(a) assert(a->IsBoolean());

//NAN_METHOD(LinearProgram::AddColumn) {
	//NanScope();
//
//
//
	//LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
//
	//String::Utf8Value str(args[0]); char* col_string = *str;
//
//	int i = (int)args[1]->Int32Value();
//
	//add_column(obj->lp, NULL);
	//set_col_name(obj->lp, i, col_string);
//
	//NanReturnUndefined();
//}

var paramFirendly = [ "First", "Second", "Third", "Fourth", "Fifth", "Sixth"];
var classmethods = [];
var staticmethods = [];

var initmodule = [];
var initclass = [];

var func = /([a-zA-Z_]*( \*)?) __WINAPI ([a-zA-Z_]*)\((.*)\);/

function validType(a) {return  typemap[a[0]] !== undefined;}

_.each(inp, function (line) {
	if (line[0] == "/") return line;


	var j = func.exec(line);

	if (j== null) return;

	var oldfuncname = 	j[3];
	var newfuncname = 	c.camel(oldfuncname);

	var rettype = j[1];

	var funcargs = _.map(j[4].split(", "), function (a) {
		var z =  a.split(" ");
		if (z[1][0] == '*')
		{
			z[1] = z[1].substring(1);
			z[0] = z[0] + " *";
		}
		if (z[1][0] == '*')
		{
			z[1] = z[1].substring(1);
			z[0] = z[0] + "*";
		}
		return z;
	});

	var output = [];

	var cantdo = (!_.all(funcargs, validType));
	if (cantdo){
		output.push("/*");
		output.push(oldfuncname);
		output.push(funcargs);
		output.push("*/");
		output.push("/*");
	}

	var thiscall = funcargs.length >= 1 && funcargs[0][0] == "lprec *";


	if (thiscall) {
		classmethods.push ((cantdo ? "// "  : "" )+"static NAN_METHOD("+ oldfuncname + ");");
		initclass.push((cantdo ? "// "  : "" )+"NODE_SET_PROTOTYPE_METHOD(tpl, \"" + oldfuncname + "\", LinearProgram::" + oldfuncname + ");")

		output.push("NAN_METHOD(LinearProgram::"+ oldfuncname + ") {");
		funcargs.splice(0, 1);
	}
	else {
		staticmethods.push ((cantdo ? "// "  : "" )+"NAN_METHOD("+ oldfuncname + ");")
		initmodule.push((cantdo ? "// "  : "" )+"exports->Set(NanNew<String>(\"" + oldfuncname + "\"), NanNew<FunctionTemplate>("+ oldfuncname +")->GetFunction());");

		output.push("NAN_METHOD("+ oldfuncname + ") {");
	}


	output.push("NanScope();")
	// param check

	output.push("if (args.Length() != " + (funcargs.length) + ") return NanThrowError(\"Invalid number of arguments\");")

	for (var i=0; i<funcargs.length ; i++) {
		var arg = funcargs[i];
		var ty = typemap[arg[0]];
		if (ty && ty.assert) {
			output.push("if (!(" + ty.assert.replace(/#/g, "args[" + i + "]") + ")) return NanThrowTypeError(\"" +paramFirendly[i] + " argument should be a " + ty.v8name +"\"); ");
		}
	}
	for (var i=0; i<funcargs.length ; i++) {
		var arg = funcargs[i];
		var ty = typemap[arg[0]];
		if (ty && ty.fromv8) {
			output.push(ty.fromv8.replace(/#name#/g, arg[1]).replace(/#arg#/g, "args["+ i + "]"));
		}
	}


	// call

	var params = funcargs.map(function(a) { return a[1]; });
	if (thiscall) {
		output.push("LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());");
		params.splice(0, 0,"obj->lp");
	}
	params = params.join(", ");
	if (typemap[rettype] && typemap[rettype].ret) {
		output.push(typemap[rettype].c + " ret = ::"  + oldfuncname + "(" + params + ");");
	}
	else {
		output.push("::" + oldfuncname + "(" + params + ");");
	}

	for (var i=0; i<funcargs.length ; i++) {
		var arg = funcargs[i];
		var ty = typemap[arg[0]];
		if (ty && ty.fromv8cleanup) {
			output.push(ty.fromv8cleanup.replace(/#name#/g, arg[1]).replace(/#arg#/g, "args["+ i + "]"));
		}
	}
	if (typemap[rettype] && typemap[rettype].ret) {
		output.push(typemap[rettype].ret);
	}
	else {
		output.push("NanReturnUndefined();");
	}

	output.push ("}");
	if (cantdo){
		output.push("*/");
	}
	console.log(output.join("\n"));
});

console.log(staticmethods.join("\n"));
console.log();
console.log(classmethods.join("\n"));
console.log();
console.log(initmodule.join("\n"));
console.log();
console.log(initclass.join("\n"));
console.log();

