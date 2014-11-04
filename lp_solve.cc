#include <node.h>
#include "nan.h"

#include "lp_solve.h"
#include "lp_lib.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
	exports->Set(NanNew<String>("lp_solve_version"), NanNew<FunctionTemplate>(getVersion)->GetFunction());
	exports->Set(NanNew<String>("make_lp"), NanNew<FunctionTemplate>(make_lp)->GetFunction());
	// exports->Set(NanNew<String>("free_lp"), NanNew<FunctionTemplate>(free_lp)->GetFunction());
	exports->Set(NanNew<String>("read_XLI"), NanNew<FunctionTemplate>(read_XLI)->GetFunction());
	exports->Set(NanNew<String>("read_MPS"), NanNew<FunctionTemplate>(read_MPS)->GetFunction());
	exports->Set(NanNew<String>("read_mps"), NanNew<FunctionTemplate>(read_mps)->GetFunction());
	exports->Set(NanNew<String>("read_freeMPS"), NanNew<FunctionTemplate>(read_freeMPS)->GetFunction());
	exports->Set(NanNew<String>("read_freemps"), NanNew<FunctionTemplate>(read_freemps)->GetFunction());
	exports->Set(NanNew<String>("read_lp"), NanNew<FunctionTemplate>(read_lp)->GetFunction());
	exports->Set(NanNew<String>("read_LP"), NanNew<FunctionTemplate>(read_LP)->GetFunction());
	// exports->Set(NanNew<String>("read_lpex"), NanNew<FunctionTemplate>(read_lpex)->GetFunction());
	// exports->Set(NanNew<String>("read_mpsex"), NanNew<FunctionTemplate>(read_mpsex)->GetFunction());
	// exports->Set(NanNew<String>("read_freempsex"), NanNew<FunctionTemplate>(read_freempsex)->GetFunction());
	LinearProgram::Init(exports);
}

NODE_MODULE(lp_solve, InitAll);


NAN_METHOD(getVersion) {
	NanScope();

	int majorversion, minorversion, release, build;

	lp_solve_version(&majorversion, &minorversion, &release, &build);

	Handle<Object> ret = Object::New();

	ret->Set(NanNew<String>("majorversion"), NanNew<Number>(majorversion));
	ret->Set(NanNew<String>("minorversion"), NanNew<Number>(minorversion));
	ret->Set(NanNew<String>("release"), NanNew<Number>(release));
	ret->Set(NanNew<String>("build"), NanNew<Number>(build));

	NanReturnValue(ret);
};

void LinearProgram::Init(Handle<Object> exports) {
	Local<FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(LinearProgram::New);
	tpl->SetClassName(NanNew<String>("lprec"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(tpl, "solve_async", LinearProgram::solve_async);

	NODE_SET_PROTOTYPE_METHOD(tpl, "resize_lp", LinearProgram::resize_lp);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_status", LinearProgram::get_status);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_statustext", LinearProgram::get_statustext);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_obj_in_basis", LinearProgram::is_obj_in_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_obj_in_basis", LinearProgram::set_obj_in_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "copy_lp", LinearProgram::copy_lp);
	NODE_SET_PROTOTYPE_METHOD(tpl, "dualize_lp", LinearProgram::dualize_lp);
	NODE_SET_PROTOTYPE_METHOD(tpl, "delete_lp", LinearProgram::delete_lp);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_lp_name", LinearProgram::set_lp_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_lp_name", LinearProgram::get_lp_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "has_BFP", LinearProgram::has_BFP);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_nativeBFP", LinearProgram::is_nativeBFP);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_BFP", LinearProgram::set_BFP);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_XLI", LinearProgram::write_XLI);
	NODE_SET_PROTOTYPE_METHOD(tpl, "has_XLI", LinearProgram::has_XLI);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_nativeXLI", LinearProgram::is_nativeXLI);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_XLI", LinearProgram::set_XLI);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_obj", LinearProgram::set_obj);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_obj_fn", LinearProgram::set_obj_fn);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_obj_fnex", LinearProgram::set_obj_fnex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "str_set_obj_fn", LinearProgram::str_set_obj_fn);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_sense", LinearProgram::set_sense);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_maxim", LinearProgram::set_maxim);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_minim", LinearProgram::set_minim);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_maxim", LinearProgram::is_maxim);
	NODE_SET_PROTOTYPE_METHOD(tpl, "add_constraint", LinearProgram::add_constraint);
	NODE_SET_PROTOTYPE_METHOD(tpl, "add_constraintex", LinearProgram::add_constraintex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_add_rowmode", LinearProgram::set_add_rowmode);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_add_rowmode", LinearProgram::is_add_rowmode);
	NODE_SET_PROTOTYPE_METHOD(tpl, "str_add_constraint", LinearProgram::str_add_constraint);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_row", LinearProgram::set_row);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_rowex", LinearProgram::set_rowex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_row", LinearProgram::get_row);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_rowex", LinearProgram::get_rowex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "del_constraint", LinearProgram::del_constraint);
	NODE_SET_PROTOTYPE_METHOD(tpl, "add_lag_con", LinearProgram::add_lag_con);
	NODE_SET_PROTOTYPE_METHOD(tpl, "str_add_lag_con", LinearProgram::str_add_lag_con);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_lag_trace", LinearProgram::set_lag_trace);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_lag_trace", LinearProgram::is_lag_trace);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_constr_type", LinearProgram::set_constr_type);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_constr_type", LinearProgram::get_constr_type);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_constr_value", LinearProgram::get_constr_value);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_constr_type", LinearProgram::is_constr_type);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_rh", LinearProgram::set_rh);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_rh", LinearProgram::get_rh);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_rh_range", LinearProgram::set_rh_range);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_rh_range", LinearProgram::get_rh_range);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_rh_vec", LinearProgram::set_rh_vec);
	NODE_SET_PROTOTYPE_METHOD(tpl, "str_set_rh_vec", LinearProgram::str_set_rh_vec);
	NODE_SET_PROTOTYPE_METHOD(tpl, "add_column", LinearProgram::add_column);
	NODE_SET_PROTOTYPE_METHOD(tpl, "add_columnex", LinearProgram::add_columnex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "str_add_column", LinearProgram::str_add_column);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_column", LinearProgram::set_column);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_columnex", LinearProgram::set_columnex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "column_in_lp", LinearProgram::column_in_lp);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_columnex", LinearProgram::get_columnex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_column", LinearProgram::get_column);
	NODE_SET_PROTOTYPE_METHOD(tpl, "del_column", LinearProgram::del_column);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_mat", LinearProgram::set_mat);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_mat", LinearProgram::get_mat);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_mat_byindex", LinearProgram::get_mat_byindex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_nonzeros", LinearProgram::get_nonzeros);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_bounds_tighter", LinearProgram::set_bounds_tighter);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_bounds_tighter", LinearProgram::get_bounds_tighter);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_upbo", LinearProgram::set_upbo);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_upbo", LinearProgram::get_upbo);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_lowbo", LinearProgram::set_lowbo);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_lowbo", LinearProgram::get_lowbo);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_bounds", LinearProgram::set_bounds);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_unbounded", LinearProgram::set_unbounded);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_unbounded", LinearProgram::is_unbounded);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_int", LinearProgram::set_int);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_int", LinearProgram::is_int);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_binary", LinearProgram::set_binary);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_binary", LinearProgram::is_binary);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_semicont", LinearProgram::set_semicont);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_semicont", LinearProgram::is_semicont);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_negative", LinearProgram::is_negative);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_var_weights", LinearProgram::set_var_weights);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_var_priority", LinearProgram::get_var_priority);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_pseudocosts", LinearProgram::set_pseudocosts);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_pseudocosts", LinearProgram::get_pseudocosts);
	NODE_SET_PROTOTYPE_METHOD(tpl, "add_SOS", LinearProgram::add_SOS);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_SOS_var", LinearProgram::is_SOS_var);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_row_name", LinearProgram::set_row_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_row_name", LinearProgram::get_row_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_origrow_name", LinearProgram::get_origrow_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_col_name", LinearProgram::set_col_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_col_name", LinearProgram::get_col_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_origcol_name", LinearProgram::get_origcol_name);
	NODE_SET_PROTOTYPE_METHOD(tpl, "unscale", LinearProgram::unscale);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_preferdual", LinearProgram::set_preferdual);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_simplextype", LinearProgram::set_simplextype);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_simplextype", LinearProgram::get_simplextype);
	NODE_SET_PROTOTYPE_METHOD(tpl, "default_basis", LinearProgram::default_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_basiscrash", LinearProgram::set_basiscrash);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_basiscrash", LinearProgram::get_basiscrash);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_basisvar", LinearProgram::set_basisvar);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_basis", LinearProgram::set_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_basis", LinearProgram::get_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "reset_basis", LinearProgram::reset_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "guess_basis", LinearProgram::guess_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_feasible", LinearProgram::is_feasible);
	NODE_SET_PROTOTYPE_METHOD(tpl, "solve", LinearProgram::solve);
	NODE_SET_PROTOTYPE_METHOD(tpl, "time_elapsed", LinearProgram::time_elapsed);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "put_bb_nodefunc", LinearProgram::put_bb_nodefunc);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "put_bb_branchfunc", LinearProgram::put_bb_branchfunc);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "put_abortfunc", LinearProgram::put_abortfunc);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "put_logfunc", LinearProgram::put_logfunc);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "put_msgfunc", LinearProgram::put_msgfunc);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_primal_solution", LinearProgram::get_primal_solution);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_primal_solution", LinearProgram::get_ptr_primal_solution);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_dual_solution", LinearProgram::get_dual_solution);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_dual_solution", LinearProgram::get_ptr_dual_solution);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_lambda", LinearProgram::get_lambda);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_lambda", LinearProgram::get_ptr_lambda);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_mps", LinearProgram::write_mps);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_MPS", LinearProgram::write_MPS);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_freemps", LinearProgram::write_freemps);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_freeMPS", LinearProgram::write_freeMPS);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_lp", LinearProgram::write_lp);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_LP", LinearProgram::write_LP);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_basis", LinearProgram::write_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "read_basis", LinearProgram::read_basis);
	NODE_SET_PROTOTYPE_METHOD(tpl, "write_params", LinearProgram::write_params);
	NODE_SET_PROTOTYPE_METHOD(tpl, "read_params", LinearProgram::read_params);
	NODE_SET_PROTOTYPE_METHOD(tpl, "reset_params", LinearProgram::reset_params);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_lp", LinearProgram::print_lp);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_tableau", LinearProgram::print_tableau);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_objective", LinearProgram::print_objective);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_solution", LinearProgram::print_solution);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_constraints", LinearProgram::print_constraints);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_duals", LinearProgram::print_duals);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_scales", LinearProgram::print_scales);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_str", LinearProgram::print_str);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_outputstream", LinearProgram::set_outputstream);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_outputfile", LinearProgram::set_outputfile);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_verbose", LinearProgram::set_verbose);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_verbose", LinearProgram::get_verbose);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "set_timeout", LinearProgram::set_timeout);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_timeout", LinearProgram::get_timeout);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_print_sol", LinearProgram::set_print_sol);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_print_sol", LinearProgram::get_print_sol);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_debug", LinearProgram::set_debug);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_debug", LinearProgram::is_debug);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_trace", LinearProgram::set_trace);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_trace", LinearProgram::is_trace);
	NODE_SET_PROTOTYPE_METHOD(tpl, "print_debugdump", LinearProgram::print_debugdump);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_anti_degen", LinearProgram::set_anti_degen);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_anti_degen", LinearProgram::get_anti_degen);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_anti_degen", LinearProgram::is_anti_degen);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_presolve", LinearProgram::set_presolve);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_presolve", LinearProgram::get_presolve);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_presolveloops", LinearProgram::get_presolveloops);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_presolve", LinearProgram::is_presolve);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_orig_index", LinearProgram::get_orig_index);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_lp_index", LinearProgram::get_lp_index);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_maxpivot", LinearProgram::set_maxpivot);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_maxpivot", LinearProgram::get_maxpivot);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_obj_bound", LinearProgram::set_obj_bound);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_obj_bound", LinearProgram::get_obj_bound);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_mip_gap", LinearProgram::set_mip_gap);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_mip_gap", LinearProgram::get_mip_gap);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_bb_rule", LinearProgram::set_bb_rule);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_bb_rule", LinearProgram::get_bb_rule);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_var_branch", LinearProgram::set_var_branch);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_var_branch", LinearProgram::get_var_branch);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_infinite", LinearProgram::is_infinite);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_infinite", LinearProgram::set_infinite);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_infinite", LinearProgram::get_infinite);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_epsint", LinearProgram::set_epsint);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_epsint", LinearProgram::get_epsint);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_epsb", LinearProgram::set_epsb);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_epsb", LinearProgram::get_epsb);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_epsd", LinearProgram::set_epsd);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_epsd", LinearProgram::get_epsd);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_epsel", LinearProgram::set_epsel);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_epsel", LinearProgram::get_epsel);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_epslevel", LinearProgram::set_epslevel);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_scaling", LinearProgram::set_scaling);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_scaling", LinearProgram::get_scaling);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_scalemode", LinearProgram::is_scalemode);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_scaletype", LinearProgram::is_scaletype);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_integerscaling", LinearProgram::is_integerscaling);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_scalelimit", LinearProgram::set_scalelimit);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_scalelimit", LinearProgram::get_scalelimit);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_improve", LinearProgram::set_improve);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_improve", LinearProgram::get_improve);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_pivoting", LinearProgram::set_pivoting);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_pivoting", LinearProgram::get_pivoting);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_partialprice", LinearProgram::set_partialprice);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_partialprice", LinearProgram::get_partialprice);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_multiprice", LinearProgram::set_multiprice);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_multiprice", LinearProgram::get_multiprice);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_use_names", LinearProgram::is_use_names);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_use_names", LinearProgram::set_use_names);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_nameindex", LinearProgram::get_nameindex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_piv_mode", LinearProgram::is_piv_mode);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_piv_rule", LinearProgram::is_piv_rule);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_break_at_first", LinearProgram::set_break_at_first);
	NODE_SET_PROTOTYPE_METHOD(tpl, "is_break_at_first", LinearProgram::is_break_at_first);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_bb_floorfirst", LinearProgram::set_bb_floorfirst);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_bb_floorfirst", LinearProgram::get_bb_floorfirst);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_bb_depthlimit", LinearProgram::set_bb_depthlimit);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_bb_depthlimit", LinearProgram::get_bb_depthlimit);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_break_at_value", LinearProgram::set_break_at_value);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_break_at_value", LinearProgram::get_break_at_value);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_negrange", LinearProgram::set_negrange);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_negrange", LinearProgram::get_negrange);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_epsperturb", LinearProgram::set_epsperturb);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_epsperturb", LinearProgram::get_epsperturb);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_epspivot", LinearProgram::set_epspivot);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_epspivot", LinearProgram::get_epspivot);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_max_level", LinearProgram::get_max_level);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_total_nodes", LinearProgram::get_total_nodes);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_total_iter", LinearProgram::get_total_iter);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_objective", LinearProgram::get_objective);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_working_objective", LinearProgram::get_working_objective);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_var_primalresult", LinearProgram::get_var_primalresult);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_var_dualresult", LinearProgram::get_var_dualresult);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_variables", LinearProgram::get_variables);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_variables", LinearProgram::get_ptr_variables);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_constraints", LinearProgram::get_constraints);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_constraints", LinearProgram::get_ptr_constraints);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_sensitivity_rhs", LinearProgram::get_sensitivity_rhs);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_sensitivity_rhs", LinearProgram::get_ptr_sensitivity_rhs);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_sensitivity_obj", LinearProgram::get_sensitivity_obj);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_sensitivity_objex", LinearProgram::get_sensitivity_objex);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_sensitivity_obj", LinearProgram::get_ptr_sensitivity_obj);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "get_ptr_sensitivity_objex", LinearProgram::get_ptr_sensitivity_objex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "set_solutionlimit", LinearProgram::set_solutionlimit);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_solutionlimit", LinearProgram::get_solutionlimit);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_solutioncount", LinearProgram::get_solutioncount);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_Norig_rows", LinearProgram::get_Norig_rows);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_Nrows", LinearProgram::get_Nrows);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_Lrows", LinearProgram::get_Lrows);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_Norig_columns", LinearProgram::get_Norig_columns);
	NODE_SET_PROTOTYPE_METHOD(tpl, "get_Ncolumns", LinearProgram::get_Ncolumns);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "write_lpex", LinearProgram::write_lpex);
//  NODE_SET_PROTOTYPE_METHOD(tpl, "MPS_writefileex", LinearProgram::MPS_writefileex);
	constructor = Persistent<Function>::New(tpl->GetFunction());
//	exports->Set(String::NewSymbol("LinearProgram"), tpl->GetFunction());
}


LinearProgram::LinearProgram() {
}


LinearProgram::~LinearProgram() {
	::delete_lp(this->lp);
}

NAN_METHOD(LinearProgram::New) {
	NanScope();
	LinearProgram* obj = new LinearProgram();
	obj->Wrap(args.This());
	NanReturnValue(args.This());
}


class SolveWorker : public NanAsyncWorker {
public:
	SolveWorker(NanCallback *callback, lprec* lp)
	: NanAsyncWorker(callback), lp(lp) {}
	~SolveWorker() {}

	void Execute() {
		int res = solve(lp);
		printf("solve %i\n", res);
	}

	void HandleOKCallback() {
		NanScope();

		Local<Value> argv[] = {
			NanNull(),
			NanNew<Number>(res)
		};

		callback->Call(2, argv);
	};

private:
	lprec* lp;
	int res;
};

NAN_METHOD(LinearProgram::solve_async) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
  	NanCallback *callback = new NanCallback(args[0].As<Function>());
	NanAsyncQueueWorker(new SolveWorker(callback, obj->lp));
	NanReturnUndefined();
}

NAN_METHOD(make_lp) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int rows = (int)(args[0]->Int32Value());
	int columns = (int)(args[1]->Int32Value());
	lprec * ret = ::make_lp(rows, columns);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(LinearProgram::resize_lp) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int rows = (int)(args[0]->Int32Value());
	int columns = (int)(args[1]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::resize_lp(obj->lp, rows, columns);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_status) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_status(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_statustext) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int statuscode = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	char * ret = ::get_statustext(obj->lp, statuscode);
	NanReturnValue(NanNew<String>(ret));
}
NAN_METHOD(LinearProgram::is_obj_in_basis) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_obj_in_basis(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_obj_in_basis) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL obj_in_basis = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_obj_in_basis(obj->lp, obj_in_basis);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::copy_lp) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	lprec * ret = ::copy_lp(obj->lp);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(LinearProgram::dualize_lp) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::dualize_lp(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::delete_lp) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::delete_lp(obj->lp);
	NanReturnUndefined();
}
/*
free_lp
lprec **,plp
*/
/*
NAN_METHOD(free_lp) {
NanScope();
if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
::free_lp(plp);
NanReturnUndefined();
}
*/
NAN_METHOD(LinearProgram::set_lp_name) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_lpname(args[0]);
	char* lpname = *str_lpname;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_lp_name(obj->lp, lpname);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_lp_name) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	char * ret = ::get_lp_name(obj->lp);
	NanReturnValue(NanNew<String>(ret));
}
NAN_METHOD(LinearProgram::has_BFP) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::has_BFP(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_nativeBFP) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_nativeBFP(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_BFP) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_BFP(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(read_XLI) {
	NanScope();
	if (args.Length() != 5) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
	if (!(args[2]->IsString())) return NanThrowTypeError("Third argument should be a String");
	if (!(args[3]->IsString())) return NanThrowTypeError("Fourth argument should be a String");
	if (!(args[4]->IsNumber())) return NanThrowTypeError("Fifth argument should be a Number");
	String::Utf8Value str_xliname(args[0]);
	char* xliname = *str_xliname;
	String::Utf8Value str_modelname(args[1]);
	char* modelname = *str_modelname;
	String::Utf8Value str_dataname(args[2]);
	char* dataname = *str_dataname;
	String::Utf8Value str_options(args[3]);
	char* options = *str_options;
	int verbose = (int)(args[4]->Int32Value());
	lprec * ret = ::read_XLI(xliname, modelname, dataname, options, verbose);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(LinearProgram::write_XLI) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
	if (!(args[2]->IsBoolean())) return NanThrowTypeError("Third argument should be a Boolean");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	String::Utf8Value str_options(args[1]);
	char* options = *str_options;
	MYBOOL results = (MYBOOL)(args[2]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_XLI(obj->lp, filename, options, results);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::has_XLI) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::has_XLI(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_nativeXLI) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_nativeXLI(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_XLI) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_XLI(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_obj) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	REAL value = (REAL)(args[1]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_obj(obj->lp, colnr, value);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_obj_fn) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* row;
	if (args[0]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[0]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_obj_fn(obj->lp, row);
	if (args[0]->IsArray()) {
		delete row;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_obj_fnex) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	int count = (int)(args[0]->Int32Value());
	REAL* row;
	if (args[1]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[1]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	int* colno;
	if (args[2]->IsArray()) {
		Handle<Array> colno_handle = Handle<Array>::Cast(args[2]);
		int colno_n = colno_handle->Length();
		colno = new int[colno_n];
		for (int i = 0; i < colno_n; i++)
			colno[i] = colno_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_obj_fnex(obj->lp, count, row, colno);
	if (args[1]->IsArray()) {
		delete row;
	}
	if (args[2]->IsArray()) {
		delete colno;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_set_obj_fn) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_row_string(args[0]);
	char* row_string = *str_row_string;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::str_set_obj_fn(obj->lp, row_string);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_sense) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL maximize = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_sense(obj->lp, maximize);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_maxim) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_maxim(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_minim) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_minim(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::is_maxim) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_maxim(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_constraint) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
	REAL* row;
	if (args[0]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[0]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	int constr_type = (int)(args[1]->Int32Value());
	REAL rh = (REAL)(args[2]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::add_constraint(obj->lp, row, constr_type, rh);
	if (args[0]->IsArray()) {
		delete row;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_constraintex) {
	NanScope();
	if (args.Length() != 5) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(args[3]->IsNumber())) return NanThrowTypeError("Fourth argument should be a Number");
	if (!(args[4]->IsNumber())) return NanThrowTypeError("Fifth argument should be a Number");
	int count = (int)(args[0]->Int32Value());
	REAL* row;
	if (args[1]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[1]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	int* colno;
	if (args[2]->IsArray()) {
		Handle<Array> colno_handle = Handle<Array>::Cast(args[2]);
		int colno_n = colno_handle->Length();
		colno = new int[colno_n];
		for (int i = 0; i < colno_n; i++)
			colno[i] = colno_handle->Get(i)->Int32Value();
	}
	int constr_type = (int)(args[3]->Int32Value());
	REAL rh = (REAL)(args[4]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::add_constraintex(obj->lp, count, row, colno, constr_type, rh);
	if (args[1]->IsArray()) {
		delete row;
	}
	if (args[2]->IsArray()) {
		delete colno;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_add_rowmode) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL turnon = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_add_rowmode(obj->lp, turnon);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_add_rowmode) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_add_rowmode(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_add_constraint) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
	String::Utf8Value str_row_string(args[0]);
	char* row_string = *str_row_string;
	int constr_type = (int)(args[1]->Int32Value());
	REAL rh = (REAL)(args[2]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::str_add_constraint(obj->lp, row_string, constr_type, rh);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_row) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	int rownr = (int)(args[0]->Int32Value());
	REAL* row;
	if (args[1]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[1]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_row(obj->lp, rownr, row);
	if (args[1]->IsArray()) {
		delete row;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_rowex) {
	NanScope();
	if (args.Length() != 4) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(args[3]->IsArray() || args[3]->IsNull())) return NanThrowTypeError("Fourth argument should be a Array of Numbers or NULL");
	int rownr = (int)(args[0]->Int32Value());
	int count = (int)(args[1]->Int32Value());
	REAL* row;
	if (args[2]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[2]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	int* colno;
	if (args[3]->IsArray()) {
		Handle<Array> colno_handle = Handle<Array>::Cast(args[3]);
		int colno_n = colno_handle->Length();
		colno = new int[colno_n];
		for (int i = 0; i < colno_n; i++)
			colno[i] = colno_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_rowex(obj->lp, rownr, count, row, colno);
	if (args[2]->IsArray()) {
		delete row;
	}
	if (args[3]->IsArray()) {
		delete colno;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_row) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	int rownr = (int)(args[0]->Int32Value());
	REAL* row;
	if (args[1]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[1]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_row(obj->lp, rownr, row);
	if (args[1]->IsArray()) {
		delete row;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_rowex) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	int rownr = (int)(args[0]->Int32Value());
	REAL* row;
	if (args[1]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[1]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	int* colno;
	if (args[2]->IsArray()) {
		Handle<Array> colno_handle = Handle<Array>::Cast(args[2]);
		int colno_n = colno_handle->Length();
		colno = new int[colno_n];
		for (int i = 0; i < colno_n; i++)
			colno[i] = colno_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_rowex(obj->lp, rownr, row, colno);
	if (args[1]->IsArray()) {
		delete row;
	}
	if (args[2]->IsArray()) {
		delete colno;
	}
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::del_constraint) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::del_constraint(obj->lp, rownr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_lag_con) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
	REAL* row;
	if (args[0]->IsArray()) {
		Handle<Array> row_handle = Handle<Array>::Cast(args[0]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = row_handle->Get(i)->NumberValue();
	}
	int con_type = (int)(args[1]->Int32Value());
	REAL rhs = (REAL)(args[2]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::add_lag_con(obj->lp, row, con_type, rhs);
	if (args[0]->IsArray()) {
		delete row;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_add_lag_con) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
	String::Utf8Value str_row_string(args[0]);
	char* row_string = *str_row_string;
	int con_type = (int)(args[1]->Int32Value());
	REAL rhs = (REAL)(args[2]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::str_add_lag_con(obj->lp, row_string, con_type, rhs);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_lag_trace) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL lag_trace = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_lag_trace(obj->lp, lag_trace);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::is_lag_trace) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_lag_trace(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_constr_type) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	int con_type = (int)(args[1]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_constr_type(obj->lp, rownr, con_type);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_constr_type) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_constr_type(obj->lp, rownr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_constr_value) {
	NanScope();
	if (args.Length() != 4) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(args[3]->IsArray() || args[3]->IsNull())) return NanThrowTypeError("Fourth argument should be a Array of Numbers or NULL");
	int rownr = (int)(args[0]->Int32Value());
	int count = (int)(args[1]->Int32Value());
	REAL* primsolution;
	if (args[2]->IsArray()) {
		Handle<Array> primsolution_handle = Handle<Array>::Cast(args[2]);
		int primsolution_n = primsolution_handle->Length();
		primsolution = new REAL[primsolution_n];
		for (int i = 0; i < primsolution_n; i++)
			primsolution[i] = primsolution_handle->Get(i)->NumberValue();
	}
	int* nzindex;
	if (args[3]->IsArray()) {
		Handle<Array> nzindex_handle = Handle<Array>::Cast(args[3]);
		int nzindex_n = nzindex_handle->Length();
		nzindex = new int[nzindex_n];
		for (int i = 0; i < nzindex_n; i++)
			nzindex[i] = nzindex_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_constr_value(obj->lp, rownr, count, primsolution, nzindex);
	if (args[2]->IsArray()) {
		delete primsolution;
	}
	if (args[3]->IsArray()) {
		delete nzindex;
	}
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::is_constr_type) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	int mask = (int)(args[1]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_constr_type(obj->lp, rownr, mask);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_rh) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	REAL value = (REAL)(args[1]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_rh(obj->lp, rownr, value);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_rh) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_rh(obj->lp, rownr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_rh_range) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	REAL deltavalue = (REAL)(args[1]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_rh_range(obj->lp, rownr, deltavalue);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_rh_range) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_rh_range(obj->lp, rownr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_rh_vec) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* rh;
	if (args[0]->IsArray()) {
		Handle<Array> rh_handle = Handle<Array>::Cast(args[0]);
		int rh_n = rh_handle->Length();
		rh = new REAL[rh_n];
		for (int i = 0; i < rh_n; i++)
			rh[i] = rh_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_rh_vec(obj->lp, rh);
	if (args[0]->IsArray()) {
		delete rh;
	}
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::str_set_rh_vec) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_rh_string(args[0]);
	char* rh_string = *str_rh_string;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::str_set_rh_vec(obj->lp, rh_string);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_column) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* column;
	if (args[0]->IsArray()) {
		Handle<Array> column_handle = Handle<Array>::Cast(args[0]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = column_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::add_column(obj->lp, column);
	if (args[0]->IsArray()) {
		delete column;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_columnex) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	int count = (int)(args[0]->Int32Value());
	REAL* column;
	if (args[1]->IsArray()) {
		Handle<Array> column_handle = Handle<Array>::Cast(args[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = column_handle->Get(i)->NumberValue();
	}
	int* rowno;
	if (args[2]->IsArray()) {
		Handle<Array> rowno_handle = Handle<Array>::Cast(args[2]);
		int rowno_n = rowno_handle->Length();
		rowno = new int[rowno_n];
		for (int i = 0; i < rowno_n; i++)
			rowno[i] = rowno_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::add_columnex(obj->lp, count, column, rowno);
	if (args[1]->IsArray()) {
		delete column;
	}
	if (args[2]->IsArray()) {
		delete rowno;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_add_column) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_col_string(args[0]);
	char* col_string = *str_col_string;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::str_add_column(obj->lp, col_string);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_column) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	int colnr = (int)(args[0]->Int32Value());
	REAL* column;
	if (args[1]->IsArray()) {
		Handle<Array> column_handle = Handle<Array>::Cast(args[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = column_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_column(obj->lp, colnr, column);
	if (args[1]->IsArray()) {
		delete column;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_columnex) {
	NanScope();
	if (args.Length() != 4) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(args[3]->IsArray() || args[3]->IsNull())) return NanThrowTypeError("Fourth argument should be a Array of Numbers or NULL");
	int colnr = (int)(args[0]->Int32Value());
	int count = (int)(args[1]->Int32Value());
	REAL* column;
	if (args[2]->IsArray()) {
		Handle<Array> column_handle = Handle<Array>::Cast(args[2]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = column_handle->Get(i)->NumberValue();
	}
	int* rowno;
	if (args[3]->IsArray()) {
		Handle<Array> rowno_handle = Handle<Array>::Cast(args[3]);
		int rowno_n = rowno_handle->Length();
		rowno = new int[rowno_n];
		for (int i = 0; i < rowno_n; i++)
			rowno[i] = rowno_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_columnex(obj->lp, colnr, count, column, rowno);
	if (args[2]->IsArray()) {
		delete column;
	}
	if (args[3]->IsArray()) {
		delete rowno;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::column_in_lp) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* column;
	if (args[0]->IsArray()) {
		Handle<Array> column_handle = Handle<Array>::Cast(args[0]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = column_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::column_in_lp(obj->lp, column);
	if (args[0]->IsArray()) {
		delete column;
	}
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_columnex) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	int colnr = (int)(args[0]->Int32Value());
	REAL* column;
	if (args[1]->IsArray()) {
		Handle<Array> column_handle = Handle<Array>::Cast(args[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = column_handle->Get(i)->NumberValue();
	}
	int* nzrow;
	if (args[2]->IsArray()) {
		Handle<Array> nzrow_handle = Handle<Array>::Cast(args[2]);
		int nzrow_n = nzrow_handle->Length();
		nzrow = new int[nzrow_n];
		for (int i = 0; i < nzrow_n; i++)
			nzrow[i] = nzrow_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_columnex(obj->lp, colnr, column, nzrow);
	if (args[1]->IsArray()) {
		delete column;
	}
	if (args[2]->IsArray()) {
		delete nzrow;
	}
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_column) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	int colnr = (int)(args[0]->Int32Value());
	REAL* column;
	if (args[1]->IsArray()) {
		Handle<Array> column_handle = Handle<Array>::Cast(args[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = column_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_column(obj->lp, colnr, column);
	if (args[1]->IsArray()) {
		delete column;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::del_column) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::del_column(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_mat) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	int colnr = (int)(args[1]->Int32Value());
	REAL value = (REAL)(args[2]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_mat(obj->lp, rownr, colnr, value);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_mat) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	int colnr = (int)(args[1]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_mat(obj->lp, rownr, colnr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_mat_byindex) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	if (!(args[2]->IsBoolean())) return NanThrowTypeError("Third argument should be a Boolean");
	int matindex = (int)(args[0]->Int32Value());
	MYBOOL isrow = (MYBOOL)(args[1]->BooleanValue());
	MYBOOL adjustsign = (MYBOOL)(args[2]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_mat_byindex(obj->lp, matindex, isrow, adjustsign);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_nonzeros) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_nonzeros(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bounds_tighter) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL tighten = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_bounds_tighter(obj->lp, tighten);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_bounds_tighter) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_bounds_tighter(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_upbo) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	REAL value = (REAL)(args[1]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_upbo(obj->lp, colnr, value);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_upbo) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_upbo(obj->lp, colnr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_lowbo) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	REAL value = (REAL)(args[1]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_lowbo(obj->lp, colnr, value);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_lowbo) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_lowbo(obj->lp, colnr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bounds) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	REAL lower = (REAL)(args[1]->NumberValue());
	REAL upper = (REAL)(args[2]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_bounds(obj->lp, colnr, lower, upper);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_unbounded) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_unbounded(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_unbounded) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_unbounded(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_int) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	int colnr = (int)(args[0]->Int32Value());
	MYBOOL must_be_int = (MYBOOL)(args[1]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_int(obj->lp, colnr, must_be_int);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_int) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_int(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_binary) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	int colnr = (int)(args[0]->Int32Value());
	MYBOOL must_be_bin = (MYBOOL)(args[1]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_binary(obj->lp, colnr, must_be_bin);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_binary) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_binary(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_semicont) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	int colnr = (int)(args[0]->Int32Value());
	MYBOOL must_be_sc = (MYBOOL)(args[1]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_semicont(obj->lp, colnr, must_be_sc);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_semicont) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_semicont(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_negative) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_negative(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_var_weights) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* weights;
	if (args[0]->IsArray()) {
		Handle<Array> weights_handle = Handle<Array>::Cast(args[0]);
		int weights_n = weights_handle->Length();
		weights = new REAL[weights_n];
		for (int i = 0; i < weights_n; i++)
			weights[i] = weights_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_var_weights(obj->lp, weights);
	if (args[0]->IsArray()) {
		delete weights;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_var_priority) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_var_priority(obj->lp, colnr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_pseudocosts) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	REAL* clower;
	if (args[0]->IsArray()) {
		Handle<Array> clower_handle = Handle<Array>::Cast(args[0]);
		int clower_n = clower_handle->Length();
		clower = new REAL[clower_n];
		for (int i = 0; i < clower_n; i++)
			clower[i] = clower_handle->Get(i)->NumberValue();
	}
	REAL* cupper;
	if (args[1]->IsArray()) {
		Handle<Array> cupper_handle = Handle<Array>::Cast(args[1]);
		int cupper_n = cupper_handle->Length();
		cupper = new REAL[cupper_n];
		for (int i = 0; i < cupper_n; i++)
			cupper[i] = cupper_handle->Get(i)->NumberValue();
	}
	int* updatelimit;
	if (args[2]->IsArray()) {
		Handle<Array> updatelimit_handle = Handle<Array>::Cast(args[2]);
		int updatelimit_n = updatelimit_handle->Length();
		updatelimit = new int[updatelimit_n];
		for (int i = 0; i < updatelimit_n; i++)
			updatelimit[i] = updatelimit_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_pseudocosts(obj->lp, clower, cupper, updatelimit);
	if (args[0]->IsArray()) {
		delete clower;
	}
	if (args[1]->IsArray()) {
		delete cupper;
	}
	if (args[2]->IsArray()) {
		delete updatelimit;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_pseudocosts) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	REAL* clower;
	if (args[0]->IsArray()) {
		Handle<Array> clower_handle = Handle<Array>::Cast(args[0]);
		int clower_n = clower_handle->Length();
		clower = new REAL[clower_n];
		for (int i = 0; i < clower_n; i++)
			clower[i] = clower_handle->Get(i)->NumberValue();
	}
	REAL* cupper;
	if (args[1]->IsArray()) {
		Handle<Array> cupper_handle = Handle<Array>::Cast(args[1]);
		int cupper_n = cupper_handle->Length();
		cupper = new REAL[cupper_n];
		for (int i = 0; i < cupper_n; i++)
			cupper[i] = cupper_handle->Get(i)->NumberValue();
	}
	int* updatelimit;
	if (args[2]->IsArray()) {
		Handle<Array> updatelimit_handle = Handle<Array>::Cast(args[2]);
		int updatelimit_n = updatelimit_handle->Length();
		updatelimit = new int[updatelimit_n];
		for (int i = 0; i < updatelimit_n; i++)
			updatelimit[i] = updatelimit_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_pseudocosts(obj->lp, clower, cupper, updatelimit);
	if (args[0]->IsArray()) {
		delete clower;
	}
	if (args[1]->IsArray()) {
		delete cupper;
	}
	if (args[2]->IsArray()) {
		delete updatelimit;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_SOS) {
	NanScope();
	if (args.Length() != 6) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
	if (!(args[3]->IsNumber())) return NanThrowTypeError("Fourth argument should be a Number");
	if (!(args[4]->IsArray() || args[4]->IsNull())) return NanThrowTypeError("Fifth argument should be a Array of Numbers or NULL");
	if (!(args[5]->IsArray() || args[5]->IsNull())) return NanThrowTypeError("Sixth argument should be a Array of Numbers or NULL");
	String::Utf8Value str_name(args[0]);
	char* name = *str_name;
	int sostype = (int)(args[1]->Int32Value());
	int priority = (int)(args[2]->Int32Value());
	int count = (int)(args[3]->Int32Value());
	int* sosvars;
	if (args[4]->IsArray()) {
		Handle<Array> sosvars_handle = Handle<Array>::Cast(args[4]);
		int sosvars_n = sosvars_handle->Length();
		sosvars = new int[sosvars_n];
		for (int i = 0; i < sosvars_n; i++)
			sosvars[i] = sosvars_handle->Get(i)->Int32Value();
	}
	REAL* weights;
	if (args[5]->IsArray()) {
		Handle<Array> weights_handle = Handle<Array>::Cast(args[5]);
		int weights_n = weights_handle->Length();
		weights = new REAL[weights_n];
		for (int i = 0; i < weights_n; i++)
			weights[i] = weights_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::add_SOS(obj->lp, name, sostype, priority, count, sosvars, weights);
	if (args[4]->IsArray()) {
		delete sosvars;
	}
	if (args[5]->IsArray()) {
		delete weights;
	}
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::is_SOS_var) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_SOS_var(obj->lp, colnr);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_row_name) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
	int rownr = (int)(args[0]->Int32Value());
	String::Utf8Value str_new_name(args[1]);
	char* new_name = *str_new_name;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_row_name(obj->lp, rownr, new_name);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_row_name) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	char * ret = ::get_row_name(obj->lp, rownr);
	NanReturnValue(NanNew<String>(ret));
}
NAN_METHOD(LinearProgram::get_origrow_name) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int rownr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	char * ret = ::get_origrow_name(obj->lp, rownr);
	NanReturnValue(NanNew<String>(ret));
}
NAN_METHOD(LinearProgram::set_col_name) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
	int colnr = (int)(args[0]->Int32Value());
	String::Utf8Value str_new_name(args[1]);
	char* new_name = *str_new_name;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_col_name(obj->lp, colnr, new_name);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_col_name) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	char * ret = ::get_col_name(obj->lp, colnr);
	NanReturnValue(NanNew<String>(ret));
}
NAN_METHOD(LinearProgram::get_origcol_name) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	char * ret = ::get_origcol_name(obj->lp, colnr);
	NanReturnValue(NanNew<String>(ret));
}
NAN_METHOD(LinearProgram::unscale) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::unscale(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_preferdual) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL dodual = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_preferdual(obj->lp, dodual);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_simplextype) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int simplextype = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_simplextype(obj->lp, simplextype);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_simplextype) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_simplextype(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::default_basis) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::default_basis(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_basiscrash) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int mode = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_basiscrash(obj->lp, mode);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_basiscrash) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_basiscrash(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_basisvar) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int basisPos = (int)(args[0]->Int32Value());
	int enteringCol = (int)(args[1]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::set_basisvar(obj->lp, basisPos, enteringCol);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_basis) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	int* bascolumn;
	if (args[0]->IsArray()) {
		Handle<Array> bascolumn_handle = Handle<Array>::Cast(args[0]);
		int bascolumn_n = bascolumn_handle->Length();
		bascolumn = new int[bascolumn_n];
		for (int i = 0; i < bascolumn_n; i++)
			bascolumn[i] = bascolumn_handle->Get(i)->Int32Value();
	}
	MYBOOL nonbasic = (MYBOOL)(args[1]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_basis(obj->lp, bascolumn, nonbasic);
	if (args[0]->IsArray()) {
		delete bascolumn;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_basis) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	int* bascolumn;
	if (args[0]->IsArray()) {
		Handle<Array> bascolumn_handle = Handle<Array>::Cast(args[0]);
		int bascolumn_n = bascolumn_handle->Length();
		bascolumn = new int[bascolumn_n];
		for (int i = 0; i < bascolumn_n; i++)
			bascolumn[i] = bascolumn_handle->Get(i)->Int32Value();
	}
	MYBOOL nonbasic = (MYBOOL)(args[1]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_basis(obj->lp, bascolumn, nonbasic);
	if (args[0]->IsArray()) {
		delete bascolumn;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::reset_basis) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::reset_basis(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::guess_basis) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	REAL* guessvector;
	if (args[0]->IsArray()) {
		Handle<Array> guessvector_handle = Handle<Array>::Cast(args[0]);
		int guessvector_n = guessvector_handle->Length();
		guessvector = new REAL[guessvector_n];
		for (int i = 0; i < guessvector_n; i++)
			guessvector[i] = guessvector_handle->Get(i)->NumberValue();
	}
	int* basisvector;
	if (args[1]->IsArray()) {
		Handle<Array> basisvector_handle = Handle<Array>::Cast(args[1]);
		int basisvector_n = basisvector_handle->Length();
		basisvector = new int[basisvector_n];
		for (int i = 0; i < basisvector_n; i++)
			basisvector[i] = basisvector_handle->Get(i)->Int32Value();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::guess_basis(obj->lp, guessvector, basisvector);
	if (args[0]->IsArray()) {
		delete guessvector;
	}
	if (args[1]->IsArray()) {
		delete basisvector;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_feasible) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	REAL* values;
	if (args[0]->IsArray()) {
		Handle<Array> values_handle = Handle<Array>::Cast(args[0]);
		int values_n = values_handle->Length();
		values = new REAL[values_n];
		for (int i = 0; i < values_n; i++)
			values[i] = values_handle->Get(i)->NumberValue();
	}
	REAL threshold = (REAL)(args[1]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_feasible(obj->lp, values, threshold);
	if (args[0]->IsArray()) {
		delete values;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::solve) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::solve(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::time_elapsed) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::time_elapsed(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
/*
put_bb_nodefunc
lphandleint_intfunc,newnode,void *,bbnodehandle
*/
/*
NAN_METHOD(LinearProgram::put_bb_nodefunc) {
NanScope();
if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
::put_bb_nodefunc(obj->lp, newnode, bbnodehandle);
NanReturnUndefined();
}
*/
/*
put_bb_branchfunc
lphandleint_intfunc,newbranch,void *,bbbranchhandle
*/
/*
NAN_METHOD(LinearProgram::put_bb_branchfunc) {
NanScope();
if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
::put_bb_branchfunc(obj->lp, newbranch, bbbranchhandle);
NanReturnUndefined();
}
*/
/*
put_abortfunc
lphandle_intfunc,newctrlc,void *,ctrlchandle
*/
/*
NAN_METHOD(LinearProgram::put_abortfunc) {
NanScope();
if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
::put_abortfunc(obj->lp, newctrlc, ctrlchandle);
NanReturnUndefined();
}
*/
/*
put_logfunc
lphandlestr_func,newlog,void *,loghandle
*/
/*
NAN_METHOD(LinearProgram::put_logfunc) {
NanScope();
if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
::put_logfunc(obj->lp, newlog, loghandle);
NanReturnUndefined();
}
*/
/*
put_msgfunc
lphandleint_func,newmsg,void *,msghandle,int,mask
*/
/*
NAN_METHOD(LinearProgram::put_msgfunc) {
NanScope();
if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
int mask = (int)(args[2]->Int32Value());
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
::put_msgfunc(obj->lp, newmsg, msghandle, mask);
NanReturnUndefined();
}
*/
NAN_METHOD(LinearProgram::get_primal_solution) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* pv;
	if (args[0]->IsArray()) {
		Handle<Array> pv_handle = Handle<Array>::Cast(args[0]);
		int pv_n = pv_handle->Length();
		pv = new REAL[pv_n];
		for (int i = 0; i < pv_n; i++)
			pv[i] = pv_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_primal_solution(obj->lp, pv);
	if (args[0]->IsArray()) {
		delete pv;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
get_ptr_primal_solution
REAL **,pv
*/
/*
NAN_METHOD(LinearProgram::get_ptr_primal_solution) {
NanScope();
if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_primal_solution(obj->lp, pv);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_dual_solution) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* rc;
	if (args[0]->IsArray()) {
		Handle<Array> rc_handle = Handle<Array>::Cast(args[0]);
		int rc_n = rc_handle->Length();
		rc = new REAL[rc_n];
		for (int i = 0; i < rc_n; i++)
			rc[i] = rc_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_dual_solution(obj->lp, rc);
	if (args[0]->IsArray()) {
		delete rc;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
get_ptr_dual_solution
REAL **,rc
*/
/*
NAN_METHOD(LinearProgram::get_ptr_dual_solution) {
NanScope();
if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_dual_solution(obj->lp, rc);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_lambda) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* lambda;
	if (args[0]->IsArray()) {
		Handle<Array> lambda_handle = Handle<Array>::Cast(args[0]);
		int lambda_n = lambda_handle->Length();
		lambda = new REAL[lambda_n];
		for (int i = 0; i < lambda_n; i++)
			lambda[i] = lambda_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_lambda(obj->lp, lambda);
	if (args[0]->IsArray()) {
		delete lambda;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
get_ptr_lambda
REAL **,lambda
*/
/*
NAN_METHOD(LinearProgram::get_ptr_lambda) {
NanScope();
if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_lambda(obj->lp, lambda);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(read_MPS) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	int options = (int)(args[1]->Int32Value());
	lprec * ret = ::read_MPS(filename, options);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(read_mps) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	String::Utf8Value str_filename(args[0]);
	FILE *filename = fopen(*str_filename, "r");
	int options = (int)(args[1]->Int32Value());
	lprec * ret = ::read_mps(filename, options);
	fclose(filename);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(read_freeMPS) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	int options = (int)(args[1]->Int32Value());
	lprec * ret = ::read_freeMPS(filename, options);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(read_freemps) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	String::Utf8Value str_filename(args[0]);
	FILE *filename = fopen(*str_filename, "r");
	int options = (int)(args[1]->Int32Value());
	lprec * ret = ::read_freemps(filename, options);
	fclose(filename);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(LinearProgram::write_mps) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_mps(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_MPS) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_output(args[0]);
	FILE *output = fopen(*str_output, "w");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_MPS(obj->lp, output);
	fclose(output);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_freemps) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_freemps(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_freeMPS) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_output(args[0]);
	FILE *output = fopen(*str_output, "w");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_freeMPS(obj->lp, output);
	fclose(output);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_lp) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_lp(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_LP) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_output(args[0]);
	FILE *output = fopen(*str_output, "w");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_LP(obj->lp, output);
	fclose(output);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
LP_readhandle
lprec **,lp,FILE *,filename,int,verbose,char *,lp_name
*/
/*
NAN_METHOD(LP_readhandle) {
NanScope();
if (args.Length() != 4) return NanThrowError("Invalid number of arguments");
if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
if (!(args[3]->IsString())) return NanThrowTypeError("Fourth argument should be a String");
String::Utf8Value str_filename(args[1]);
FILE *filename = fopen(*str_filename, "r");
int verbose = (int)(args[2]->Int32Value());
String::Utf8Value str_lp_name(args[3]);
char* lp_name = *str_lp_name;
MYBOOL ret = ::LP_readhandle(lp, filename, verbose, lp_name);
fclose(filename);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(read_lp) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsString())) return NanThrowTypeError("Third argument should be a String");
	String::Utf8Value str_filename(args[0]);
	FILE *filename = fopen(*str_filename, "r");
	int verbose = (int)(args[1]->Int32Value());
	String::Utf8Value str_lp_name(args[2]);
	char* lp_name = *str_lp_name;
	lprec * ret = ::read_lp(filename, verbose, lp_name);
	fclose(filename);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(read_LP) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	if (!(args[2]->IsString())) return NanThrowTypeError("Third argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	int verbose = (int)(args[1]->Int32Value());
	String::Utf8Value str_lp_name(args[2]);
	char* lp_name = *str_lp_name;
	lprec * ret = ::read_LP(filename, verbose, lp_name);
	Local<Object> instance = constructor->NewInstance();
	LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	NanReturnValue(instance);
}
NAN_METHOD(LinearProgram::write_basis) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_basis(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::read_basis) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	String::Utf8Value str_info(args[1]);
	char* info = *str_info;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::read_basis(obj->lp, filename, info);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_params) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	String::Utf8Value str_options(args[1]);
	char* options = *str_options;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::write_params(obj->lp, filename, options);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::read_params) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsString())) return NanThrowTypeError("Second argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	String::Utf8Value str_options(args[1]);
	char* options = *str_options;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::read_params(obj->lp, filename, options);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::reset_params) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::reset_params(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_lp) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_lp(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_tableau) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_tableau(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_objective) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_objective(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_solution) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int columns = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_solution(obj->lp, columns);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_constraints) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int columns = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_constraints(obj->lp, columns);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_duals) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_duals(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_scales) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_scales(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::print_str) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_str(args[0]);
	char* str = *str_str;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::print_str(obj->lp, str);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_outputstream) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_stream(args[0]);
	FILE *stream = fopen(*str_stream, "w");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_outputstream(obj->lp, stream);
	fclose(stream);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_outputfile) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_outputfile(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_verbose) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int verbose = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_verbose(obj->lp, verbose);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_verbose) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_verbose(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
/*
set_timeout
long,sectimeout
*/
/*
NAN_METHOD(LinearProgram::set_timeout) {
NanScope();
if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
::set_timeout(obj->lp, sectimeout);
NanReturnUndefined();
}
*/
NAN_METHOD(LinearProgram::get_timeout) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::get_timeout(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_print_sol) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int print_sol = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_print_sol(obj->lp, print_sol);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_print_sol) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_print_sol(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_debug) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL debug = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_debug(obj->lp, debug);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::is_debug) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_debug(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_trace) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL trace = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_trace(obj->lp, trace);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::is_trace) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_trace(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::print_debugdump) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	String::Utf8Value str_filename(args[0]);
	char* filename = *str_filename;
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::print_debugdump(obj->lp, filename);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_anti_degen) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int anti_degen = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_anti_degen(obj->lp, anti_degen);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_anti_degen) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_anti_degen(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::is_anti_degen) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int testmask = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_anti_degen(obj->lp, testmask);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_presolve) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int presolvemode = (int)(args[0]->Int32Value());
	int maxloops = (int)(args[1]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_presolve(obj->lp, presolvemode, maxloops);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_presolve) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_presolve(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_presolveloops) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_presolveloops(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::is_presolve) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int testmask = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_presolve(obj->lp, testmask);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_orig_index) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int lp_index = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_orig_index(obj->lp, lp_index);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_lp_index) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int orig_index = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_lp_index(obj->lp, orig_index);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_maxpivot) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int max_num_inv = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_maxpivot(obj->lp, max_num_inv);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_maxpivot) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_maxpivot(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_obj_bound) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL obj_bound = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_obj_bound(obj->lp, obj_bound);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_obj_bound) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_obj_bound(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_mip_gap) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	MYBOOL absolute = (MYBOOL)(args[0]->BooleanValue());
	REAL mip_gap = (REAL)(args[1]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_mip_gap(obj->lp, absolute, mip_gap);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_mip_gap) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL absolute = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_mip_gap(obj->lp, absolute);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bb_rule) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int bb_rule = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_bb_rule(obj->lp, bb_rule);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_bb_rule) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_bb_rule(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_var_branch) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsNumber())) return NanThrowTypeError("Second argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	int branch_mode = (int)(args[1]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_var_branch(obj->lp, colnr, branch_mode);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_var_branch) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int colnr = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_var_branch(obj->lp, colnr);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::is_infinite) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL value = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_infinite(obj->lp, value);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_infinite) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL infinite = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_infinite(obj->lp, infinite);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_infinite) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_infinite(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsint) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL epsint = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_epsint(obj->lp, epsint);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_epsint) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_epsint(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsb) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL epsb = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_epsb(obj->lp, epsb);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_epsb) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_epsb(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsd) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL epsd = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_epsd(obj->lp, epsd);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_epsd) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_epsd(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsel) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL epsel = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_epsel(obj->lp, epsel);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_epsel) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_epsel(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epslevel) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int epslevel = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_epslevel(obj->lp, epslevel);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_scaling) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int scalemode = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_scaling(obj->lp, scalemode);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_scaling) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_scaling(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::is_scalemode) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int testmask = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_scalemode(obj->lp, testmask);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_scaletype) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int scaletype = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_scaletype(obj->lp, scaletype);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_integerscaling) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_integerscaling(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_scalelimit) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL scalelimit = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_scalelimit(obj->lp, scalelimit);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_scalelimit) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_scalelimit(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_improve) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int improve = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_improve(obj->lp, improve);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_improve) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_improve(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_pivoting) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int piv_rule = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_pivoting(obj->lp, piv_rule);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_pivoting) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_pivoting(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_partialprice) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsBoolean())) return NanThrowTypeError("Third argument should be a Boolean");
	int blockcount = (int)(args[0]->Int32Value());
	int* blockstart;
	if (args[1]->IsArray()) {
		Handle<Array> blockstart_handle = Handle<Array>::Cast(args[1]);
		int blockstart_n = blockstart_handle->Length();
		blockstart = new int[blockstart_n];
		for (int i = 0; i < blockstart_n; i++)
			blockstart[i] = blockstart_handle->Get(i)->Int32Value();
	}
	MYBOOL isrow = (MYBOOL)(args[2]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_partialprice(obj->lp, blockcount, blockstart, isrow);
	if (args[1]->IsArray()) {
		delete blockstart;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_partialprice) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsBoolean())) return NanThrowTypeError("Third argument should be a Boolean");
	int* blockcount;
	if (args[0]->IsArray()) {
		Handle<Array> blockcount_handle = Handle<Array>::Cast(args[0]);
		int blockcount_n = blockcount_handle->Length();
		blockcount = new int[blockcount_n];
		for (int i = 0; i < blockcount_n; i++)
			blockcount[i] = blockcount_handle->Get(i)->Int32Value();
	}
	int* blockstart;
	if (args[1]->IsArray()) {
		Handle<Array> blockstart_handle = Handle<Array>::Cast(args[1]);
		int blockstart_n = blockstart_handle->Length();
		blockstart = new int[blockstart_n];
		for (int i = 0; i < blockstart_n; i++)
			blockstart[i] = blockstart_handle->Get(i)->Int32Value();
	}
	MYBOOL isrow = (MYBOOL)(args[2]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::get_partialprice(obj->lp, blockcount, blockstart, isrow);
	if (args[0]->IsArray()) {
		delete blockcount;
	}
	if (args[1]->IsArray()) {
		delete blockstart;
	}
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::set_multiprice) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int multiblockdiv = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::set_multiprice(obj->lp, multiblockdiv);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_multiprice) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL getabssize = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_multiprice(obj->lp, getabssize);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::is_use_names) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL isrow = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_use_names(obj->lp, isrow);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_use_names) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	MYBOOL isrow = (MYBOOL)(args[0]->BooleanValue());
	MYBOOL use_names = (MYBOOL)(args[1]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_use_names(obj->lp, isrow, use_names);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_nameindex) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsString())) return NanThrowTypeError("First argument should be a String");
	if (!(args[1]->IsBoolean())) return NanThrowTypeError("Second argument should be a Boolean");
	String::Utf8Value str_varname(args[0]);
	char* varname = *str_varname;
	MYBOOL isrow = (MYBOOL)(args[1]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_nameindex(obj->lp, varname, isrow);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::is_piv_mode) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int testmask = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_piv_mode(obj->lp, testmask);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_piv_rule) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int rule = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_piv_rule(obj->lp, rule);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_break_at_first) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsBoolean())) return NanThrowTypeError("First argument should be a Boolean");
	MYBOOL break_at_first = (MYBOOL)(args[0]->BooleanValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_break_at_first(obj->lp, break_at_first);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::is_break_at_first) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::is_break_at_first(obj->lp);
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_bb_floorfirst) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int bb_floorfirst = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_bb_floorfirst(obj->lp, bb_floorfirst);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_bb_floorfirst) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_bb_floorfirst(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bb_depthlimit) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int bb_maxlevel = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_bb_depthlimit(obj->lp, bb_maxlevel);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_bb_depthlimit) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_bb_depthlimit(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_break_at_value) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL break_at_value = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_break_at_value(obj->lp, break_at_value);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_break_at_value) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_break_at_value(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_negrange) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL negrange = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_negrange(obj->lp, negrange);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_negrange) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_negrange(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsperturb) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL epsperturb = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_epsperturb(obj->lp, epsperturb);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_epsperturb) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_epsperturb(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epspivot) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	REAL epspivot = (REAL)(args[0]->NumberValue());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_epspivot(obj->lp, epspivot);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_epspivot) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_epspivot(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_max_level) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_max_level(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_total_nodes) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::get_total_nodes(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_total_iter) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::get_total_iter(obj->lp);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_objective) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_objective(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_working_objective) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_working_objective(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_var_primalresult) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int index = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_var_primalresult(obj->lp, index);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_var_dualresult) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int index = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	REAL ret = ::get_var_dualresult(obj->lp, index);
	NanReturnValue(NanNew<Number>(ret));
}
//checked
NAN_METHOD(LinearProgram::get_variables) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray())) return NanThrowTypeError("First argument should be a Array of Numbers");
	Handle<Array> var_handle = Handle<Array>::Cast(args[0]);
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int var_n = ::get_Ncolumns(obj->lp);
	REAL* var = new REAL[var_n];
	MYBOOL ret = ::get_variables(obj->lp, var);
	for (int i = 0; i < var_n; i++)
		var_handle->Set(i, NanNew<Number>(var[i]));
	delete var;
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
get_ptr_variables
REAL **,var
*/
/*
NAN_METHOD(LinearProgram::get_ptr_variables) {
NanScope();
if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_variables(obj->lp, var);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_constraints) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* constr;
	if (args[0]->IsArray()) {
		Handle<Array> constr_handle = Handle<Array>::Cast(args[0]);
		int constr_n = constr_handle->Length();
		constr = new REAL[constr_n];
		for (int i = 0; i < constr_n; i++)
			constr[i] = constr_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_constraints(obj->lp, constr);
	if (args[0]->IsArray()) {
		delete constr;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
get_ptr_constraints
REAL **,constr
*/
/*
NAN_METHOD(LinearProgram::get_ptr_constraints) {
NanScope();
if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_constraints(obj->lp, constr);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_sensitivity_rhs) {
	NanScope();
	if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	REAL* duals;
	if (args[0]->IsArray()) {
		Handle<Array> duals_handle = Handle<Array>::Cast(args[0]);
		int duals_n = duals_handle->Length();
		duals = new REAL[duals_n];
		for (int i = 0; i < duals_n; i++)
			duals[i] = duals_handle->Get(i)->NumberValue();
	}
	REAL* dualsfrom;
	if (args[1]->IsArray()) {
		Handle<Array> dualsfrom_handle = Handle<Array>::Cast(args[1]);
		int dualsfrom_n = dualsfrom_handle->Length();
		dualsfrom = new REAL[dualsfrom_n];
		for (int i = 0; i < dualsfrom_n; i++)
			dualsfrom[i] = dualsfrom_handle->Get(i)->NumberValue();
	}
	REAL* dualstill;
	if (args[2]->IsArray()) {
		Handle<Array> dualstill_handle = Handle<Array>::Cast(args[2]);
		int dualstill_n = dualstill_handle->Length();
		dualstill = new REAL[dualstill_n];
		for (int i = 0; i < dualstill_n; i++)
			dualstill[i] = dualstill_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_sensitivity_rhs(obj->lp, duals, dualsfrom, dualstill);
	if (args[0]->IsArray()) {
		delete duals;
	}
	if (args[1]->IsArray()) {
		delete dualsfrom;
	}
	if (args[2]->IsArray()) {
		delete dualstill;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
get_ptr_sensitivity_rhs
REAL **,duals,REAL **,dualsfrom,REAL **,dualstill
*/
/*
NAN_METHOD(LinearProgram::get_ptr_sensitivity_rhs) {
NanScope();
if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_sensitivity_rhs(obj->lp, duals, dualsfrom, dualstill);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_sensitivity_obj) {
	NanScope();
	if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	REAL* objfrom;
	if (args[0]->IsArray()) {
		Handle<Array> objfrom_handle = Handle<Array>::Cast(args[0]);
		int objfrom_n = objfrom_handle->Length();
		objfrom = new REAL[objfrom_n];
		for (int i = 0; i < objfrom_n; i++)
			objfrom[i] = objfrom_handle->Get(i)->NumberValue();
	}
	REAL* objtill;
	if (args[1]->IsArray()) {
		Handle<Array> objtill_handle = Handle<Array>::Cast(args[1]);
		int objtill_n = objtill_handle->Length();
		objtill = new REAL[objtill_n];
		for (int i = 0; i < objtill_n; i++)
			objtill[i] = objtill_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_sensitivity_obj(obj->lp, objfrom, objtill);
	if (args[0]->IsArray()) {
		delete objfrom;
	}
	if (args[1]->IsArray()) {
		delete objtill;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_sensitivity_objex) {
	NanScope();
	if (args.Length() != 4) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsArray() || args[0]->IsNull())) return NanThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(args[1]->IsArray() || args[1]->IsNull())) return NanThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(args[2]->IsArray() || args[2]->IsNull())) return NanThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(args[3]->IsArray() || args[3]->IsNull())) return NanThrowTypeError("Fourth argument should be a Array of Numbers or NULL");
	REAL* objfrom;
	if (args[0]->IsArray()) {
		Handle<Array> objfrom_handle = Handle<Array>::Cast(args[0]);
		int objfrom_n = objfrom_handle->Length();
		objfrom = new REAL[objfrom_n];
		for (int i = 0; i < objfrom_n; i++)
			objfrom[i] = objfrom_handle->Get(i)->NumberValue();
	}
	REAL* objtill;
	if (args[1]->IsArray()) {
		Handle<Array> objtill_handle = Handle<Array>::Cast(args[1]);
		int objtill_n = objtill_handle->Length();
		objtill = new REAL[objtill_n];
		for (int i = 0; i < objtill_n; i++)
			objtill[i] = objtill_handle->Get(i)->NumberValue();
	}
	REAL* objfromvalue;
	if (args[2]->IsArray()) {
		Handle<Array> objfromvalue_handle = Handle<Array>::Cast(args[2]);
		int objfromvalue_n = objfromvalue_handle->Length();
		objfromvalue = new REAL[objfromvalue_n];
		for (int i = 0; i < objfromvalue_n; i++)
			objfromvalue[i] = objfromvalue_handle->Get(i)->NumberValue();
	}
	REAL* objtillvalue;
	if (args[3]->IsArray()) {
		Handle<Array> objtillvalue_handle = Handle<Array>::Cast(args[3]);
		int objtillvalue_n = objtillvalue_handle->Length();
		objtillvalue = new REAL[objtillvalue_n];
		for (int i = 0; i < objtillvalue_n; i++)
			objtillvalue[i] = objtillvalue_handle->Get(i)->NumberValue();
	}
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	MYBOOL ret = ::get_sensitivity_objex(obj->lp, objfrom, objtill, objfromvalue, objtillvalue);
	if (args[0]->IsArray()) {
		delete objfrom;
	}
	if (args[1]->IsArray()) {
		delete objtill;
	}
	if (args[2]->IsArray()) {
		delete objfromvalue;
	}
	if (args[3]->IsArray()) {
		delete objtillvalue;
	}
	NanReturnValue(NanNew<Boolean>(ret == 1));
}
/*
get_ptr_sensitivity_obj
REAL **,objfrom,REAL **,objtill
*/
/*
NAN_METHOD(LinearProgram::get_ptr_sensitivity_obj) {
NanScope();
if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_sensitivity_obj(obj->lp, objfrom, objtill);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
/*
get_ptr_sensitivity_objex
REAL **,objfrom,REAL **,objtill,REAL **,objfromvalue,REAL **,objtillvalue
*/
/*
NAN_METHOD(LinearProgram::get_ptr_sensitivity_objex) {
NanScope();
if (args.Length() != 4) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::get_ptr_sensitivity_objex(obj->lp, objfrom, objtill, objfromvalue, objtillvalue);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::set_solutionlimit) {
	NanScope();
	if (args.Length() != 1) return NanThrowError("Invalid number of arguments");
	if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
	int limit = (int)(args[0]->Int32Value());
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	::set_solutionlimit(obj->lp, limit);
	NanReturnUndefined();
}
NAN_METHOD(LinearProgram::get_solutionlimit) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_solutionlimit(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_solutioncount) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_solutioncount(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Norig_rows) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_Norig_rows(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Nrows) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_Nrows(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Lrows) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_Lrows(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Norig_columns) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_Norig_columns(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Ncolumns) {
	NanScope();
	if (args.Length() != 0) return NanThrowError("Invalid number of arguments");
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
	int ret = ::get_Ncolumns(obj->lp);
	NanReturnValue(NanNew<Number>(ret));
}
/*
MPS_readex
lprec **,newlp,void *,userhandle,read_modeldata_func,read_modeldata,int,typeMPS,int,options
*/
/*
NAN_METHOD(MPS_readex) {
NanScope();
if (args.Length() != 5) return NanThrowError("Invalid number of arguments");
if (!(args[3]->IsNumber())) return NanThrowTypeError("Fourth argument should be a Number");
if (!(args[4]->IsNumber())) return NanThrowTypeError("Fifth argument should be a Number");
int typeMPS = (int)(args[3]->Int32Value());
int options = (int)(args[4]->Int32Value());
MYBOOL ret = ::MPS_readex(newlp, userhandle, read_modeldata, typeMPS, options);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
/*
read_lpex
void *,userhandle,read_modeldata_func,read_modeldata,int,verbose,char *,lp_name
*/
/*
NAN_METHOD(read_lpex) {
NanScope();
if (args.Length() != 4) return NanThrowError("Invalid number of arguments");
if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
if (!(args[3]->IsString())) return NanThrowTypeError("Fourth argument should be a String");
int verbose = (int)(args[2]->Int32Value());
String::Utf8Value str_lp_name(args[3]);
char* lp_name = *str_lp_name;
lprec * ret = ::read_lpex(userhandle, read_modeldata, verbose, lp_name);
Local<Object> instance = constructor->NewInstance();
LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
retobj->lp = ret;
NanReturnValue(instance);
}
*/
/*
write_lpex
void *,userhandle,write_modeldata_func,write_modeldata
*/
/*
NAN_METHOD(LinearProgram::write_lpex) {
NanScope();
if (args.Length() != 2) return NanThrowError("Invalid number of arguments");
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::write_lpex(obj->lp, userhandle, write_modeldata);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/
/*
read_mpsex
void *,userhandle,read_modeldata_func,read_modeldata,int,options
*/
/*
NAN_METHOD(read_mpsex) {
NanScope();
if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
int options = (int)(args[2]->Int32Value());
lprec * ret = ::read_mpsex(userhandle, read_modeldata, options);
Local<Object> instance = constructor->NewInstance();
LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
retobj->lp = ret;
NanReturnValue(instance);
}
*/
/*
read_freempsex
void *,userhandle,read_modeldata_func,read_modeldata,int,options
*/
/*
NAN_METHOD(read_freempsex) {
NanScope();
if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
if (!(args[2]->IsNumber())) return NanThrowTypeError("Third argument should be a Number");
int options = (int)(args[2]->Int32Value());
lprec * ret = ::read_freempsex(userhandle, read_modeldata, options);
Local<Object> instance = constructor->NewInstance();
LinearProgram* retobj = node::ObjectWrap::Unwrap<LinearProgram>(instance);
retobj->lp = ret;
NanReturnValue(instance);
}
*/
/*
MPS_writefileex
int,typeMPS,void *,userhandle,write_modeldata_func,write_modeldata
*/
/*
NAN_METHOD(LinearProgram::MPS_writefileex) {
NanScope();
if (args.Length() != 3) return NanThrowError("Invalid number of arguments");
if (!(args[0]->IsNumber())) return NanThrowTypeError("First argument should be a Number");
int typeMPS = (int)(args[0]->Int32Value());
LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
MYBOOL ret = ::MPS_writefileex(obj->lp, typeMPS, userhandle, write_modeldata);
NanReturnValue(NanNew<Boolean>(ret == 1));
}
*/