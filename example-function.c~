#include "module<"
define_public_lambda(makevoid2() __ void)({
	make_void();
})
define_public_lambda(add(var(x, int), var(y, int)) __ int)({
	x+y;
})
define_private_lambda(addprivate(var(x, int), var(y, int)) __ int)({
	x+y;
})
define_public_inline_lambda(add2(var(x, int), var(y, int)) __ int)({
	var_lambda_withTypeOfBody(f, int __ int)=lambda_withTypeOfBody(var(y, int) __ int)({ x+y; });
	f(y+1);
})
#include ">module"
