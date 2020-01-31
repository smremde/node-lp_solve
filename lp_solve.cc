#include <node.h>
#include "nan.h"

#include "lp_solve.h"
#include "lp_lib.h"

using namespace v8;

NAN_MODULE_INIT(InitAll) {
	Nan::Set(target, Nan::New<String>("lp_solve_version").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(getVersion)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("make_lp").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(make_lp)).ToLocalChecked());
	// Nan::Set(target, Nan::New<String>("free_lp").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(free_lp)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("read_XLI").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_XLI)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("read_MPS").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_MPS)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("read_mps").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_mps)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("read_freeMPS").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_freeMPS)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("read_freemps").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_freemps)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("read_lp").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_lp)).ToLocalChecked());
	Nan::Set(target, Nan::New<String>("read_LP").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_LP)).ToLocalChecked());
	// Nan::Set(target, Nan::New<String>("read_lpex").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_lpex)).ToLocalChecked());
	// Nan::Set(target, Nan::New<String>("read_mpsex").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_mpsex)).ToLocalChecked());
	// Nan::Set(target, Nan::New<String>("read_freempsex").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(read_freempsex)).ToLocalChecked());
	Local<Object> PRESOLVE = Nan::New<Object>();

	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_NONE").ToLocalChecked(), Nan::New<Number>(0));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_ROWS").ToLocalChecked(), Nan::New<Number>(1));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_COLS").ToLocalChecked(), Nan::New<Number>(2));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_LINDEP").ToLocalChecked(), Nan::New<Number>(4));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_AGGREGATE").ToLocalChecked(), Nan::New<Number>(8));  /* Not implemented */
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_SPARSER").ToLocalChecked(), Nan::New<Number>(16));  /* Not implemented */
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_SOS").ToLocalChecked(), Nan::New<Number>(32));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_REDUCEMIP").ToLocalChecked(), Nan::New<Number>(64));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_KNAPSACK").ToLocalChecked(), Nan::New<Number>(128));  /* Implementation not tested completely */
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_ELIMEQ2").ToLocalChecked(), Nan::New<Number>(256));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_IMPLIEDFREE").ToLocalChecked(), Nan::New<Number>(512));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_REDUCEGCD").ToLocalChecked(), Nan::New<Number>(1024));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_PROBEFIX").ToLocalChecked(), Nan::New<Number>(2048));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_PROBEREDUCE").ToLocalChecked(), Nan::New<Number>(4096));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_ROWDOMINATE").ToLocalChecked(), Nan::New<Number>(8192));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_COLDOMINATE").ToLocalChecked(), Nan::New<Number>(16384));  /* Reduced functionality, should be expanded */
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_MERGEROWS").ToLocalChecked(), Nan::New<Number>(32768));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_IMPLIEDSLK").ToLocalChecked(), Nan::New<Number>(65536));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_COLFIXDUAL").ToLocalChecked(), Nan::New<Number>(131072));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_BOUNDS").ToLocalChecked(), Nan::New<Number>(262144));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_LASTMASKMODE").ToLocalChecked(), Nan::New<Number>(524288 -1));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_DUALS").ToLocalChecked(), Nan::New<Number>(524288));
	Nan::Set(PRESOLVE, Nan::New<String>("PRESOLVE_SENSDUALS").ToLocalChecked(), Nan::New<Number>(1048576));

	Nan::Set(target, Nan::New<String>("PRESOLVE").ToLocalChecked(), PRESOLVE);

	LinearProgram::Init(target);
}

NODE_MODULE(lp_solve, InitAll);

NAN_METHOD(getVersion) {
	int majorversion, minorversion, release, build;

	lp_solve_version(&majorversion, &minorversion, &release, &build);

	Local<Object> ret = Nan::New<Object>();

	Nan::Set(ret, Nan::New<String>("majorversion").ToLocalChecked(), Nan::New<Number>(majorversion));
	Nan::Set(ret, Nan::New<String>("minorversion").ToLocalChecked(), Nan::New<Number>(minorversion));
	Nan::Set(ret, Nan::New<String>("release").ToLocalChecked(), Nan::New<Number>(release));
	Nan::Set(ret, Nan::New<String>("build").ToLocalChecked(), Nan::New<Number>(build));

	info.GetReturnValue().Set(ret);
};

void LinearProgram::Init(Local<Object> exports) {
	Local<FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(LinearProgram::New);
	tpl->SetClassName(Nan::New<String>("lprec").ToLocalChecked());
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(tpl, "solve_async", LinearProgram::solve_async);

	Nan::SetPrototypeMethod(tpl, "resize_lp", LinearProgram::resize_lp);
	Nan::SetPrototypeMethod(tpl, "get_status", LinearProgram::get_status);
	Nan::SetPrototypeMethod(tpl, "get_statustext", LinearProgram::get_statustext);
	Nan::SetPrototypeMethod(tpl, "is_obj_in_basis", LinearProgram::is_obj_in_basis);
	Nan::SetPrototypeMethod(tpl, "set_obj_in_basis", LinearProgram::set_obj_in_basis);
	Nan::SetPrototypeMethod(tpl, "copy_lp", LinearProgram::copy_lp);
	Nan::SetPrototypeMethod(tpl, "dualize_lp", LinearProgram::dualize_lp);
	Nan::SetPrototypeMethod(tpl, "delete_lp", LinearProgram::delete_lp);
	Nan::SetPrototypeMethod(tpl, "set_lp_name", LinearProgram::set_lp_name);
	Nan::SetPrototypeMethod(tpl, "get_lp_name", LinearProgram::get_lp_name);
	Nan::SetPrototypeMethod(tpl, "has_BFP", LinearProgram::has_BFP);
	Nan::SetPrototypeMethod(tpl, "is_nativeBFP", LinearProgram::is_nativeBFP);
	Nan::SetPrototypeMethod(tpl, "set_BFP", LinearProgram::set_BFP);
	Nan::SetPrototypeMethod(tpl, "write_XLI", LinearProgram::write_XLI);
	Nan::SetPrototypeMethod(tpl, "has_XLI", LinearProgram::has_XLI);
	Nan::SetPrototypeMethod(tpl, "is_nativeXLI", LinearProgram::is_nativeXLI);
	Nan::SetPrototypeMethod(tpl, "set_XLI", LinearProgram::set_XLI);
	Nan::SetPrototypeMethod(tpl, "set_obj", LinearProgram::set_obj);
	Nan::SetPrototypeMethod(tpl, "set_obj_fn", LinearProgram::set_obj_fn);
	Nan::SetPrototypeMethod(tpl, "set_obj_fnex", LinearProgram::set_obj_fnex);
	Nan::SetPrototypeMethod(tpl, "str_set_obj_fn", LinearProgram::str_set_obj_fn);
	Nan::SetPrototypeMethod(tpl, "set_sense", LinearProgram::set_sense);
	Nan::SetPrototypeMethod(tpl, "set_maxim", LinearProgram::set_maxim);
	Nan::SetPrototypeMethod(tpl, "set_minim", LinearProgram::set_minim);
	Nan::SetPrototypeMethod(tpl, "is_maxim", LinearProgram::is_maxim);
	Nan::SetPrototypeMethod(tpl, "add_constraint", LinearProgram::add_constraint);
	Nan::SetPrototypeMethod(tpl, "add_constraintex", LinearProgram::add_constraintex);
	Nan::SetPrototypeMethod(tpl, "set_add_rowmode", LinearProgram::set_add_rowmode);
	Nan::SetPrototypeMethod(tpl, "is_add_rowmode", LinearProgram::is_add_rowmode);
	Nan::SetPrototypeMethod(tpl, "str_add_constraint", LinearProgram::str_add_constraint);
	Nan::SetPrototypeMethod(tpl, "set_row", LinearProgram::set_row);
	Nan::SetPrototypeMethod(tpl, "set_rowex", LinearProgram::set_rowex);
	Nan::SetPrototypeMethod(tpl, "get_row", LinearProgram::get_row);
	Nan::SetPrototypeMethod(tpl, "get_rowex", LinearProgram::get_rowex);
	Nan::SetPrototypeMethod(tpl, "del_constraint", LinearProgram::del_constraint);
	Nan::SetPrototypeMethod(tpl, "add_lag_con", LinearProgram::add_lag_con);
	Nan::SetPrototypeMethod(tpl, "str_add_lag_con", LinearProgram::str_add_lag_con);
	Nan::SetPrototypeMethod(tpl, "set_lag_trace", LinearProgram::set_lag_trace);
	Nan::SetPrototypeMethod(tpl, "is_lag_trace", LinearProgram::is_lag_trace);
	Nan::SetPrototypeMethod(tpl, "set_constr_type", LinearProgram::set_constr_type);
	Nan::SetPrototypeMethod(tpl, "get_constr_type", LinearProgram::get_constr_type);
	Nan::SetPrototypeMethod(tpl, "get_constr_value", LinearProgram::get_constr_value);
	Nan::SetPrototypeMethod(tpl, "is_constr_type", LinearProgram::is_constr_type);
	Nan::SetPrototypeMethod(tpl, "set_rh", LinearProgram::set_rh);
	Nan::SetPrototypeMethod(tpl, "get_rh", LinearProgram::get_rh);
	Nan::SetPrototypeMethod(tpl, "set_rh_range", LinearProgram::set_rh_range);
	Nan::SetPrototypeMethod(tpl, "get_rh_range", LinearProgram::get_rh_range);
	Nan::SetPrototypeMethod(tpl, "set_rh_vec", LinearProgram::set_rh_vec);
	Nan::SetPrototypeMethod(tpl, "str_set_rh_vec", LinearProgram::str_set_rh_vec);
	Nan::SetPrototypeMethod(tpl, "add_column", LinearProgram::add_column);
	Nan::SetPrototypeMethod(tpl, "add_columnex", LinearProgram::add_columnex);
	Nan::SetPrototypeMethod(tpl, "str_add_column", LinearProgram::str_add_column);
	Nan::SetPrototypeMethod(tpl, "set_column", LinearProgram::set_column);
	Nan::SetPrototypeMethod(tpl, "set_columnex", LinearProgram::set_columnex);
	Nan::SetPrototypeMethod(tpl, "column_in_lp", LinearProgram::column_in_lp);
	Nan::SetPrototypeMethod(tpl, "get_columnex", LinearProgram::get_columnex);
	Nan::SetPrototypeMethod(tpl, "get_column", LinearProgram::get_column);
	Nan::SetPrototypeMethod(tpl, "del_column", LinearProgram::del_column);
	Nan::SetPrototypeMethod(tpl, "set_mat", LinearProgram::set_mat);
	Nan::SetPrototypeMethod(tpl, "get_mat", LinearProgram::get_mat);
	Nan::SetPrototypeMethod(tpl, "get_mat_byindex", LinearProgram::get_mat_byindex);
	Nan::SetPrototypeMethod(tpl, "get_nonzeros", LinearProgram::get_nonzeros);
	Nan::SetPrototypeMethod(tpl, "set_bounds_tighter", LinearProgram::set_bounds_tighter);
	Nan::SetPrototypeMethod(tpl, "get_bounds_tighter", LinearProgram::get_bounds_tighter);
	Nan::SetPrototypeMethod(tpl, "set_upbo", LinearProgram::set_upbo);
	Nan::SetPrototypeMethod(tpl, "get_upbo", LinearProgram::get_upbo);
	Nan::SetPrototypeMethod(tpl, "set_lowbo", LinearProgram::set_lowbo);
	Nan::SetPrototypeMethod(tpl, "get_lowbo", LinearProgram::get_lowbo);
	Nan::SetPrototypeMethod(tpl, "set_bounds", LinearProgram::set_bounds);
	Nan::SetPrototypeMethod(tpl, "set_unbounded", LinearProgram::set_unbounded);
	Nan::SetPrototypeMethod(tpl, "is_unbounded", LinearProgram::is_unbounded);
	Nan::SetPrototypeMethod(tpl, "set_int", LinearProgram::set_int);
	Nan::SetPrototypeMethod(tpl, "is_int", LinearProgram::is_int);
	Nan::SetPrototypeMethod(tpl, "set_binary", LinearProgram::set_binary);
	Nan::SetPrototypeMethod(tpl, "is_binary", LinearProgram::is_binary);
	Nan::SetPrototypeMethod(tpl, "set_semicont", LinearProgram::set_semicont);
	Nan::SetPrototypeMethod(tpl, "is_semicont", LinearProgram::is_semicont);
	Nan::SetPrototypeMethod(tpl, "is_negative", LinearProgram::is_negative);
	Nan::SetPrototypeMethod(tpl, "set_var_weights", LinearProgram::set_var_weights);
	Nan::SetPrototypeMethod(tpl, "get_var_priority", LinearProgram::get_var_priority);
	Nan::SetPrototypeMethod(tpl, "set_pseudocosts", LinearProgram::set_pseudocosts);
	Nan::SetPrototypeMethod(tpl, "get_pseudocosts", LinearProgram::get_pseudocosts);
	Nan::SetPrototypeMethod(tpl, "add_SOS", LinearProgram::add_SOS);
	Nan::SetPrototypeMethod(tpl, "is_SOS_var", LinearProgram::is_SOS_var);
	Nan::SetPrototypeMethod(tpl, "set_row_name", LinearProgram::set_row_name);
	Nan::SetPrototypeMethod(tpl, "get_row_name", LinearProgram::get_row_name);
	Nan::SetPrototypeMethod(tpl, "get_origrow_name", LinearProgram::get_origrow_name);
	Nan::SetPrototypeMethod(tpl, "set_col_name", LinearProgram::set_col_name);
	Nan::SetPrototypeMethod(tpl, "get_col_name", LinearProgram::get_col_name);
	Nan::SetPrototypeMethod(tpl, "get_origcol_name", LinearProgram::get_origcol_name);
	Nan::SetPrototypeMethod(tpl, "unscale", LinearProgram::unscale);
	Nan::SetPrototypeMethod(tpl, "set_preferdual", LinearProgram::set_preferdual);
	Nan::SetPrototypeMethod(tpl, "set_simplextype", LinearProgram::set_simplextype);
	Nan::SetPrototypeMethod(tpl, "get_simplextype", LinearProgram::get_simplextype);
	Nan::SetPrototypeMethod(tpl, "default_basis", LinearProgram::default_basis);
	Nan::SetPrototypeMethod(tpl, "set_basiscrash", LinearProgram::set_basiscrash);
	Nan::SetPrototypeMethod(tpl, "get_basiscrash", LinearProgram::get_basiscrash);
	Nan::SetPrototypeMethod(tpl, "set_basisvar", LinearProgram::set_basisvar);
	Nan::SetPrototypeMethod(tpl, "set_basis", LinearProgram::set_basis);
	Nan::SetPrototypeMethod(tpl, "get_basis", LinearProgram::get_basis);
	Nan::SetPrototypeMethod(tpl, "reset_basis", LinearProgram::reset_basis);
	Nan::SetPrototypeMethod(tpl, "guess_basis", LinearProgram::guess_basis);
	Nan::SetPrototypeMethod(tpl, "is_feasible", LinearProgram::is_feasible);
	Nan::SetPrototypeMethod(tpl, "solve", LinearProgram::solve);
	Nan::SetPrototypeMethod(tpl, "time_elapsed", LinearProgram::time_elapsed);
//  Nan::SetPrototypeMethod(tpl, "put_bb_nodefunc", LinearProgram::put_bb_nodefunc);
//  Nan::SetPrototypeMethod(tpl, "put_bb_branchfunc", LinearProgram::put_bb_branchfunc);
//  Nan::SetPrototypeMethod(tpl, "put_abortfunc", LinearProgram::put_abortfunc);
//  Nan::SetPrototypeMethod(tpl, "put_logfunc", LinearProgram::put_logfunc);
//  Nan::SetPrototypeMethod(tpl, "put_msgfunc", LinearProgram::put_msgfunc);
	Nan::SetPrototypeMethod(tpl, "get_primal_solution", LinearProgram::get_primal_solution);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_primal_solution", LinearProgram::get_ptr_primal_solution);
	Nan::SetPrototypeMethod(tpl, "get_dual_solution", LinearProgram::get_dual_solution);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_dual_solution", LinearProgram::get_ptr_dual_solution);
	Nan::SetPrototypeMethod(tpl, "get_lambda", LinearProgram::get_lambda);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_lambda", LinearProgram::get_ptr_lambda);
	Nan::SetPrototypeMethod(tpl, "write_mps", LinearProgram::write_mps);
	Nan::SetPrototypeMethod(tpl, "write_MPS", LinearProgram::write_MPS);
	Nan::SetPrototypeMethod(tpl, "write_freemps", LinearProgram::write_freemps);
	Nan::SetPrototypeMethod(tpl, "write_freeMPS", LinearProgram::write_freeMPS);
	Nan::SetPrototypeMethod(tpl, "write_lp", LinearProgram::write_lp);
	Nan::SetPrototypeMethod(tpl, "write_LP", LinearProgram::write_LP);
	Nan::SetPrototypeMethod(tpl, "write_basis", LinearProgram::write_basis);
	Nan::SetPrototypeMethod(tpl, "read_basis", LinearProgram::read_basis);
	Nan::SetPrototypeMethod(tpl, "write_params", LinearProgram::write_params);
	Nan::SetPrototypeMethod(tpl, "read_params", LinearProgram::read_params);
	Nan::SetPrototypeMethod(tpl, "reset_params", LinearProgram::reset_params);
	Nan::SetPrototypeMethod(tpl, "print_lp", LinearProgram::print_lp);
	Nan::SetPrototypeMethod(tpl, "print_tableau", LinearProgram::print_tableau);
	Nan::SetPrototypeMethod(tpl, "print_objective", LinearProgram::print_objective);
	Nan::SetPrototypeMethod(tpl, "print_solution", LinearProgram::print_solution);
	Nan::SetPrototypeMethod(tpl, "print_constraints", LinearProgram::print_constraints);
	Nan::SetPrototypeMethod(tpl, "print_duals", LinearProgram::print_duals);
	Nan::SetPrototypeMethod(tpl, "print_scales", LinearProgram::print_scales);
	Nan::SetPrototypeMethod(tpl, "print_str", LinearProgram::print_str);
	Nan::SetPrototypeMethod(tpl, "set_outputstream", LinearProgram::set_outputstream);
	Nan::SetPrototypeMethod(tpl, "set_outputfile", LinearProgram::set_outputfile);
	Nan::SetPrototypeMethod(tpl, "set_verbose", LinearProgram::set_verbose);
	Nan::SetPrototypeMethod(tpl, "get_verbose", LinearProgram::get_verbose);
  Nan::SetPrototypeMethod(tpl, "set_timeout", LinearProgram::set_timeout);
	Nan::SetPrototypeMethod(tpl, "get_timeout", LinearProgram::get_timeout);
	Nan::SetPrototypeMethod(tpl, "set_print_sol", LinearProgram::set_print_sol);
	Nan::SetPrototypeMethod(tpl, "get_print_sol", LinearProgram::get_print_sol);
	Nan::SetPrototypeMethod(tpl, "set_debug", LinearProgram::set_debug);
	Nan::SetPrototypeMethod(tpl, "is_debug", LinearProgram::is_debug);
	Nan::SetPrototypeMethod(tpl, "set_trace", LinearProgram::set_trace);
	Nan::SetPrototypeMethod(tpl, "is_trace", LinearProgram::is_trace);
	Nan::SetPrototypeMethod(tpl, "print_debugdump", LinearProgram::print_debugdump);
	Nan::SetPrototypeMethod(tpl, "set_anti_degen", LinearProgram::set_anti_degen);
	Nan::SetPrototypeMethod(tpl, "get_anti_degen", LinearProgram::get_anti_degen);
	Nan::SetPrototypeMethod(tpl, "is_anti_degen", LinearProgram::is_anti_degen);
	Nan::SetPrototypeMethod(tpl, "set_presolve", LinearProgram::set_presolve);
	Nan::SetPrototypeMethod(tpl, "get_presolve", LinearProgram::get_presolve);
	Nan::SetPrototypeMethod(tpl, "get_presolveloops", LinearProgram::get_presolveloops);
	Nan::SetPrototypeMethod(tpl, "is_presolve", LinearProgram::is_presolve);
	Nan::SetPrototypeMethod(tpl, "get_orig_index", LinearProgram::get_orig_index);
	Nan::SetPrototypeMethod(tpl, "get_lp_index", LinearProgram::get_lp_index);
	Nan::SetPrototypeMethod(tpl, "set_maxpivot", LinearProgram::set_maxpivot);
	Nan::SetPrototypeMethod(tpl, "get_maxpivot", LinearProgram::get_maxpivot);
	Nan::SetPrototypeMethod(tpl, "set_obj_bound", LinearProgram::set_obj_bound);
	Nan::SetPrototypeMethod(tpl, "get_obj_bound", LinearProgram::get_obj_bound);
	Nan::SetPrototypeMethod(tpl, "set_mip_gap", LinearProgram::set_mip_gap);
	Nan::SetPrototypeMethod(tpl, "get_mip_gap", LinearProgram::get_mip_gap);
	Nan::SetPrototypeMethod(tpl, "set_bb_rule", LinearProgram::set_bb_rule);
	Nan::SetPrototypeMethod(tpl, "get_bb_rule", LinearProgram::get_bb_rule);
	Nan::SetPrototypeMethod(tpl, "set_var_branch", LinearProgram::set_var_branch);
	Nan::SetPrototypeMethod(tpl, "get_var_branch", LinearProgram::get_var_branch);
	Nan::SetPrototypeMethod(tpl, "is_infinite", LinearProgram::is_infinite);
	Nan::SetPrototypeMethod(tpl, "set_infinite", LinearProgram::set_infinite);
	Nan::SetPrototypeMethod(tpl, "get_infinite", LinearProgram::get_infinite);
	Nan::SetPrototypeMethod(tpl, "set_epsint", LinearProgram::set_epsint);
	Nan::SetPrototypeMethod(tpl, "get_epsint", LinearProgram::get_epsint);
	Nan::SetPrototypeMethod(tpl, "set_epsb", LinearProgram::set_epsb);
	Nan::SetPrototypeMethod(tpl, "get_epsb", LinearProgram::get_epsb);
	Nan::SetPrototypeMethod(tpl, "set_epsd", LinearProgram::set_epsd);
	Nan::SetPrototypeMethod(tpl, "get_epsd", LinearProgram::get_epsd);
	Nan::SetPrototypeMethod(tpl, "set_epsel", LinearProgram::set_epsel);
	Nan::SetPrototypeMethod(tpl, "get_epsel", LinearProgram::get_epsel);
	Nan::SetPrototypeMethod(tpl, "set_epslevel", LinearProgram::set_epslevel);
	Nan::SetPrototypeMethod(tpl, "set_scaling", LinearProgram::set_scaling);
	Nan::SetPrototypeMethod(tpl, "get_scaling", LinearProgram::get_scaling);
	Nan::SetPrototypeMethod(tpl, "is_scalemode", LinearProgram::is_scalemode);
	Nan::SetPrototypeMethod(tpl, "is_scaletype", LinearProgram::is_scaletype);
	Nan::SetPrototypeMethod(tpl, "is_integerscaling", LinearProgram::is_integerscaling);
	Nan::SetPrototypeMethod(tpl, "set_scalelimit", LinearProgram::set_scalelimit);
	Nan::SetPrototypeMethod(tpl, "get_scalelimit", LinearProgram::get_scalelimit);
	Nan::SetPrototypeMethod(tpl, "set_improve", LinearProgram::set_improve);
	Nan::SetPrototypeMethod(tpl, "get_improve", LinearProgram::get_improve);
	Nan::SetPrototypeMethod(tpl, "set_pivoting", LinearProgram::set_pivoting);
	Nan::SetPrototypeMethod(tpl, "get_pivoting", LinearProgram::get_pivoting);
	Nan::SetPrototypeMethod(tpl, "set_partialprice", LinearProgram::set_partialprice);
	Nan::SetPrototypeMethod(tpl, "get_partialprice", LinearProgram::get_partialprice);
	Nan::SetPrototypeMethod(tpl, "set_multiprice", LinearProgram::set_multiprice);
	Nan::SetPrototypeMethod(tpl, "get_multiprice", LinearProgram::get_multiprice);
	Nan::SetPrototypeMethod(tpl, "is_use_names", LinearProgram::is_use_names);
	Nan::SetPrototypeMethod(tpl, "set_use_names", LinearProgram::set_use_names);
	Nan::SetPrototypeMethod(tpl, "get_nameindex", LinearProgram::get_nameindex);
	Nan::SetPrototypeMethod(tpl, "is_piv_mode", LinearProgram::is_piv_mode);
	Nan::SetPrototypeMethod(tpl, "is_piv_rule", LinearProgram::is_piv_rule);
	Nan::SetPrototypeMethod(tpl, "set_break_at_first", LinearProgram::set_break_at_first);
	Nan::SetPrototypeMethod(tpl, "is_break_at_first", LinearProgram::is_break_at_first);
	Nan::SetPrototypeMethod(tpl, "set_bb_floorfirst", LinearProgram::set_bb_floorfirst);
	Nan::SetPrototypeMethod(tpl, "get_bb_floorfirst", LinearProgram::get_bb_floorfirst);
	Nan::SetPrototypeMethod(tpl, "set_bb_depthlimit", LinearProgram::set_bb_depthlimit);
	Nan::SetPrototypeMethod(tpl, "get_bb_depthlimit", LinearProgram::get_bb_depthlimit);
	Nan::SetPrototypeMethod(tpl, "set_break_at_value", LinearProgram::set_break_at_value);
	Nan::SetPrototypeMethod(tpl, "get_break_at_value", LinearProgram::get_break_at_value);
	Nan::SetPrototypeMethod(tpl, "set_negrange", LinearProgram::set_negrange);
	Nan::SetPrototypeMethod(tpl, "get_negrange", LinearProgram::get_negrange);
	Nan::SetPrototypeMethod(tpl, "set_epsperturb", LinearProgram::set_epsperturb);
	Nan::SetPrototypeMethod(tpl, "get_epsperturb", LinearProgram::get_epsperturb);
	Nan::SetPrototypeMethod(tpl, "set_epspivot", LinearProgram::set_epspivot);
	Nan::SetPrototypeMethod(tpl, "get_epspivot", LinearProgram::get_epspivot);
	Nan::SetPrototypeMethod(tpl, "get_max_level", LinearProgram::get_max_level);
	Nan::SetPrototypeMethod(tpl, "get_total_nodes", LinearProgram::get_total_nodes);
	Nan::SetPrototypeMethod(tpl, "get_total_iter", LinearProgram::get_total_iter);
	Nan::SetPrototypeMethod(tpl, "get_objective", LinearProgram::get_objective);
	Nan::SetPrototypeMethod(tpl, "get_working_objective", LinearProgram::get_working_objective);
	Nan::SetPrototypeMethod(tpl, "get_var_primalresult", LinearProgram::get_var_primalresult);
	Nan::SetPrototypeMethod(tpl, "get_var_dualresult", LinearProgram::get_var_dualresult);
	Nan::SetPrototypeMethod(tpl, "get_variables", LinearProgram::get_variables);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_variables", LinearProgram::get_ptr_variables);
	Nan::SetPrototypeMethod(tpl, "get_constraints", LinearProgram::get_constraints);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_constraints", LinearProgram::get_ptr_constraints);
	Nan::SetPrototypeMethod(tpl, "get_sensitivity_rhs", LinearProgram::get_sensitivity_rhs);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_sensitivity_rhs", LinearProgram::get_ptr_sensitivity_rhs);
	Nan::SetPrototypeMethod(tpl, "get_sensitivity_obj", LinearProgram::get_sensitivity_obj);
	Nan::SetPrototypeMethod(tpl, "get_sensitivity_objex", LinearProgram::get_sensitivity_objex);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_sensitivity_obj", LinearProgram::get_ptr_sensitivity_obj);
//  Nan::SetPrototypeMethod(tpl, "get_ptr_sensitivity_objex", LinearProgram::get_ptr_sensitivity_objex);
	Nan::SetPrototypeMethod(tpl, "set_solutionlimit", LinearProgram::set_solutionlimit);
	Nan::SetPrototypeMethod(tpl, "get_solutionlimit", LinearProgram::get_solutionlimit);
	Nan::SetPrototypeMethod(tpl, "get_solutioncount", LinearProgram::get_solutioncount);
	Nan::SetPrototypeMethod(tpl, "get_Norig_rows", LinearProgram::get_Norig_rows);
	Nan::SetPrototypeMethod(tpl, "get_Nrows", LinearProgram::get_Nrows);
	Nan::SetPrototypeMethod(tpl, "get_Lrows", LinearProgram::get_Lrows);
	Nan::SetPrototypeMethod(tpl, "get_Norig_columns", LinearProgram::get_Norig_columns);
	Nan::SetPrototypeMethod(tpl, "get_Ncolumns", LinearProgram::get_Ncolumns);
//  Nan::SetPrototypeMethod(tpl, "write_lpex", LinearProgram::write_lpex);
//  Nan::SetPrototypeMethod(tpl, "MPS_writefileex", LinearProgram::MPS_writefileex);

	constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
}

LinearProgram::LinearProgram() {
}


LinearProgram::~LinearProgram() {
	if (this->lp) {
		::delete_lp(this->lp);
	}
}

NAN_METHOD(LinearProgram::New) {
	if (info.IsConstructCall()) {
		LinearProgram* obj = new LinearProgram();
		obj->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	} else {
		//Local<Value> argv[0] = { };
		Local<Function> cons = Nan::New<Function>(constructor);
		info.GetReturnValue().Set(Nan::NewInstance(cons).ToLocalChecked());
	}
}


class SolveWorker : public Nan::AsyncWorker {
public:
	SolveWorker(Nan::Callback *callback, lprec* lp)
	: Nan::AsyncWorker(callback), lp(lp) {}
	~SolveWorker() {}

	void Execute() {
		res = ::solve(lp);
		// printf("solve %i\n", res);
	}

	void HandleOKCallback() {
		Local<Value> argv[] = {
			Nan::Null(),
			Nan::New<Number>(res)
		};

		callback->Call(2, argv, this->async_resource);
	};

private:
	lprec* lp;
	int res;
};

NAN_METHOD(LinearProgram::solve_async) {
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
  	Nan::Callback *callback = new Nan::Callback(info[0].As<Function>());
	Nan::AsyncQueueWorker(new SolveWorker(callback, obj->lp));
	}

NAN_METHOD(make_lp) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int rows = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int columns = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	lprec * ret = ::make_lp(rows, columns);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(LinearProgram::resize_lp) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int rows = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int columns = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::resize_lp(obj->lp, rows, columns);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_status) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_status(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_statustext) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int statuscode = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	char * ret = ::get_statustext(obj->lp, statuscode);
	info.GetReturnValue().Set(Nan::New<String>(ret).ToLocalChecked());
}
NAN_METHOD(LinearProgram::is_obj_in_basis) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_obj_in_basis(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_obj_in_basis) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL obj_in_basis = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_obj_in_basis(obj->lp, obj_in_basis);
}
NAN_METHOD(LinearProgram::copy_lp) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	lprec * ret = ::copy_lp(obj->lp);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(LinearProgram::dualize_lp) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::dualize_lp(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::delete_lp) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::delete_lp(obj->lp);
	}
/*
free_lp
lprec **,plp
*/
/*
NAN_METHOD(free_lp) {
if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
::free_lp(plp);
}
*/
NAN_METHOD(LinearProgram::set_lp_name) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_lpname(info[0]);
	char* lpname = *str_lpname;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_lp_name(obj->lp, lpname);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_lp_name) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	char * ret = ::get_lp_name(obj->lp);
	info.GetReturnValue().Set(Nan::New<String>(ret).ToLocalChecked());
}
NAN_METHOD(LinearProgram::has_BFP) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::has_BFP(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_nativeBFP) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_nativeBFP(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_BFP) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_BFP(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(read_XLI) {
	if (info.Length() != 5) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
	if (!(info[2]->IsString())) return Nan::ThrowTypeError("Third argument should be a String");
	if (!(info[3]->IsString())) return Nan::ThrowTypeError("Fourth argument should be a String");
	if (!(info[4]->IsNumber())) return Nan::ThrowTypeError("Fifth argument should be a Number");
	Nan::Utf8String str_xliname(info[0]);
	char* xliname = *str_xliname;
	Nan::Utf8String str_modelname(info[1]);
	char* modelname = *str_modelname;
	Nan::Utf8String str_dataname(info[2]);
	char* dataname = *str_dataname;
	Nan::Utf8String str_options(info[3]);
	char* options = *str_options;
	int verbose = (int)(Nan::To<int32_t>(info[4]).ToChecked());
	lprec * ret = ::read_XLI(xliname, modelname, dataname, options, verbose);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(LinearProgram::write_XLI) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
	if (!(info[2]->IsBoolean())) return Nan::ThrowTypeError("Third argument should be a Boolean");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	Nan::Utf8String str_options(info[1]);
	char* options = *str_options;
	MYBOOL results = (MYBOOL)(Nan::To<bool>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_XLI(obj->lp, filename, options, results);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::has_XLI) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::has_XLI(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_nativeXLI) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_nativeXLI(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_XLI) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_XLI(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_obj) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL value = (REAL)(Nan::To<double>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_obj(obj->lp, colnr, value);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
// checked
NAN_METHOD(LinearProgram::set_obj_fn) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray())) return Nan::ThrowTypeError("First argument should be a Array of Numbers");	
	Local<Array> row_handle = Local<Array>::Cast(info[0]);
	int row_n = row_handle->Length();
	REAL* row = new REAL[row_n];
	for (int i = 0; i < row_n; i++)
		row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();	
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_obj_fn(obj->lp, row);
	delete[] row;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
//checked
NAN_METHOD(LinearProgram::set_obj_fnex) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers");
	if (!(info[2]->IsArray())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers");
	int count = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	Local<Array> row_handle = Local<Array>::Cast(info[1]);
	int row_n = row_handle->Length();
	REAL* row = new REAL[row_n];
	for (int i = 0; i < row_n; i++)
		row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	Local<Array> colno_handle = Local<Array>::Cast(info[2]);
	int colno_n = colno_handle->Length();
	int* colno = new int[colno_n];
	for (int i = 0; i < colno_n; i++)
		colno[i] = Nan::To<int32_t>(Nan::Get(colno_handle, i).ToLocalChecked()).ToChecked();
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_obj_fnex(obj->lp, count, row, colno);
	delete[] row;
	delete[] colno;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_set_obj_fn) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_row_string(info[0]);
	char* row_string = *str_row_string;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::str_set_obj_fn(obj->lp, row_string);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_sense) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL maximize = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_sense(obj->lp, maximize);
}
NAN_METHOD(LinearProgram::set_maxim) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_maxim(obj->lp);
}
NAN_METHOD(LinearProgram::set_minim) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_minim(obj->lp);
}
NAN_METHOD(LinearProgram::is_maxim) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_maxim(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
// checked
NAN_METHOD(LinearProgram::add_constraint) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray())) return Nan::ThrowTypeError("First argument should be a Array of Numbers");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
	Local<Array> row_handle = Local<Array>::Cast(info[0]);
	int row_n = row_handle->Length();
	REAL* row = new REAL[row_n];
	for (int i = 0; i < row_n; i++)
		row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	int constr_type = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	REAL rh = (REAL)(Nan::To<double>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::add_constraint(obj->lp, row, constr_type, rh);
	delete[] row;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
// checked
NAN_METHOD(LinearProgram::add_constraintex) {
	if (info.Length() != 5) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers");
	if (!(info[2]->IsArray())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers");
	if (!(info[3]->IsNumber())) return Nan::ThrowTypeError("Fourth argument should be a Number");
	if (!(info[4]->IsNumber())) return Nan::ThrowTypeError("Fifth argument should be a Number");
	int count = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	Local<Array> row_handle = Local<Array>::Cast(info[1]);
	int row_n = row_handle->Length();
	REAL* row = new REAL[row_n];
	for (int i = 0; i < row_n; i++)
		row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	Local<Array> colno_handle = Local<Array>::Cast(info[2]);
	int colno_n = colno_handle->Length();
	int* colno = new int[colno_n];
	for (int i = 0; i < colno_n; i++)
		colno[i] = Nan::To<int32_t>(Nan::Get(colno_handle, i).ToLocalChecked()).ToChecked();
	int constr_type = (int)(Nan::To<int32_t>(info[3]).ToChecked());
	REAL rh = (REAL)(Nan::To<double>(info[4]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::add_constraintex(obj->lp, count, row, colno, constr_type, rh);
	delete[] row;
	delete[] colno;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_add_rowmode) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL turnon = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_add_rowmode(obj->lp, turnon);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_add_rowmode) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_add_rowmode(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_add_constraint) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
	Nan::Utf8String str_row_string(info[0]);
	char* row_string = *str_row_string;
	int constr_type = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	REAL rh = (REAL)(Nan::To<double>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::str_add_constraint(obj->lp, row_string, constr_type, rh);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_row) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	Local<Array> row_handle = Local<Array>::Cast(info[1]);
	int row_n = row_handle->Length();
	REAL* row = new REAL[row_n];
	for (int i = 0; i < row_n; i++)
		row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_row(obj->lp, rownr, row);
	delete[] row;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
// checked
NAN_METHOD(LinearProgram::set_rowex) {
	if (info.Length() != 4) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsArray())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers");
	if (!(info[3]->IsArray())) return Nan::ThrowTypeError("Fourth argument should be a Array of Numbers");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int count = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	Local<Array> row_handle = Local<Array>::Cast(info[2]);
	int row_n = row_handle->Length();
	REAL* row = new REAL[row_n];
	for (int i = 0; i < row_n; i++)
		row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	Local<Array> colno_handle = Local<Array>::Cast(info[3]);
	int colno_n = colno_handle->Length();
	int* colno = new int[colno_n];
	for (int i = 0; i < colno_n; i++)
		colno[i] = Nan::To<int32_t>(Nan::Get(colno_handle, i).ToLocalChecked()).ToChecked();
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_rowex(obj->lp, rownr, count, row, colno);
	delete[] row;
	delete[] colno;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
// will not work
NAN_METHOD(LinearProgram::get_row) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL* row= NULL;
	if (info[1]->IsArray()) {
		Local<Array> row_handle = Local<Array>::Cast(info[1]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_row(obj->lp, rownr, row);
	if (info[1]->IsArray()) {
		delete[] row;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
// will not work
NAN_METHOD(LinearProgram::get_rowex) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL* row = NULL;
	if (info[1]->IsArray()) {
		Local<Array> row_handle = Local<Array>::Cast(info[1]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	}
	int* colno = NULL;
	if (info[2]->IsArray()) {
		Local<Array> colno_handle = Local<Array>::Cast(info[2]);
		int colno_n = colno_handle->Length();
		colno = new int[colno_n];
		for (int i = 0; i < colno_n; i++)
			colno[i] = Nan::To<int32_t>(Nan::Get(colno_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_rowex(obj->lp, rownr, row, colno);
	if (info[1]->IsArray()) {
		delete[] row;
	}
	if (info[2]->IsArray()) {
		delete[] colno;
	}
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
// checked
NAN_METHOD(LinearProgram::del_constraint) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::del_constraint(obj->lp, rownr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_lag_con) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
	REAL* row = NULL;
	if (info[0]->IsArray()) {
		Local<Array> row_handle = Local<Array>::Cast(info[0]);
		int row_n = row_handle->Length();
		row = new REAL[row_n];
		for (int i = 0; i < row_n; i++)
			row[i] = Nan::To<double>(Nan::Get(row_handle, i).ToLocalChecked()).ToChecked();
	}
	int con_type = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	REAL rhs = (REAL)(Nan::To<double>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::add_lag_con(obj->lp, row, con_type, rhs);
	if (info[0]->IsArray()) {
		delete[] row;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_add_lag_con) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
	Nan::Utf8String str_row_string(info[0]);
	char* row_string = *str_row_string;
	int con_type = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	REAL rhs = (REAL)(Nan::To<double>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::str_add_lag_con(obj->lp, row_string, con_type, rhs);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_lag_trace) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL lag_trace = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_lag_trace(obj->lp, lag_trace);
}
NAN_METHOD(LinearProgram::is_lag_trace) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_lag_trace(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_constr_type) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int con_type = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_constr_type(obj->lp, rownr, con_type);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_constr_type) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_constr_type(obj->lp, rownr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_constr_value) {
	if (info.Length() != 4) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(info[3]->IsArray() || info[3]->IsNull())) return Nan::ThrowTypeError("Fourth argument should be a Array of Numbers or NULL");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int count = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	REAL* primsolution = NULL;
	if (info[2]->IsArray()) {
		Local<Array> primsolution_handle = Local<Array>::Cast(info[2]);
		int primsolution_n = primsolution_handle->Length();
		primsolution = new REAL[primsolution_n];
		for (int i = 0; i < primsolution_n; i++)
			primsolution[i] = Nan::To<double>(Nan::Get(primsolution_handle, i).ToLocalChecked()).ToChecked();
	}
	int* nzindex = NULL;
	if (info[3]->IsArray()) {
		Local<Array> nzindex_handle = Local<Array>::Cast(info[3]);
		int nzindex_n = nzindex_handle->Length();
		nzindex = new int[nzindex_n];
		for (int i = 0; i < nzindex_n; i++)
			nzindex[i] = Nan::To<int32_t>(Nan::Get(nzindex_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_constr_value(obj->lp, rownr, count, primsolution, nzindex);
	if (info[2]->IsArray()) {
		delete[] primsolution;
	}
	if (info[3]->IsArray()) {
		delete[] nzindex;
	}
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::is_constr_type) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int mask = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_constr_type(obj->lp, rownr, mask);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_rh) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL value = (REAL)(Nan::To<double>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_rh(obj->lp, rownr, value);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_rh) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_rh(obj->lp, rownr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_rh_range) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL deltavalue = (REAL)(Nan::To<double>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_rh_range(obj->lp, rownr, deltavalue);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_rh_range) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_rh_range(obj->lp, rownr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_rh_vec) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers");
	REAL* rh = NULL;
	if (info[0]->IsArray()) {
		Local<Array> rh_handle = Local<Array>::Cast(info[0]);
		int rh_n = rh_handle->Length();
		rh = new REAL[rh_n];
		for (int i = 0; i < rh_n; i++)
			rh[i] = Nan::To<double>(Nan::Get(rh_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_rh_vec(obj->lp, rh);
	delete[] rh;
}
NAN_METHOD(LinearProgram::str_set_rh_vec) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_rh_string(info[0]);
	char* rh_string = *str_rh_string;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::str_set_rh_vec(obj->lp, rh_string);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_column) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* column = NULL;
	if (info[0]->IsArray()) {
		Local<Array> column_handle = Local<Array>::Cast(info[0]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = Nan::To<double>(Nan::Get(column_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::add_column(obj->lp, column);
	if (info[0]->IsArray()) {
		delete[] column;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_columnex) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	int count = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL* column = NULL;
	if (info[1]->IsArray()) {
		Local<Array> column_handle = Local<Array>::Cast(info[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = Nan::To<double>(Nan::Get(column_handle, i).ToLocalChecked()).ToChecked();
	}
	int* rowno = NULL;
	if (info[2]->IsArray()) {
		Local<Array> rowno_handle = Local<Array>::Cast(info[2]);
		int rowno_n = rowno_handle->Length();
		rowno = new int[rowno_n];
		for (int i = 0; i < rowno_n; i++)
			rowno[i] = Nan::To<int32_t>(Nan::Get(rowno_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::add_columnex(obj->lp, count, column, rowno);
	if (info[1]->IsArray()) {
		delete[] column;
	}
	if (info[2]->IsArray()) {
		delete[] rowno;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::str_add_column) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_col_string(info[0]);
	char* col_string = *str_col_string;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::str_add_column(obj->lp, col_string);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_column) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL* column = NULL;
	if (info[1]->IsArray()) {
		Local<Array> column_handle = Local<Array>::Cast(info[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = Nan::To<double>(Nan::Get(column_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_column(obj->lp, colnr, column);
	if (info[1]->IsArray()) {
		delete[] column;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_columnex) {
	if (info.Length() != 4) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(info[3]->IsArray() || info[3]->IsNull())) return Nan::ThrowTypeError("Fourth argument should be a Array of Numbers or NULL");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int count = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	REAL* column = NULL;
	if (info[2]->IsArray()) {
		Local<Array> column_handle = Local<Array>::Cast(info[2]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = Nan::To<double>(Nan::Get(column_handle, i).ToLocalChecked()).ToChecked();
	}
	int* rowno = NULL;
	if (info[3]->IsArray()) {
		Local<Array> rowno_handle = Local<Array>::Cast(info[3]);
		int rowno_n = rowno_handle->Length();
		rowno = new int[rowno_n];
		for (int i = 0; i < rowno_n; i++)
			rowno[i] = Nan::To<int32_t>(Nan::Get(rowno_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_columnex(obj->lp, colnr, count, column, rowno);
	if (info[2]->IsArray()) {
		delete[] column;
	}
	if (info[3]->IsArray()) {
		delete[] rowno;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::column_in_lp) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* column = NULL;
	if (info[0]->IsArray()) {
		Local<Array> column_handle = Local<Array>::Cast(info[0]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = Nan::To<double>(Nan::Get(column_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::column_in_lp(obj->lp, column);
	if (info[0]->IsArray()) {
		delete[] column;
	}
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_columnex) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL* column = NULL;
	if (info[1]->IsArray()) {
		Local<Array> column_handle = Local<Array>::Cast(info[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = Nan::To<double>(Nan::Get(column_handle, i).ToLocalChecked()).ToChecked();
	}
	int* nzrow = NULL;
	if (info[2]->IsArray()) {
		Local<Array> nzrow_handle = Local<Array>::Cast(info[2]);
		int nzrow_n = nzrow_handle->Length();
		nzrow = new int[nzrow_n];
		for (int i = 0; i < nzrow_n; i++)
			nzrow[i] = Nan::To<int32_t>(Nan::Get(nzrow_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_columnex(obj->lp, colnr, column, nzrow);
	if (info[1]->IsArray()) {
		delete[] column;
	}
	if (info[2]->IsArray()) {
		delete[] nzrow;
	}
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_column) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL* column = NULL;
	if (info[1]->IsArray()) {
		Local<Array> column_handle = Local<Array>::Cast(info[1]);
		int column_n = column_handle->Length();
		column = new REAL[column_n];
		for (int i = 0; i < column_n; i++)
			column[i] = Nan::To<double>(Nan::Get(column_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_column(obj->lp, colnr, column);
	if (info[1]->IsArray()) {
		delete[] column;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::del_column) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::del_column(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_mat) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int colnr = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	REAL value = (REAL)(Nan::To<double>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_mat(obj->lp, rownr, colnr, value);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_mat) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int colnr = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_mat(obj->lp, rownr, colnr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_mat_byindex) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	if (!(info[2]->IsBoolean())) return Nan::ThrowTypeError("Third argument should be a Boolean");
	int matindex = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	MYBOOL isrow = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	MYBOOL adjustsign = (MYBOOL)(Nan::To<bool>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_mat_byindex(obj->lp, matindex, isrow, adjustsign);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_nonzeros) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_nonzeros(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bounds_tighter) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL tighten = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_bounds_tighter(obj->lp, tighten);
}
NAN_METHOD(LinearProgram::get_bounds_tighter) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_bounds_tighter(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_upbo) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL value = (REAL)(Nan::To<double>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_upbo(obj->lp, colnr, value);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_upbo) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_upbo(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_lowbo) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL value = (REAL)(Nan::To<double>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_lowbo(obj->lp, colnr, value);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_lowbo) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_lowbo(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bounds) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	REAL lower = (REAL)(Nan::To<double>(info[1]).ToChecked());
	REAL upper = (REAL)(Nan::To<double>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_bounds(obj->lp, colnr, lower, upper);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_unbounded) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_unbounded(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_unbounded) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_unbounded(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_int) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	MYBOOL must_be_int = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_int(obj->lp, colnr, must_be_int);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_int) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_int(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_binary) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	MYBOOL must_be_bin = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_binary(obj->lp, colnr, must_be_bin);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_binary) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_binary(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_semicont) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	MYBOOL must_be_sc = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_semicont(obj->lp, colnr, must_be_sc);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_semicont) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_semicont(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_negative) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_negative(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_var_weights) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* weights = NULL;
	if (info[0]->IsArray()) {
		Local<Array> weights_handle = Local<Array>::Cast(info[0]);
		int weights_n = weights_handle->Length();
		weights = new REAL[weights_n];
		for (int i = 0; i < weights_n; i++)
			weights[i] = Nan::To<double>(Nan::Get(weights_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_var_weights(obj->lp, weights);
	if (info[0]->IsArray()) {
		delete[] weights;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_var_priority) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_var_priority(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_pseudocosts) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	REAL* clower = NULL;
	if (info[0]->IsArray()) {
		Local<Array> clower_handle = Local<Array>::Cast(info[0]);
		int clower_n = clower_handle->Length();
		clower = new REAL[clower_n];
		for (int i = 0; i < clower_n; i++)
			clower[i] = Nan::To<double>(Nan::Get(clower_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* cupper = NULL;
	if (info[1]->IsArray()) {
		Local<Array> cupper_handle = Local<Array>::Cast(info[1]);
		int cupper_n = cupper_handle->Length();
		cupper = new REAL[cupper_n];
		for (int i = 0; i < cupper_n; i++)
			cupper[i] = Nan::To<double>(Nan::Get(cupper_handle, i).ToLocalChecked()).ToChecked();
	}
	int* updatelimit = NULL;
	if (info[2]->IsArray()) {
		Local<Array> updatelimit_handle = Local<Array>::Cast(info[2]);
		int updatelimit_n = updatelimit_handle->Length();
		updatelimit = new int[updatelimit_n];
		for (int i = 0; i < updatelimit_n; i++)
			updatelimit[i] = Nan::To<int32_t>(Nan::Get(updatelimit_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_pseudocosts(obj->lp, clower, cupper, updatelimit);
	if (info[0]->IsArray()) {
		delete[] clower;
	}
	if (info[1]->IsArray()) {
		delete[] cupper;
	}
	if (info[2]->IsArray()) {
		delete[] updatelimit;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_pseudocosts) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	REAL* clower = NULL;
	if (info[0]->IsArray()) {
		Local<Array> clower_handle = Local<Array>::Cast(info[0]);
		int clower_n = clower_handle->Length();
		clower = new REAL[clower_n];
		for (int i = 0; i < clower_n; i++)
			clower[i] = Nan::To<double>(Nan::Get(clower_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* cupper = NULL;
	if (info[1]->IsArray()) {
		Local<Array> cupper_handle = Local<Array>::Cast(info[1]);
		int cupper_n = cupper_handle->Length();
		cupper = new REAL[cupper_n];
		for (int i = 0; i < cupper_n; i++)
			cupper[i] = Nan::To<double>(Nan::Get(cupper_handle, i).ToLocalChecked()).ToChecked();
	}
	int* updatelimit = NULL;
	if (info[2]->IsArray()) {
		Local<Array> updatelimit_handle = Local<Array>::Cast(info[2]);
		int updatelimit_n = updatelimit_handle->Length();
		updatelimit = new int[updatelimit_n];
		for (int i = 0; i < updatelimit_n; i++)
			updatelimit[i] = Nan::To<int32_t>(Nan::Get(updatelimit_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_pseudocosts(obj->lp, clower, cupper, updatelimit);
	if (info[0]->IsArray()) {
		delete[] clower;
	}
	if (info[1]->IsArray()) {
		delete[] cupper;
	}
	if (info[2]->IsArray()) {
		delete[] updatelimit;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::add_SOS) {
	if (info.Length() != 6) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
	if (!(info[3]->IsNumber())) return Nan::ThrowTypeError("Fourth argument should be a Number");
	if (!(info[4]->IsArray() || info[4]->IsNull())) return Nan::ThrowTypeError("Fifth argument should be a Array of Numbers or NULL");
	if (!(info[5]->IsArray() || info[5]->IsNull())) return Nan::ThrowTypeError("Sixth argument should be a Array of Numbers or NULL");
	Nan::Utf8String str_name(info[0]);
	char* name = *str_name;
	int sostype = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	int priority = (int)(Nan::To<int32_t>(info[2]).ToChecked());
	int count = (int)(Nan::To<int32_t>(info[3]).ToChecked());
	int* sosvars = NULL;
	if (info[4]->IsArray()) {
		Local<Array> sosvars_handle = Local<Array>::Cast(info[4]);
		int sosvars_n = sosvars_handle->Length();
		sosvars = new int[sosvars_n];
		for (int i = 0; i < sosvars_n; i++)
			sosvars[i] = Nan::To<int32_t>(Nan::Get(sosvars_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* weights = NULL;
	if (info[5]->IsArray()) {
		Local<Array> weights_handle = Local<Array>::Cast(info[5]);
		int weights_n = weights_handle->Length();
		weights = new REAL[weights_n];
		for (int i = 0; i < weights_n; i++)
			weights[i] = Nan::To<double>(Nan::Get(weights_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::add_SOS(obj->lp, name, sostype, priority, count, sosvars, weights);
	if (info[4]->IsArray()) {
		delete[] sosvars;
	}
	if (info[5]->IsArray()) {
		delete[] weights;
	}
}
NAN_METHOD(LinearProgram::is_SOS_var) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_SOS_var(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_row_name) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	Nan::Utf8String str_new_name(info[1]);
	char* new_name = *str_new_name;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_row_name(obj->lp, rownr, new_name);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_row_name) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	char * ret = ::get_row_name(obj->lp, rownr);
	info.GetReturnValue().Set(Nan::New<String>(ret).ToLocalChecked());
}
NAN_METHOD(LinearProgram::get_origrow_name) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int rownr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	char * ret = ::get_origrow_name(obj->lp, rownr);
	info.GetReturnValue().Set(Nan::New<String>(ret).ToLocalChecked());
}
NAN_METHOD(LinearProgram::set_col_name) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	Nan::Utf8String str_new_name(info[1]);
	char* new_name = *str_new_name;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_col_name(obj->lp, colnr, new_name);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_col_name) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	char * ret = ::get_col_name(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<String>(ret).ToLocalChecked());
}
NAN_METHOD(LinearProgram::get_origcol_name) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	char * ret = ::get_origcol_name(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<String>(ret).ToLocalChecked());
}
NAN_METHOD(LinearProgram::unscale) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::unscale(obj->lp);
}
NAN_METHOD(LinearProgram::set_preferdual) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL dodual = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_preferdual(obj->lp, dodual);
}
NAN_METHOD(LinearProgram::set_simplextype) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int simplextype = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_simplextype(obj->lp, simplextype);
}
NAN_METHOD(LinearProgram::get_simplextype) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_simplextype(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::default_basis) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::default_basis(obj->lp);
}
NAN_METHOD(LinearProgram::set_basiscrash) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int mode = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_basiscrash(obj->lp, mode);
}
NAN_METHOD(LinearProgram::get_basiscrash) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_basiscrash(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_basisvar) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int basisPos = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int enteringCol = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::set_basisvar(obj->lp, basisPos, enteringCol);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_basis) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	int* bascolumn = NULL;
	if (info[0]->IsArray()) {
		Local<Array> bascolumn_handle = Local<Array>::Cast(info[0]);
		int bascolumn_n = bascolumn_handle->Length();
		bascolumn = new int[bascolumn_n];
		for (int i = 0; i < bascolumn_n; i++)
			bascolumn[i] = Nan::To<int32_t>(Nan::Get(bascolumn_handle, i).ToLocalChecked()).ToChecked();
	}
	MYBOOL nonbasic = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_basis(obj->lp, bascolumn, nonbasic);
	if (info[0]->IsArray()) {
		delete[] bascolumn;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_basis) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	int* bascolumn = NULL;
	if (info[0]->IsArray()) {
		Local<Array> bascolumn_handle = Local<Array>::Cast(info[0]);
		int bascolumn_n = bascolumn_handle->Length();
		bascolumn = new int[bascolumn_n];
		for (int i = 0; i < bascolumn_n; i++)
			bascolumn[i] = Nan::To<int32_t>(Nan::Get(bascolumn_handle, i).ToLocalChecked()).ToChecked();
	}
	MYBOOL nonbasic = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_basis(obj->lp, bascolumn, nonbasic);
	if (info[0]->IsArray()) {
		delete[] bascolumn;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::reset_basis) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::reset_basis(obj->lp);
}
NAN_METHOD(LinearProgram::guess_basis) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	REAL* guessvector = NULL;
	if (info[0]->IsArray()) {
		Local<Array> guessvector_handle = Local<Array>::Cast(info[0]);
		int guessvector_n = guessvector_handle->Length();
		guessvector = new REAL[guessvector_n];
		for (int i = 0; i < guessvector_n; i++)
			guessvector[i] = Nan::To<double>(Nan::Get(guessvector_handle, i).ToLocalChecked()).ToChecked();
	}
	int* basisvector = NULL;
	if (info[1]->IsArray()) {
		Local<Array> basisvector_handle = Local<Array>::Cast(info[1]);
		int basisvector_n = basisvector_handle->Length();
		basisvector = new int[basisvector_n];
		for (int i = 0; i < basisvector_n; i++)
			basisvector[i] = Nan::To<int32_t>(Nan::Get(basisvector_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::guess_basis(obj->lp, guessvector, basisvector);
	if (info[0]->IsArray()) {
		delete[] guessvector;
	}
	if (info[1]->IsArray()) {
		delete[] basisvector;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_feasible) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	REAL* values = NULL;
	if (info[0]->IsArray()) {
		Local<Array> values_handle = Local<Array>::Cast(info[0]);
		int values_n = values_handle->Length();
		values = new REAL[values_n];
		for (int i = 0; i < values_n; i++)
			values[i] = Nan::To<double>(Nan::Get(values_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL threshold = (REAL)(Nan::To<double>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_feasible(obj->lp, values, threshold);
	if (info[0]->IsArray()) {
		delete[] values;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::solve) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::solve(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::time_elapsed) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::time_elapsed(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
/*
put_bb_nodefunc
lphandleint_intfunc,newnode,void *,bbnodehandle
*/
/*
NAN_METHOD(LinearProgram::put_bb_nodefunc) {
if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
::put_bb_nodefunc(obj->lp, newnode, bbnodehandle);
}
*/
/*
put_bb_branchfunc
lphandleint_intfunc,newbranch,void *,bbbranchhandle
*/
/*
NAN_METHOD(LinearProgram::put_bb_branchfunc) {
if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
::put_bb_branchfunc(obj->lp, newbranch, bbbranchhandle);
}
*/
/*
put_abortfunc
lphandle_intfunc,newctrlc,void *,ctrlchandle
*/
/*
NAN_METHOD(LinearProgram::put_abortfunc) {
if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
::put_abortfunc(obj->lp, newctrlc, ctrlchandle);
}
*/
/*
put_logfunc
lphandlestr_func,newlog,void *,loghandle
*/
/*
NAN_METHOD(LinearProgram::put_logfunc) {
if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
::put_logfunc(obj->lp, newlog, loghandle);
}
*/
/*
put_msgfunc
lphandleint_func,newmsg,void *,msghandle,int,mask
*/
/*
NAN_METHOD(LinearProgram::put_msgfunc) {
if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
int mask = (int)(info[2]->Int32Value());
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
::put_msgfunc(obj->lp, newmsg, msghandle, mask);
}
*/
NAN_METHOD(LinearProgram::get_primal_solution) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* pv = NULL;
	if (info[0]->IsArray()) {
		Local<Array> pv_handle = Local<Array>::Cast(info[0]);
		int pv_n = pv_handle->Length();
		pv = new REAL[pv_n];
		for (int i = 0; i < pv_n; i++)
			pv[i] = Nan::To<double>(Nan::Get(pv_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_primal_solution(obj->lp, pv);
	if (info[0]->IsArray()) {
		delete[] pv;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
get_ptr_primal_solution
REAL **,pv
*/
/*
NAN_METHOD(LinearProgram::get_ptr_primal_solution) {
if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_primal_solution(obj->lp, pv);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_dual_solution) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* rc = NULL;
	if (info[0]->IsArray()) {
		Local<Array> rc_handle = Local<Array>::Cast(info[0]);
		int rc_n = rc_handle->Length();
		rc = new REAL[rc_n];
		for (int i = 0; i < rc_n; i++)
			rc[i] = Nan::To<double>(Nan::Get(rc_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_dual_solution(obj->lp, rc);
	if (info[0]->IsArray()) {
		delete[] rc;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
get_ptr_dual_solution
REAL **,rc
*/
/*
NAN_METHOD(LinearProgram::get_ptr_dual_solution) {
if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_dual_solution(obj->lp, rc);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_lambda) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	REAL* lambda = NULL;
	if (info[0]->IsArray()) {
		Local<Array> lambda_handle = Local<Array>::Cast(info[0]);
		int lambda_n = lambda_handle->Length();
		lambda = new REAL[lambda_n];
		for (int i = 0; i < lambda_n; i++)
			lambda[i] = Nan::To<double>(Nan::Get(lambda_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_lambda(obj->lp, lambda);
	if (info[0]->IsArray()) {
		delete[] lambda;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
get_ptr_lambda
REAL **,lambda
*/
/*
NAN_METHOD(LinearProgram::get_ptr_lambda) {
if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_lambda(obj->lp, lambda);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(read_MPS) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	int options = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	lprec * ret = ::read_MPS(filename, options);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(read_mps) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	Nan::Utf8String str_filename(info[0]);
	FILE *filename = fopen(*str_filename, "r");
	int options = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	lprec * ret = ::read_mps(filename, options);
	fclose(filename);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(read_freeMPS) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	int options = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	lprec * ret = ::read_freeMPS(filename, options);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(read_freemps) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	Nan::Utf8String str_filename(info[0]);
	FILE *filename = fopen(*str_filename, "r");
	int options = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	lprec * ret = ::read_freemps(filename, options);
	fclose(filename);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(LinearProgram::write_mps) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_mps(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_MPS) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_output(info[0]);
	FILE *output = fopen(*str_output, "w");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_MPS(obj->lp, output);
	fclose(output);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_freemps) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_freemps(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_freeMPS) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_output(info[0]);
	FILE *output = fopen(*str_output, "w");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_freeMPS(obj->lp, output);
	fclose(output);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_lp) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_lp(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_LP) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_output(info[0]);
	FILE *output = fopen(*str_output, "w");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_LP(obj->lp, output);
	fclose(output);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
LP_readhandle
lprec **,lp,FILE *,filename,int,verbose,char *,lp_name
*/
/*
NAN_METHOD(LP_readhandle) {
if (info.Length() != 4) return Nan::ThrowError("Invalid number of arguments");
if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
if (!(info[3]->IsString())) return Nan::ThrowTypeError("Fourth argument should be a String");
String::Utf8Value str_filename(info[1]);
FILE *filename = fopen(*str_filename, "r");
int verbose = (int)(info[2]->Int32Value());
String::Utf8Value str_lp_name(info[3]);
char* lp_name = *str_lp_name;
MYBOOL ret = ::LP_readhandle(lp, filename, verbose, lp_name);
fclose(filename);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(read_lp) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsString())) return Nan::ThrowTypeError("Third argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	FILE *filename = fopen(*str_filename, "r");
	int verbose = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	Nan::Utf8String str_lp_name(info[2]);
	char* lp_name = *str_lp_name;
	lprec * ret = ::read_lp(filename, verbose, lp_name);
	fclose(filename);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(read_LP) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	if (!(info[2]->IsString())) return Nan::ThrowTypeError("Third argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	int verbose = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	Nan::Utf8String str_lp_name(info[2]);
	char* lp_name = *str_lp_name;
	lprec * ret = ::read_LP(filename, verbose, lp_name);
	Local<Object> instance = Nan::NewInstance(Nan::New<Function>(constructor)).ToLocalChecked();
	LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
	retobj->lp = ret;
	info.GetReturnValue().Set(instance);
}
NAN_METHOD(LinearProgram::write_basis) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_basis(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::read_basis) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	Nan::Utf8String str_info(info[1]);
	char* infop = *str_info;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::read_basis(obj->lp, filename, infop);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::write_params) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	Nan::Utf8String str_options(info[1]);
	char* options = *str_options;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::write_params(obj->lp, filename, options);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::read_params) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsString())) return Nan::ThrowTypeError("Second argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	Nan::Utf8String str_options(info[1]);
	char* options = *str_options;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::read_params(obj->lp, filename, options);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::reset_params) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::reset_params(obj->lp);
}
NAN_METHOD(LinearProgram::print_lp) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_lp(obj->lp);
}
NAN_METHOD(LinearProgram::print_tableau) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_tableau(obj->lp);
}
NAN_METHOD(LinearProgram::print_objective) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_objective(obj->lp);
}
NAN_METHOD(LinearProgram::print_solution) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int columns = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_solution(obj->lp, columns);
}
NAN_METHOD(LinearProgram::print_constraints) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int columns = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_constraints(obj->lp, columns);
}
NAN_METHOD(LinearProgram::print_duals) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_duals(obj->lp);
}
NAN_METHOD(LinearProgram::print_scales) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_scales(obj->lp);
}
NAN_METHOD(LinearProgram::print_str) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_str(info[0]);
	char* str = *str_str;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::print_str(obj->lp, str);
}
NAN_METHOD(LinearProgram::set_outputstream) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_stream(info[0]);
	FILE *stream = fopen(*str_stream, "w");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_outputstream(obj->lp, stream);
	fclose(stream);
}
NAN_METHOD(LinearProgram::set_outputfile) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_outputfile(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_verbose) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int verbose = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_verbose(obj->lp, verbose);
}
NAN_METHOD(LinearProgram::get_verbose) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_verbose(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_timeout) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	long sectimeout = (long)(Nan::To<int64_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_timeout(obj->lp, sectimeout);
}
NAN_METHOD(LinearProgram::get_timeout) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	long ret = ::get_timeout(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_print_sol) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int print_sol = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_print_sol(obj->lp, print_sol);
}
NAN_METHOD(LinearProgram::get_print_sol) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_print_sol(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_debug) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL debug = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_debug(obj->lp, debug);
}
NAN_METHOD(LinearProgram::is_debug) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_debug(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_trace) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL trace = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_trace(obj->lp, trace);
}
NAN_METHOD(LinearProgram::is_trace) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_trace(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::print_debugdump) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	Nan::Utf8String str_filename(info[0]);
	char* filename = *str_filename;
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::print_debugdump(obj->lp, filename);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_anti_degen) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int anti_degen = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_anti_degen(obj->lp, anti_degen);
}
NAN_METHOD(LinearProgram::get_anti_degen) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_anti_degen(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::is_anti_degen) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int testmask = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_anti_degen(obj->lp, testmask);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_presolve) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int presolvemode = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int maxloops = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_presolve(obj->lp, presolvemode, maxloops);
}
NAN_METHOD(LinearProgram::get_presolve) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_presolve(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_presolveloops) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_presolveloops(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::is_presolve) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int testmask = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_presolve(obj->lp, testmask);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_orig_index) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int lp_index = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_orig_index(obj->lp, lp_index);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_lp_index) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int orig_index = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_lp_index(obj->lp, orig_index);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_maxpivot) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int max_num_inv = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_maxpivot(obj->lp, max_num_inv);
}
NAN_METHOD(LinearProgram::get_maxpivot) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_maxpivot(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_obj_bound) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL obj_bound = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_obj_bound(obj->lp, obj_bound);
}
NAN_METHOD(LinearProgram::get_obj_bound) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_obj_bound(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_mip_gap) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	MYBOOL absolute = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	REAL mip_gap = (REAL)(Nan::To<double>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_mip_gap(obj->lp, absolute, mip_gap);
}
NAN_METHOD(LinearProgram::get_mip_gap) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL absolute = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_mip_gap(obj->lp, absolute);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bb_rule) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int bb_rule = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_bb_rule(obj->lp, bb_rule);
}
NAN_METHOD(LinearProgram::get_bb_rule) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_bb_rule(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_var_branch) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsNumber())) return Nan::ThrowTypeError("Second argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int branch_mode = (int)(Nan::To<int32_t>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_var_branch(obj->lp, colnr, branch_mode);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_var_branch) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int colnr = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_var_branch(obj->lp, colnr);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::is_infinite) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL value = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_infinite(obj->lp, value);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_infinite) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL infinite = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_infinite(obj->lp, infinite);
}
NAN_METHOD(LinearProgram::get_infinite) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_infinite(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsint) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL epsint = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_epsint(obj->lp, epsint);
}
NAN_METHOD(LinearProgram::get_epsint) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_epsint(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsb) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL epsb = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_epsb(obj->lp, epsb);
}
NAN_METHOD(LinearProgram::get_epsb) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_epsb(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsd) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL epsd = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_epsd(obj->lp, epsd);
}
NAN_METHOD(LinearProgram::get_epsd) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_epsd(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsel) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL epsel = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_epsel(obj->lp, epsel);
}
NAN_METHOD(LinearProgram::get_epsel) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_epsel(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epslevel) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int epslevel = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_epslevel(obj->lp, epslevel);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_scaling) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int scalemode = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_scaling(obj->lp, scalemode);
}
NAN_METHOD(LinearProgram::get_scaling) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_scaling(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::is_scalemode) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int testmask = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_scalemode(obj->lp, testmask);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_scaletype) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int scaletype = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_scaletype(obj->lp, scaletype);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_integerscaling) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_integerscaling(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_scalelimit) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL scalelimit = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_scalelimit(obj->lp, scalelimit);
}
NAN_METHOD(LinearProgram::get_scalelimit) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_scalelimit(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_improve) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int improve = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_improve(obj->lp, improve);
}
NAN_METHOD(LinearProgram::get_improve) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_improve(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_pivoting) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int piv_rule = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_pivoting(obj->lp, piv_rule);
}
NAN_METHOD(LinearProgram::get_pivoting) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_pivoting(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_partialprice) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsBoolean())) return Nan::ThrowTypeError("Third argument should be a Boolean");
	int blockcount = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	int* blockstart = NULL;
	if (info[1]->IsArray()) {
		Local<Array> blockstart_handle = Local<Array>::Cast(info[1]);
		int blockstart_n = blockstart_handle->Length();
		blockstart = new int[blockstart_n];
		for (int i = 0; i < blockstart_n; i++)
			blockstart[i] = Nan::To<int32_t>(Nan::Get(blockstart_handle, i).ToLocalChecked()).ToChecked();
	}
	MYBOOL isrow = (MYBOOL)(Nan::To<bool>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_partialprice(obj->lp, blockcount, blockstart, isrow);
	if (info[1]->IsArray()) {
		delete[] blockstart;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_partialprice) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsBoolean())) return Nan::ThrowTypeError("Third argument should be a Boolean");
	int* blockcount = NULL;
	if (info[0]->IsArray()) {
		Local<Array> blockcount_handle = Local<Array>::Cast(info[0]);
		int blockcount_n = blockcount_handle->Length();
		blockcount = new int[blockcount_n];
		for (int i = 0; i < blockcount_n; i++)
			blockcount[i] = Nan::To<int32_t>(Nan::Get(blockcount_handle, i).ToLocalChecked()).ToChecked();
	}
	int* blockstart = NULL;
	if (info[1]->IsArray()) {
		Local<Array> blockstart_handle = Local<Array>::Cast(info[1]);
		int blockstart_n = blockstart_handle->Length();
		blockstart = new int[blockstart_n];
		for (int i = 0; i < blockstart_n; i++)
			blockstart[i] = Nan::To<int32_t>(Nan::Get(blockstart_handle, i).ToLocalChecked()).ToChecked();
	}
	MYBOOL isrow = (MYBOOL)(Nan::To<bool>(info[2]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::get_partialprice(obj->lp, blockcount, blockstart, isrow);
	if (info[0]->IsArray()) {
		delete[] blockcount;
	}
	if (info[1]->IsArray()) {
		delete[] blockstart;
	}
}
NAN_METHOD(LinearProgram::set_multiprice) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int multiblockdiv = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::set_multiprice(obj->lp, multiblockdiv);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_multiprice) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL getabssize = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_multiprice(obj->lp, getabssize);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::is_use_names) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL isrow = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_use_names(obj->lp, isrow);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_use_names) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	MYBOOL isrow = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	MYBOOL use_names = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_use_names(obj->lp, isrow, use_names);
}
NAN_METHOD(LinearProgram::get_nameindex) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsString())) return Nan::ThrowTypeError("First argument should be a String");
	if (!(info[1]->IsBoolean())) return Nan::ThrowTypeError("Second argument should be a Boolean");
	Nan::Utf8String str_varname(info[0]);
	char* varname = *str_varname;
	MYBOOL isrow = (MYBOOL)(Nan::To<bool>(info[1]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_nameindex(obj->lp, varname, isrow);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::is_piv_mode) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int testmask = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_piv_mode(obj->lp, testmask);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::is_piv_rule) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int rule = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_piv_rule(obj->lp, rule);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_break_at_first) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsBoolean())) return Nan::ThrowTypeError("First argument should be a Boolean");
	MYBOOL break_at_first = (MYBOOL)(Nan::To<bool>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_break_at_first(obj->lp, break_at_first);
}
NAN_METHOD(LinearProgram::is_break_at_first) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::is_break_at_first(obj->lp);
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::set_bb_floorfirst) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int bb_floorfirst = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_bb_floorfirst(obj->lp, bb_floorfirst);
}
NAN_METHOD(LinearProgram::get_bb_floorfirst) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_bb_floorfirst(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_bb_depthlimit) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int bb_maxlevel = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_bb_depthlimit(obj->lp, bb_maxlevel);
}
NAN_METHOD(LinearProgram::get_bb_depthlimit) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_bb_depthlimit(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_break_at_value) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL break_at_value = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_break_at_value(obj->lp, break_at_value);
}
NAN_METHOD(LinearProgram::get_break_at_value) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_break_at_value(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_negrange) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL negrange = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_negrange(obj->lp, negrange);
}
NAN_METHOD(LinearProgram::get_negrange) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_negrange(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epsperturb) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL epsperturb = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_epsperturb(obj->lp, epsperturb);
}
NAN_METHOD(LinearProgram::get_epsperturb) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_epsperturb(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::set_epspivot) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	REAL epspivot = (REAL)(Nan::To<double>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_epspivot(obj->lp, epspivot);
}
NAN_METHOD(LinearProgram::get_epspivot) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_epspivot(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_max_level) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_max_level(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_total_nodes) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::get_total_nodes(obj->lp);
}
NAN_METHOD(LinearProgram::get_total_iter) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::get_total_iter(obj->lp);
}
NAN_METHOD(LinearProgram::get_objective) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_objective(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_working_objective) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_working_objective(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_var_primalresult) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int index = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_var_primalresult(obj->lp, index);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_var_dualresult) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int index = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	REAL ret = ::get_var_dualresult(obj->lp, index);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
//checked
NAN_METHOD(LinearProgram::get_variables) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray())) return Nan::ThrowTypeError("First argument should be a Array of Numbers");
	Local<Array> var_handle = Local<Array>::Cast(info[0]);
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int var_n = ::get_Ncolumns(obj->lp);
	REAL* var = new REAL[var_n];
	MYBOOL ret = ::get_variables(obj->lp, var);
	for (int i = 0; i < var_n; i++)
		Nan::Set(var_handle, i, Nan::New<Number>(var[i]));
	delete[] var;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
get_ptr_variables
REAL **,var
*/
/*
NAN_METHOD(LinearProgram::get_ptr_variables) {
if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_variables(obj->lp, var);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_constraints) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray())) return Nan::ThrowTypeError("First argument should be a Array of Numbers");
	Local<Array> constr_handle = Local<Array>::Cast(info[0]);
	int constr_n = constr_handle->Length();
	REAL* constr = new REAL[constr_n];
	for (int i = 0; i < constr_n; i++)
		constr[i] = Nan::To<double>(Nan::Get(constr_handle, i).ToLocalChecked()).ToChecked();
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_constraints(obj->lp, constr);
	delete[] constr;
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
get_ptr_constraints
REAL **,constr
*/
/*
NAN_METHOD(LinearProgram::get_ptr_constraints) {
if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_constraints(obj->lp, constr);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_sensitivity_rhs) {
	if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	REAL* duals = NULL;
	if (info[0]->IsArray()) {
		Local<Array> duals_handle = Local<Array>::Cast(info[0]);
		int duals_n = duals_handle->Length();
		duals = new REAL[duals_n];
		for (int i = 0; i < duals_n; i++)
			duals[i] = Nan::To<double>(Nan::Get(duals_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* dualsfrom = NULL;
	if (info[1]->IsArray()) {
		Local<Array> dualsfrom_handle = Local<Array>::Cast(info[1]);
		int dualsfrom_n = dualsfrom_handle->Length();
		dualsfrom = new REAL[dualsfrom_n];
		for (int i = 0; i < dualsfrom_n; i++)
			dualsfrom[i] = Nan::To<double>(Nan::Get(dualsfrom_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* dualstill = NULL;
	if (info[2]->IsArray()) {
		Local<Array> dualstill_handle = Local<Array>::Cast(info[2]);
		int dualstill_n = dualstill_handle->Length();
		dualstill = new REAL[dualstill_n];
		for (int i = 0; i < dualstill_n; i++)
			dualstill[i] = Nan::To<double>(Nan::Get(dualstill_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_sensitivity_rhs(obj->lp, duals, dualsfrom, dualstill);
	if (info[0]->IsArray()) {
		delete[] duals;
	}
	if (info[1]->IsArray()) {
		delete[] dualsfrom;
	}
	if (info[2]->IsArray()) {
		delete[] dualstill;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
get_ptr_sensitivity_rhs
REAL **,duals,REAL **,dualsfrom,REAL **,dualstill
*/
/*
NAN_METHOD(LinearProgram::get_ptr_sensitivity_rhs) {
if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_sensitivity_rhs(obj->lp, duals, dualsfrom, dualstill);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::get_sensitivity_obj) {
	if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	REAL* objfrom = NULL;
	if (info[0]->IsArray()) {
		Local<Array> objfrom_handle = Local<Array>::Cast(info[0]);
		int objfrom_n = objfrom_handle->Length();
		objfrom = new REAL[objfrom_n];
		for (int i = 0; i < objfrom_n; i++)
			objfrom[i] = Nan::To<double>(Nan::Get(objfrom_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* objtill = NULL;
	if (info[1]->IsArray()) {
		Local<Array> objtill_handle = Local<Array>::Cast(info[1]);
		int objtill_n = objtill_handle->Length();
		objtill = new REAL[objtill_n];
		for (int i = 0; i < objtill_n; i++)
			objtill[i] = Nan::To<double>(Nan::Get(objtill_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_sensitivity_obj(obj->lp, objfrom, objtill);
	if (info[0]->IsArray()) {
		delete[] objfrom;
	}
	if (info[1]->IsArray()) {
		delete[] objtill;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
NAN_METHOD(LinearProgram::get_sensitivity_objex) {
	if (info.Length() != 4) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsArray() || info[0]->IsNull())) return Nan::ThrowTypeError("First argument should be a Array of Numbers or NULL");
	if (!(info[1]->IsArray() || info[1]->IsNull())) return Nan::ThrowTypeError("Second argument should be a Array of Numbers or NULL");
	if (!(info[2]->IsArray() || info[2]->IsNull())) return Nan::ThrowTypeError("Third argument should be a Array of Numbers or NULL");
	if (!(info[3]->IsArray() || info[3]->IsNull())) return Nan::ThrowTypeError("Fourth argument should be a Array of Numbers or NULL");
	REAL* objfrom = NULL;
	if (info[0]->IsArray()) {
		Local<Array> objfrom_handle = Local<Array>::Cast(info[0]);
		int objfrom_n = objfrom_handle->Length();
		objfrom = new REAL[objfrom_n];
		for (int i = 0; i < objfrom_n; i++)
			objfrom[i] = Nan::To<double>(Nan::Get(objfrom_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* objtill = NULL;
	if (info[1]->IsArray()) {
		Local<Array> objtill_handle = Local<Array>::Cast(info[1]);
		int objtill_n = objtill_handle->Length();
		objtill = new REAL[objtill_n];
		for (int i = 0; i < objtill_n; i++)
			objtill[i] = Nan::To<double>(Nan::Get(objtill_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* objfromvalue = NULL;
	if (info[2]->IsArray()) {
		Local<Array> objfromvalue_handle = Local<Array>::Cast(info[2]);
		int objfromvalue_n = objfromvalue_handle->Length();
		objfromvalue = new REAL[objfromvalue_n];
		for (int i = 0; i < objfromvalue_n; i++)
			objfromvalue[i] = Nan::To<double>(Nan::Get(objfromvalue_handle, i).ToLocalChecked()).ToChecked();
	}
	REAL* objtillvalue = NULL;
	if (info[3]->IsArray()) {
		Local<Array> objtillvalue_handle = Local<Array>::Cast(info[3]);
		int objtillvalue_n = objtillvalue_handle->Length();
		objtillvalue = new REAL[objtillvalue_n];
		for (int i = 0; i < objtillvalue_n; i++)
			objtillvalue[i] = Nan::To<double>(Nan::Get(objtillvalue_handle, i).ToLocalChecked()).ToChecked();
	}
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	MYBOOL ret = ::get_sensitivity_objex(obj->lp, objfrom, objtill, objfromvalue, objtillvalue);
	if (info[0]->IsArray()) {
		delete[] objfrom;
	}
	if (info[1]->IsArray()) {
		delete[] objtill;
	}
	if (info[2]->IsArray()) {
		delete[] objfromvalue;
	}
	if (info[3]->IsArray()) {
		delete[] objtillvalue;
	}
	info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
/*
get_ptr_sensitivity_obj
REAL **,objfrom,REAL **,objtill
*/
/*
NAN_METHOD(LinearProgram::get_ptr_sensitivity_obj) {
if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_sensitivity_obj(obj->lp, objfrom, objtill);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
/*
get_ptr_sensitivity_objex
REAL **,objfrom,REAL **,objtill,REAL **,objfromvalue,REAL **,objtillvalue
*/
/*
NAN_METHOD(LinearProgram::get_ptr_sensitivity_objex) {
if (info.Length() != 4) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::get_ptr_sensitivity_objex(obj->lp, objfrom, objtill, objfromvalue, objtillvalue);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
NAN_METHOD(LinearProgram::set_solutionlimit) {
	if (info.Length() != 1) return Nan::ThrowError("Invalid number of arguments");
	if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
	int limit = (int)(Nan::To<int32_t>(info[0]).ToChecked());
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	::set_solutionlimit(obj->lp, limit);
}
NAN_METHOD(LinearProgram::get_solutionlimit) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_solutionlimit(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_solutioncount) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_solutioncount(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Norig_rows) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_Norig_rows(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Nrows) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_Nrows(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Lrows) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_Lrows(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Norig_columns) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_Norig_columns(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
NAN_METHOD(LinearProgram::get_Ncolumns) {
	if (info.Length() != 0) return Nan::ThrowError("Invalid number of arguments");
	LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
	int ret = ::get_Ncolumns(obj->lp);
	info.GetReturnValue().Set(Nan::New<Number>(ret));
}
/*
MPS_readex
lprec **,newlp,void *,userhandle,read_modeldata_func,read_modeldata,int,typeMPS,int,options
*/
/*
NAN_METHOD(MPS_readex) {
if (info.Length() != 5) return Nan::ThrowError("Invalid number of arguments");
if (!(info[3]->IsNumber())) return Nan::ThrowTypeError("Fourth argument should be a Number");
if (!(info[4]->IsNumber())) return Nan::ThrowTypeError("Fifth argument should be a Number");
int typeMPS = (int)(info[3]->Int32Value());
int options = (int)(info[4]->Int32Value());
MYBOOL ret = ::MPS_readex(newlp, userhandle, read_modeldata, typeMPS, options);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
/*
read_lpex
void *,userhandle,read_modeldata_func,read_modeldata,int,verbose,char *,lp_name
*/
/*
NAN_METHOD(read_lpex) {
if (info.Length() != 4) return Nan::ThrowError("Invalid number of arguments");
if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
if (!(info[3]->IsString())) return Nan::ThrowTypeError("Fourth argument should be a String");
int verbose = (int)(info[2]->Int32Value());
String::Utf8Value str_lp_name(info[3]);
char* lp_name = *str_lp_name;
lprec * ret = ::read_lpex(userhandle, read_modeldata, verbose, lp_name);
Local<Object> instance = Nan::New<Function>(constructor)->NewInstance();
LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
retobj->lp = ret;
info.GetReturnValue().Set(instance);
}
*/
/*
write_lpex
void *,userhandle,write_modeldata_func,write_modeldata
*/
/*
NAN_METHOD(LinearProgram::write_lpex) {
if (info.Length() != 2) return Nan::ThrowError("Invalid number of arguments");
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::write_lpex(obj->lp, userhandle, write_modeldata);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
/*
read_mpsex
void *,userhandle,read_modeldata_func,read_modeldata,int,options
*/
/*
NAN_METHOD(read_mpsex) {
if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
int options = (int)(info[2]->Int32Value());
lprec * ret = ::read_mpsex(userhandle, read_modeldata, options);
Local<Object> instance = Nan::New<Function>(constructor)->NewInstance();
LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
retobj->lp = ret;
info.GetReturnValue().Set(instance);
}
*/
/*
read_freempsex
void *,userhandle,read_modeldata_func,read_modeldata,int,options
*/
/*
NAN_METHOD(read_freempsex) {
if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
if (!(info[2]->IsNumber())) return Nan::ThrowTypeError("Third argument should be a Number");
int options = (int)(info[2]->Int32Value());
lprec * ret = ::read_freempsex(userhandle, read_modeldata, options);
Local<Object> instance = Nan::New<Function>(constructor)->NewInstance();
LinearProgram* retobj = Nan::ObjectWrap::Unwrap<LinearProgram>(instance);
retobj->lp = ret;
info.GetReturnValue().Set(instance);
}
*/
/*
MPS_writefileex
int,typeMPS,void *,userhandle,write_modeldata_func,write_modeldata
*/
/*
NAN_METHOD(LinearProgram::MPS_writefileex) {
if (info.Length() != 3) return Nan::ThrowError("Invalid number of arguments");
if (!(info[0]->IsNumber())) return Nan::ThrowTypeError("First argument should be a Number");
int typeMPS = (int)(info[0]->Int32Value());
LinearProgram* obj = Nan::ObjectWrap::Unwrap<LinearProgram>(info.This());
MYBOOL ret = ::MPS_writefileex(obj->lp, typeMPS, userhandle, write_modeldata);
info.GetReturnValue().Set(Nan::New<Boolean>(ret == 1));
}
*/
