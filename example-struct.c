#include "module<"
#include "require<"
#include "example-lambda.c"
#include ">require"
define_struct(List)(
	var(car, void*);
	List* cdr;
)
#include ">module"
