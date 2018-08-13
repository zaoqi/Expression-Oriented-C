#include "module<"
define_public_lambda_withTypeOfBody(add(var(x, int), var(y, int)) __ int)(
	x+y;)
define_public_withTypeOfBody_lambda(int add2(int x, var(y, int)))(
	x+y;)
define_public_inline_withTypeOfBody_lambda(int add3(int x, int y))(
	x+y;)
define_private_inline_lambda_s_withTypeOfBody(add4 __ var(x, int), var(y, int)__ int)(
	make_void();
	add3(x,y);)
#include ">module"
