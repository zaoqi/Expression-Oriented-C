#include "module<"
define_public_lambda_withTypeOfBody(CaSe(var(x, int)) __ int)(
	case_const_number(x, int)(
		((1,2) __ 3;),
		(_ __ 4;),);)
define_public_lambda_withTypeOfBody(CaSe2(var(x, int)) __ int)(
	case_const_number(x, int)(
		((1,2) __ 3;),
		((0) __ 4;),);)

#include ">module"
