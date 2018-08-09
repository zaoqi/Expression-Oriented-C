#include "module<"
define_public_lambda(makevoid2 __ void)({
	make_void();
})
define_public_lambda(add, var(x, int), var(y, int) __ int)({
	x+y;
})
define_private_lambda(addprivate, var(x, int), var(y, int) __ int)({
	x+y;
})
#include ">module"
