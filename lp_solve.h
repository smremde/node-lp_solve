#include <node.h>
#include "nan.h"
#include "lp_lib.h"

using namespace v8;

NAN_METHOD(getVersion);

NAN_METHOD(createLP);


Persistent<Function> constructor;

class LinearProgram : public node::ObjectWrap {

public:
	static void Init(Handle<Object> exports);

private:

 	LinearProgram();
 	~LinearProgram();


	static NAN_METHOD(New);
	static NAN_METHOD(SetOutputFile);
	static NAN_METHOD(AddColumn);
	static NAN_METHOD(SetColumnInteger);
	static NAN_METHOD(SetColumnBinary);
	static NAN_METHOD(AddConstraint);
	static NAN_METHOD(SetObjective);
	static NAN_METHOD(GetObjectiveValue);
	static NAN_METHOD(Solve);
	static NAN_METHOD(GetSolutionVariables);

	lprec* lp;
};

 //
