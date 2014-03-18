#include <node.h>
#include "nan.h"

#include "lp_solve.h"
#include "lp_lib.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
	exports->Set(NanSymbol("getVersion"),
		FunctionTemplate::New(getVersion)->GetFunction());
	LinearProgram::Init(exports);
}

NODE_MODULE(lp_solve, InitAll);


NAN_METHOD(getVersion) {
	NanScope();

	int majorversion, minorversion, release, build;

	lp_solve_version(&majorversion, &minorversion, &release, &build);

	Handle<Object> ret = Object::New();

	ret->Set(NanSymbol("majorversion"), Number::New(majorversion));
	ret->Set(NanSymbol("minorversion"), Number::New(minorversion));
	ret->Set(NanSymbol("release"), Number::New(release));
	ret->Set(NanSymbol("build"), Number::New(build));

	NanReturnValue(ret);
};


void LinearProgram::Init(Handle<Object> exports) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(LinearProgram::New);
	tpl->SetClassName(NanSymbol("LinearProgram"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(tpl, "setOutputFile", LinearProgram::SetOutputFile);
	NODE_SET_PROTOTYPE_METHOD(tpl, "addColumn", LinearProgram::AddColumn);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setColumnInteger", LinearProgram::SetColumnInteger);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setColumnBinary", LinearProgram::SetColumnBinary);
	NODE_SET_PROTOTYPE_METHOD(tpl, "addConstraint", LinearProgram::AddConstraint);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setObjective", LinearProgram::SetObjective);
	NODE_SET_PROTOTYPE_METHOD(tpl, "solve", LinearProgram::Solve);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getObjectiveValue", LinearProgram::GetObjectiveValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getSolutionVariables", LinearProgram::GetSolutionVariables);

	NanAssignPersistent(Function, constructor, tpl->GetFunction());
	exports->Set(String::NewSymbol("LinearProgram"), tpl->GetFunction());
}

NAN_METHOD(LinearProgram::New) {
	NanScope();

	if (args.IsConstructCall()) {
		// Invoked as constructor: `new LinearProgram(...)`
		LinearProgram* obj = new LinearProgram();
		obj->Wrap(args.This());
		NanReturnValue(args.This());
	} else {
		//Local<Value> argv[0];
		NanReturnValue(NanPersistentToLocal(constructor)->NewInstance(0, NULL));
	}
}

NAN_METHOD(LinearProgram::SetOutputFile) {
	NanScope();

	assert(args[0]->IsString());

	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());

	size_t bc;

	char *s = NanFromV8String(args[0].As<String>(), Nan::UTF8, &bc, NULL, 0, 0);

	Local<Boolean> res = NanNewLocal<Boolean>(Boolean::New(set_outputfile(obj->lp, s)));

	delete[] s;

	NanReturnValue(res);
}

LinearProgram::LinearProgram() {
	lp = make_lp(0, 0);
}

LinearProgram::~LinearProgram() {
	delete_lp(lp);
}

NAN_METHOD(LinearProgram::AddColumn) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());

	size_t bc;

	char *col_string = NanFromV8String(args[0].As<String>(), Nan::UTF8, &bc, NULL, 0, 0);

	int i = (int)args[1]->Int32Value();

	add_column(obj->lp, NULL);
	set_col_name(obj->lp, i, col_string);

	delete col_string;

	NanReturnUndefined();
}

NAN_METHOD(LinearProgram::SetColumnInteger) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());

	int columnId = Handle<Number>::Cast(args[0])->Int32Value();
	bool isInteger = Handle<Array>::Cast(args[1])->BooleanValue();

  	set_int(obj->lp, columnId, isInteger);

	NanReturnUndefined();
}

NAN_METHOD(LinearProgram::SetColumnBinary) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());

	int columnId = Handle<Number>::Cast(args[0])->Int32Value();
	bool isBinary = Handle<Array>::Cast(args[1])->BooleanValue();

	set_binary(obj->lp, columnId, isBinary);

	NanReturnUndefined();
}

NAN_METHOD(LinearProgram::AddConstraint) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());

  	// name, rowId, rowValues, constrint type, constant

	Handle<Array> rowId = Handle<Array>::Cast(args[1]);
	Handle<Array> rowValue = Handle<Array>::Cast(args[2]);

	int n = rowId->Length();

	int* _rowId = new int[n];
	REAL* _rowValue = new REAL[n];

 	for (int i = 0; i < n; i++) {
 		_rowId[i] = rowId->Get(i)->Int32Value();
 		_rowValue[i] = (REAL)rowValue->Get(i)->NumberValue();
 	}

 	int constr_type = (int)Handle<Number>::Cast(args[3])->Int32Value();
 	REAL rh = (REAL)Handle<Number>::Cast(args[4])->NumberValue();

	add_constraintex(obj->lp, n, _rowValue, _rowId, constr_type, rh);

	if (!args[0]->IsUndefined()) {
		String::Utf8Value utf8str(args[0]);

		char* row_string = (char*) *utf8str;

		set_row_name(obj->lp, get_Nrows(obj->lp), row_string);
	}

	NanReturnUndefined();
}

NAN_METHOD(LinearProgram::SetObjective) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());

  	Handle<Array> rowId = Handle<Array>::Cast(args[1]);
	Handle<Array> rowValue = Handle<Array>::Cast(args[2]);

	int n = rowId->Length();

	int* _rowId = new int[n];
	REAL* _rowValue = new REAL[n];

	for (int i = 0; i < n; i++) {
 		_rowId[i] = rowId->Get(i)->Int32Value();
 		_rowValue[i] = (REAL)rowValue->Get(i)->NumberValue();
 	}

 	bool minimize = args[0]->BooleanValue();

 	if (minimize) {
 		set_minim(obj->lp);
 	} else {
 		set_maxim(obj->lp);
 	}

 	set_obj_fnex(obj->lp, n, _rowValue, _rowId);

	NanReturnUndefined();
}

NAN_METHOD(LinearProgram::Solve) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
  	int res = solve(obj->lp);
	NanReturnValue(Number::New(res));
}

NAN_METHOD(LinearProgram::GetObjectiveValue) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());
  	REAL res = get_objective(obj->lp);
	NanReturnValue(Number::New(res));
}

NAN_METHOD(LinearProgram::GetSolutionVariables) {
	NanScope();
	LinearProgram* obj = node::ObjectWrap::Unwrap<LinearProgram>(args.This());

	int n = get_Ncolumns(obj->lp);
	REAL* row = new REAL[n];

  	get_variables(obj->lp, row);

  	Handle<Array> ret = Array::New(n);

	for (int i=0; i<n; i++) {
		ret->Set(i, Number::New(row[i]));
	}

	NanReturnValue(ret);
}
